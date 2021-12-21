/*****************************************************************//**
 * \file   TestScene.h
 * \brief  テストシーン
 *
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/

#include "TestScene.h"

#include <Engine/Core/Engine.h>
#include <RHI/Core/RHI.h>
#include <RHI/Core/Device.h>
#include <RHI/Core/CommandList.h>
#include <Resource/Core/Geometry.h>

#include <Runtime\Core\EntityManager.h>
#include <Runtime\Core\ComponentManager.h>
#include <Runtime\Core\Script.h>

#include <Runtime\System\TransformSystm.h>

using namespace Core;

class TestScript : public Script
{
	DECLARE_SCRIPT_INFO(TestScript);
public:

private:

};


Core::ShaderID			g_shaderID;
Core::MaterialID			g_matID;
Core::RenderBufferID		g_rdID;
Core::TextureID			g_texID;

constexpr std::uint32_t MAX_WORLD_BUFFER = 2;
Core::GPUBufferID			g_worldID[MAX_WORLD_BUFFER];

Core::RenderTargetID		g_rtID;
Core::DepthStencilID		g_dsID;
Color					g_ClearColor = Color(0.2f, 0.2f, 0.2f, 1.0f);

// ライティング
constexpr std::uint32_t	MAX_POINT_LIGHT = 6;
Core::CorePointLight		g_pointLights[MAX_POINT_LIGHT];
Core::GPUBufferID			g_pointLightBufferID;
Core::ShaderID			g_lightShaderID;
Core::MaterialID			g_lightMatID;
Core::RenderBufferID		g_litRdID;
Core::RenderBufferID		g_litQuadID;

// ポストエフェクト用
Core::ShaderID			g_postShaderID;
Core::MaterialID			g_postMatID;
Core::RenderBufferID		g_postRdID;

constexpr int MAX_WORLD = 1000;

 /// @brief スタート
void TestScene::Start()
{
	auto* renderer = GetSceneManager()->GetEngine()->GetRenderer();
	auto* device = renderer->GetDevice();

	float width = static_cast<float>(renderer->GetEngine()->GetWindowWidth());
	float height = static_cast<float>(renderer->GetEngine()->GetWindowHeight());

	// テクスチャマトリックス
	Matrix texMatrix = Matrix::CreateScale(6);
	texMatrix *= Matrix::CreateRotationZ(1);
	texMatrix = texMatrix.Transpose();

	//--- ジオメトリ ---
	auto quadID = device->CreateMesh("quad");
	auto* pQuad = device->getMesh(quadID);
	Geometry::Quad(*pQuad);

	auto cubeMehID = device->CreateMesh("cube");
	auto* pCubeMesh = device->getMesh(cubeMehID);
	Geometry::Cube(*pCubeMesh);

	{
		// テクスチャの生成
		uint32_t texWidth = 256u;
		uint32_t texHeight = 256u;
		uint32_t texDepth = 4u;
		std::vector<unsigned char> texArray(texWidth * texHeight * texDepth);
		Core::TextureData texData;
		texData.pInitData = texArray.data();
		texData.size = texArray.size();

		uint32_t texX = texWidth * texDepth;
		for (int y = 0; y < texHeight; ++y)
		{
			for (int x = 0; x < texX; x += texDepth)
			{
				if (y < texHeight / 2)
				{
					if (x < texX / 2)
					{
						texArray[y * texX + x + 0] = 255;	// R
						texArray[y * texX + x + 1] = 100;	// G
						texArray[y * texX + x + 2] = 100;	// B
						texArray[y * texX + x + 3] = 255;	// A
					}
					else
					{
						texArray[y * texX + x + 0] = 100;	// R
						texArray[y * texX + x + 1] = 255;	// G
						texArray[y * texX + x + 2] = 100;	// B
						texArray[y * texX + x + 3] = 255;	// A
					}
				}
				else
				{
					if (x < texX / 2)
					{
						texArray[y * texX + x + 0] = 100;	// R
						texArray[y * texX + x + 1] = 100;	// G
						texArray[y * texX + x + 2] = 255;	// B
						texArray[y * texX + x + 3] = 255;	// A
					}
					else
					{
						texArray[y * texX + x + 0] = 255;	// R
						texArray[y * texX + x + 1] = 255;	// G
						texArray[y * texX + x + 2] = 255;	// B
						texArray[y * texX + x + 3] = 255;	// A
					}
				}

			}
		}

		Core::TextureDesc texDesc;
		texDesc.width = texWidth;
		texDesc.height = texHeight;
		texDesc.depth = texDepth;
		texDesc.mipLevels = 1;
		texDesc.bindFlags = 0 | Core::BindFlags::SHADER_RESOURCE;
		texDesc.format = Core::TextureFormat::R8G8B8A8_UNORM;

		auto texID = device->CreateTexture(texDesc, &texData);
		g_texID = texID;

		// シェーダー・マテリアルの生成
		Core::ShaderDesc shaderDesc;
		shaderDesc.m_stages = Core::GraphicsShaderStageFlags::VS | Core::GraphicsShaderStageFlags::PS;

		shaderDesc.m_name = "Unlit";

		auto unlitShaderID = device->CreateShader(shaderDesc);
		auto unlitMatID = device->CreateMaterial("Unlit", unlitShaderID);
		auto* pUnlitMat = device->getMaterial(unlitMatID);
		pUnlitMat->SetVector4("_Color", Vector4(1, 1, 1, 1));
		pUnlitMat->setTexture("_Texture", texID);
		pUnlitMat->setSampler("_Sampler", Core::SamplerState::LINEAR_WRAP);
		g_shaderID = unlitShaderID;
		g_matID = unlitMatID;

		// レンダーバッファの作成
		g_rdID = device->CreateRenderBuffer(unlitShaderID, cubeMehID);
	}

	{
		// レンダーターゲットの生成
		Core::TextureDesc rtDesc = {};
		rtDesc.name = "レンダーターゲット";
		rtDesc.width = width;
		rtDesc.height = height;
		rtDesc.bindFlags = 0 | Core::BindFlags::RENDER_TARGET | Core::BindFlags::SHADER_RESOURCE;
		rtDesc.format = Core::TextureFormat::R8G8B8A8_UNORM;
		g_rtID = device->CreateRenderTarget(rtDesc, g_ClearColor);

		// デプスステンシルの生成
		rtDesc.name = "デプスステンシル";
		rtDesc.bindFlags = 0 | Core::BindFlags::DEPTH_STENCIL | Core::BindFlags::SHADER_RESOURCE;
		rtDesc.format = Core::TextureFormat::R32_TYPELESS;
		g_dsID = device->CreateDepthStencil(rtDesc);

		// ワールドマトリックスの作成
		Core::GPUBufferDesc bufferDesc;
		bufferDesc.name = "WorldMatrix";
		bufferDesc.size = sizeof(Matrix);
		bufferDesc.count = MAX_WORLD;
		bufferDesc.bindFlags = 0 | Core::BindFlags::CONSTANT_BUFFER;
		bufferDesc.usage = Core::Usage::DEFAULT;
		bufferDesc.cpuAccessFlags = 0 | Core::CPUAccessFlags::NONE;
		for (std::uint32_t i = 0; i < MAX_WORLD_BUFFER; ++i)
		{
			bufferDesc.name = std::string("WorldMatrix") + std::to_string(i);
			g_worldID[i] = device->CreateBuffer(bufferDesc);
		}
	}

	auto* pRT = device->GetRenderTarget(g_rtID);
	//----- ポストエフェクト用
	{
		// シェーダー・マテリアルの生成
		Core::ShaderDesc shaderDesc;
		shaderDesc.m_stages = Core::GraphicsShaderStageFlags::VS | Core::GraphicsShaderStageFlags::PS;
		shaderDesc.m_name = "Post";

		g_postShaderID = device->CreateShader(shaderDesc);
		g_postMatID = device->CreateMaterial("Post", g_postShaderID);
		auto* pPostMat = device->getMaterial(g_postMatID);
		pPostMat->SetVector3("_Color", Vector3(1, 1, 1));
		pPostMat->setTexture("_RT", pRT->m_texID);
		pPostMat->setSampler("_Sampler", Core::SamplerState::LINEAR_WRAP);

		// レンダーバッファの作成
		g_postRdID = device->CreateRenderBuffer(g_postShaderID, quadID);
	}

	//----- ライティング -----
	{
		// シェーダー・マテリアルの生成
		Core::ShaderDesc shaderDesc;
		shaderDesc.m_stages = Core::GraphicsShaderStageFlags::VS | Core::GraphicsShaderStageFlags::PS;
		shaderDesc.m_name = "Lit";

		g_lightShaderID = device->CreateShader(shaderDesc);
		g_lightMatID = device->CreateMaterial("Lit", g_lightShaderID);
		auto* pMat = device->getMaterial(g_lightMatID);
		pMat->SetVector3("_Color", Vector3(1, 1, 1));
		pMat->setUint("_PointLightNum", MAX_POINT_LIGHT);
		pMat->setSampler("_Sampler", Core::SamplerState::LINEAR_WRAP);
		pMat->setTexture("_Texture", g_texID);
		pMat->SetMatrix("_mTex", texMatrix);

		// ポイントライトバッファ作成
		Core::GPUBufferDesc bufferDesc;
		bufferDesc.name = "PointLights";
		bufferDesc.size = sizeof(Core::CorePointLight);
		bufferDesc.count = MAX_POINT_LIGHT;
		bufferDesc.bindFlags = 0 | Core::BindFlags::SHADER_RESOURCE;
		bufferDesc.usage = Core::Usage::DEFAULT;
		bufferDesc.cpuAccessFlags = 0 | Core::CPUAccessFlags::NONE;
		bufferDesc.miscFlags = 0 | Core::MiscFlags::BUFFER_STRUCTURED;
		g_pointLightBufferID = device->CreateBuffer(bufferDesc);

		// レンダーバッファの作成
		g_litRdID = device->CreateRenderBuffer(g_lightShaderID, cubeMehID);
		g_litQuadID = device->CreateRenderBuffer(g_lightShaderID, quadID);
	}

	// テスト
	Entity* pParent = nullptr;
	for (int i = 0; i < 10; ++i)
	{
		auto pEntity = GetEntityManager()->CreateEntity(std::to_string(i));
		auto pTestScript = pEntity->AddComponent<TestScript>();
		if (pParent)
		{
			pParent->transform()->AddChild(pEntity->transform()->GetTransformID());
		}
		pParent = pEntity;
	}


	GetSystemManager()->AddSystem<TransformSystem>();
}

/// @brief システムの更新
void TestScene::Update()
{

}

/// @brief パイプラインの描画
void TestScene::Render()
{
	auto* renderer = GetSceneManager()->GetEngine()->GetRenderer();
	auto* device = renderer->GetDevice();
	auto* cmdList = renderer->GetCommandList();

	float width = static_cast<float>(renderer->GetEngine()->GetWindowWidth());
	float height = static_cast<float>(renderer->GetEngine()->GetWindowHeight());

	auto* pRT = device->GetRenderTarget(g_rtID);
	auto* pUnlitMat = device->getMaterial(g_matID);
	auto* pLitMat = device->getMaterial(g_lightMatID);
	auto* pPostMat = device->getMaterial(g_postMatID);

	auto* pWorldBuffer0 = device->getBuffer(g_worldID[0]);
	auto* pWorldBuffer1 = device->getBuffer(g_worldID[1]);
	auto* pPointLightBuffer = device->getBuffer(g_pointLightBufferID);

	// カメラ
	Vector3 eyepos = Vector3(0, 3, -5);
	Vector3 eyedir = Vector3(0, 0, 0);
	Vector3 up = Vector3(0, 1, 0);
	Matrix view = Matrix::CreateLookAt(eyepos, eyedir, up);

	Matrix proj = Matrix::CreatePerspectiveFieldOfView(
		Mathf::ToRadians(60),
		width / height,
		1.0f,
		100.0f
	);
	view = view.Transpose();
	proj = proj.Transpose();

	// ワールドマトリックス
	static float angleY = 0;
	angleY += 0.01f;
	float y = -8;
	std::vector<Matrix> aWorld(MAX_WORLD);
	int boxNum = 31;
	for (int y = 0; y < boxNum; ++y)
	{
		for (int x = 0; x < boxNum; ++x)
		{
			auto& world = aWorld[y * boxNum + x];
			float s = 0.1f;
			float t = s * 4;
			float o = -boxNum / 2.0f + t;
			Vector3 pos = Vector3(o * t + x * t, -0.4f, o * t + y * t);
			Vector3 rot = Vector3(0, angleY, 0);
			//Vector3 sca = Vector3(0.3f, 0.3f, 0.3f);
			Vector3 sca = Vector3(s,s,s);
			world = Matrix::CreateScale(sca);
			world *= Matrix::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
			world *= Matrix::CreateTranslation(pos);
			world = world.Transpose();
		}
	}
	for (int i = boxNum; i < boxNum + 1; ++i)
	{
		auto& world = aWorld[i];
		Vector3 pos = Vector3();
		Vector3 rot = Vector3(0, angleY, 0);
		Vector3 sca = Vector3(1.0f, 1.0f, 1.0f);
		world = Matrix::CreateScale(sca);
		world *= Matrix::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
		world *= Matrix::CreateTranslation(pos);
		world = world.Transpose();
	}
	pWorldBuffer0->UpdateBuffer(aWorld.data(), sizeof(Matrix) * MAX_WORLD);

	pUnlitMat->SetMatrix("_mView", view);
	pUnlitMat->SetMatrix("_mProj", proj);

	pLitMat->SetVector3("_ViewPos", eyepos);
	pLitMat->SetMatrix("_mView", view);
	pLitMat->SetMatrix("_mProj", proj);

	//----- ライト更新
	{
		static float litLen;
		litLen += 0.03f;
		Vector3 pointPos = Vector3(fabsf(sinf(litLen)) * 2.0f + 0.5f, 0, (cosf(litLen)) * 0.5f);
		static float litY;
		litY -= 0.03f;
		for (std::uint32_t i = 0; i < MAX_POINT_LIGHT; ++i)
		{
			g_pointLights[i].position = Vector3::Transform(pointPos, Matrix::CreateRotationY(
				litY + Mathf::TwoPi / MAX_POINT_LIGHT * (i % MAX_POINT_LIGHT)));
			g_pointLights[i].range = 3;
			if(i % 3 == 0)
				g_pointLights[i].color = Vector4(1.0f, 0.1f, 0.1f, 1.0f);
			else if(i % 3 == 1)
				g_pointLights[i].color = Vector4(0.1f, 1.0f, 0.1f, 1.0f);
			else if(i % 3 == 2)
				g_pointLights[i].color = Vector4(0.1f, 0.1f, 1.0f, 1.0f);
		}


		pPointLightBuffer->UpdateBuffer(g_pointLights, sizeof(Core::CorePointLight) * MAX_POINT_LIGHT);
	}


	//----- 描画
	{
		// レンダーターゲット指定
		cmdList->SetRenderTarget(g_rtID, g_dsID);

		// レンダーターゲットクリア
		cmdList->ClearRederTarget(g_rtID, g_ClearColor);
		cmdList->ClearDepthStencil(g_dsID, 1.0f, 0);

		// ビューポート指定
		cmdList->SetViewport(Viewport(0, 0, width, height));

		// マテリアルの指定
		//cmdList->SetMaterial(g_matID);
		cmdList->SetMaterial(g_lightMatID);

		// レンダーバッファの指定
		//cmdList->SetRenderBuffer(g_rdID);
		cmdList->SetRenderBuffer(g_litRdID);

		// バッファ指定
		//cmdList->bindGlobalBuffer(g_shaderID, "World", g_worldID);
		cmdList->bindGlobalBuffer(g_lightShaderID, "World", g_worldID[0]);
		cmdList->bindGlobalBuffer(g_lightShaderID, "_PointLights", g_pointLightBufferID);

		// 描画
		//for (int i = 0; i < 100; ++i)
		{
			//cmdList->render(g_rdID, 1);
			cmdList->render(g_litRdID, boxNum * boxNum);
		}

		// 床の描画
		{
			// マトリックス更新
			Matrix world;
			Vector3 pos = Vector3(0, 2, 0);
			Vector3 rot = Vector3(-Mathf::Pi / 2, 0, 0);
			//Vector3 sca = Vector3(0.3f, 0.3f, 0.3f);
			Vector3 sca = Vector3(5.0f, 5.0f, 5.0f);
			world = Matrix::CreateScale(sca);
			world *= Matrix::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
			world *= Matrix::CreateTranslation(pos);
			world = world.Transpose();
			pWorldBuffer1->UpdateBuffer(&world, sizeof(Matrix));

			// マテリアル
			cmdList->SetMaterial(g_lightMatID);
			// レンダーバッファの指定
			cmdList->SetRenderBuffer(g_litQuadID);
			// バッファ指定
			cmdList->bindGlobalBuffer(g_lightShaderID, "World", g_worldID[1]);
			cmdList->bindGlobalBuffer(g_lightShaderID, "_PointLights", g_pointLightBufferID);
			// 描画
			cmdList->render(g_litQuadID, 1);
		}
	}

	//--- ポストエフェクト
	{
		// トランスフォームのセット
		Matrix world = Matrix::CreateScale(width, height, 1.0f);
		world = world.Transpose();
		view = Matrix::CreateLookAt(Vector3(0,0,-1), Vector3(), up);
		view = view.Transpose();
		proj = Matrix::CreateOrthographic(width, height, 1.0f, 100.0f);
		proj = proj.Transpose();

		pPostMat->SetMatrix("_mWorld", world);
		pPostMat->SetMatrix("_mView", view);
		pPostMat->SetMatrix("_mProj", proj);
		pPostMat->setTexture("_RT", pRT->m_texID);

		// マテリアルの更新
		pPostMat->SetVector3("_Color", Vector3(1, 1, 1));
		static float _time;
		_time += 0.05f;
		pPostMat->setFloat("_Time", _time);


		// バッファバッファ指定
		//cmdList->SetBackBuffer();
		//cmdList->ClearBackBuffer(Color());
		cmdList->SetRenderTarget(m_sceneResultID);
		cmdList->ClearRederTarget(m_sceneResultID, Color());

		// マテリアルの指定
		cmdList->SetMaterial(g_postMatID);
		// レンダーバッファの指定
		cmdList->SetRenderBuffer(g_postRdID);
		// 描画
		cmdList->render(g_postRdID, 1);
	}

	// バインド解除
	pPostMat->setTexture("_RT", Core::NONE_TEXTURE_ID);
	cmdList->SetMaterial(g_postMatID);

	// バックバッファへコピー
	//cmdList->CopyBackBuffer(pRT->m_texID);

}

/// @brief エンド
void TestScene::End()
{

}
