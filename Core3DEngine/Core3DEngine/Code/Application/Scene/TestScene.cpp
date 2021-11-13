/*****************************************************************//**
 * \file   TestScene.h
 * \brief  テストシーン
 *
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/

#include "TestScene.h"

#include <CoreEngine/Core_Engine.h>
#include <CoreRenderer/Core/Core_Renderer.h>
#include <CoreRenderer/Core/Core_Device.h>
#include <CoreRenderer/Core/Core_CommandList.h>
#include <CoreRenderer/Core/Core_Geometry.h>


core::ShaderID			g_shaderID;
core::MaterialID			g_matID;
core::RenderBufferID		g_rdID;
core::TextureID			g_texID;

constexpr std::uint32_t MAX_WORLD_BUFFER = 2;
core::BufferID			g_worldID[MAX_WORLD_BUFFER];

core::RenderTargetID		g_rtID;
core::DepthStencilID		g_dsID;
Color					g_clearColor = Color(0.2f, 0.2f, 0.2f, 1.0f);

// ライティング
constexpr std::uint32_t	MAX_POINT_LIGHT = 6;
core::CorePointLight		g_pointLights[MAX_POINT_LIGHT];
core::BufferID			g_pointLightBufferID;
core::ShaderID			g_lightShaderID;
core::MaterialID			g_lightMatID;
core::RenderBufferID		g_litRdID;
core::RenderBufferID		g_litQuadID;

// ポストエフェクト用
core::ShaderID			g_postShaderID;
core::MaterialID			g_postMatID;
core::RenderBufferID		g_postRdID;

constexpr int MAX_WORLD = 1000;

 /// @brief スタート
void TestScene::Start()
{
	auto* renderer = m_pSceneManager->getEngine()->getRenderer();
	auto* device = renderer->getDevice();

	float width = static_cast<float>(renderer->getCoreEngine()->getWindowWidth());
	float height = static_cast<float>(renderer->getCoreEngine()->getWindowHeight());

	// テクスチャマトリックス
	Matrix texMatrix = Matrix::CreateScale(6);
	texMatrix *= Matrix::CreateRotationZ(1);
	texMatrix = texMatrix.Transpose();

	//--- ジオメトリ ---
	auto quadID = device->createMesh("quad");
	auto* pQuad = device->getMesh(quadID);
	Geometry::Quad(*pQuad);

	auto cubeMehID = device->createMesh("cube");
	auto* pCubeMesh = device->getMesh(cubeMehID);
	Geometry::Cube(*pCubeMesh);

	{
		// テクスチャの生成
		uint32_t texWidth = 256u;
		uint32_t texHeight = 256u;
		uint32_t texDepth = 4u;
		std::vector<unsigned char> texArray(texWidth * texHeight * texDepth);
		core::TextureData texData;
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

		core::TextureDesc texDesc;
		texDesc.width = texWidth;
		texDesc.height = texHeight;
		texDesc.depth = texDepth;
		texDesc.mipLevels = 1;
		texDesc.bindFlags = 0 | core::BindFlags::SHADER_RESOURCE;
		texDesc.format = core::TextureFormat::R8G8B8A8_UNORM;

		auto texID = device->createTexture(texDesc, &texData);
		g_texID = texID;

		// シェーダー・マテリアルの生成
		core::ShaderDesc shaderDesc;
		shaderDesc.m_stages = core::ShaderStageFlags::VS | core::ShaderStageFlags::PS;

		shaderDesc.m_name = "Unlit";

		auto unlitShaderID = device->createShader(shaderDesc);
		auto unlitMatID = device->createMaterial("Unlit", unlitShaderID);
		auto* pUnlitMat = device->getMaterial(unlitMatID);
		pUnlitMat->setVector4("_Color", Vector4(1, 1, 1, 1));
		pUnlitMat->setTexture("_Texture", texID);
		pUnlitMat->setSampler("_Sampler", core::SamplerState::LINEAR_WRAP);
		g_shaderID = unlitShaderID;
		g_matID = unlitMatID;

		// レンダーバッファの作成
		g_rdID = device->createRenderBuffer(unlitShaderID, cubeMehID);
	}

	{
		// レンダーターゲットの生成
		core::TextureDesc rtDesc = {};
		rtDesc.name = "レンダーターゲット";
		rtDesc.width = width;
		rtDesc.height = height;
		rtDesc.bindFlags = 0 | core::BindFlags::RENDER_TARGET | core::BindFlags::SHADER_RESOURCE;
		rtDesc.format = core::TextureFormat::R8G8B8A8_UNORM;
		g_rtID = device->createRenderTarget(rtDesc, g_clearColor);

		// デプスステンシルの生成
		rtDesc.name = "デプスステンシル";
		rtDesc.bindFlags = 0 | core::BindFlags::DEPTH_STENCIL | core::BindFlags::SHADER_RESOURCE;
		rtDesc.format = core::TextureFormat::R32_TYPELESS;
		g_dsID = device->createDepthStencil(rtDesc);

		// ワールドマトリックスの作成
		core::BufferDesc bufferDesc;
		bufferDesc.name = "WorldMatrix";
		bufferDesc.size = sizeof(Matrix);
		bufferDesc.count = MAX_WORLD;
		bufferDesc.bindFlags = 0 | core::BindFlags::CONSTANT_BUFFER;
		bufferDesc.usage = core::Usage::DEFAULT;
		bufferDesc.cpuAccessFlags = 0 | core::CPUAccessFlags::NONE;
		for (std::uint32_t i = 0; i < MAX_WORLD_BUFFER; ++i)
		{
			bufferDesc.name = std::string("WorldMatrix") + std::to_string(i);
			g_worldID[i] = device->createBuffer(bufferDesc);
		}
	}

	auto* pRT = device->getRenderTarget(g_rtID);
	//----- ポストエフェクト用
	{
		// シェーダー・マテリアルの生成
		core::ShaderDesc shaderDesc;
		shaderDesc.m_stages = core::ShaderStageFlags::VS | core::ShaderStageFlags::PS;
		shaderDesc.m_name = "Post";

		g_postShaderID = device->createShader(shaderDesc);
		g_postMatID = device->createMaterial("Post", g_postShaderID);
		auto* pPostMat = device->getMaterial(g_postMatID);
		pPostMat->setVector3("_Color", Vector3(1, 1, 1));
		pPostMat->setTexture("_RT", pRT->m_texID);
		pPostMat->setSampler("_Sampler", core::SamplerState::LINEAR_WRAP);

		// レンダーバッファの作成
		g_postRdID = device->createRenderBuffer(g_postShaderID, quadID);
	}

	//----- ライティング -----
	{
		// シェーダー・マテリアルの生成
		core::ShaderDesc shaderDesc;
		shaderDesc.m_stages = core::ShaderStageFlags::VS | core::ShaderStageFlags::PS;
		shaderDesc.m_name = "Lit";

		g_lightShaderID = device->createShader(shaderDesc);
		g_lightMatID = device->createMaterial("Lit", g_lightShaderID);
		auto* pMat = device->getMaterial(g_lightMatID);
		pMat->setVector3("_Color", Vector3(1, 1, 1));
		pMat->setUint("_PointLightNum", MAX_POINT_LIGHT);
		pMat->setSampler("_Sampler", core::SamplerState::LINEAR_WRAP);
		pMat->setTexture("_Texture", g_texID);
		pMat->setMatrix("_mTex", texMatrix);

		// ポイントライトバッファ作成
		core::BufferDesc bufferDesc;
		bufferDesc.name = "PointLights";
		bufferDesc.size = sizeof(core::CorePointLight);
		bufferDesc.count = MAX_POINT_LIGHT;
		bufferDesc.bindFlags = 0 | core::BindFlags::SHADER_RESOURCE;
		bufferDesc.usage = core::Usage::DEFAULT;
		bufferDesc.cpuAccessFlags = 0 | core::CPUAccessFlags::NONE;
		bufferDesc.miscFlags = 0 | core::MiscFlags::BUFFER_STRUCTURED;
		g_pointLightBufferID = device->createBuffer(bufferDesc);

		// レンダーバッファの作成
		g_litRdID = device->createRenderBuffer(g_lightShaderID, cubeMehID);
		g_litQuadID = device->createRenderBuffer(g_lightShaderID, quadID);
	}
}

/// @brief システムの更新
void TestScene::Update()
{

}

/// @brief パイプラインの描画
void TestScene::Render()
{
	auto* renderer = m_pSceneManager->getEngine()->getRenderer();
	auto* device = renderer->getDevice();
	auto* cmdList = renderer->getCommandList();

	float width = static_cast<float>(renderer->getCoreEngine()->getWindowWidth());
	float height = static_cast<float>(renderer->getCoreEngine()->getWindowHeight());

	auto* pRT = device->getRenderTarget(g_rtID);
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

	Matrix proj = Matrix::CreatePerspectiveFOV(
		Mathf::ToRadians(60),
		width,
		height,
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
			world *= Matrix::CreateRotationZXY(rot);
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
		world *= Matrix::CreateRotationZXY(rot);
		world *= Matrix::CreateTranslation(pos);
		world = world.Transpose();
	}
	pWorldBuffer0->UpdateBuffer(aWorld.data(), sizeof(Matrix) * MAX_WORLD);

	pUnlitMat->setMatrix("_mView", view);
	pUnlitMat->setMatrix("_mProj", proj);

	pLitMat->setVector3("_ViewPos", eyepos);
	pLitMat->setMatrix("_mView", view);
	pLitMat->setMatrix("_mProj", proj);

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


		pPointLightBuffer->UpdateBuffer(g_pointLights, sizeof(core::CorePointLight) * MAX_POINT_LIGHT);
	}


	//----- 描画
	{
		// レンダーターゲット指定
		cmdList->setRenderTarget(g_rtID, g_dsID);

		// レンダーターゲットクリア
		cmdList->clearRederTarget(g_rtID, g_clearColor);
		cmdList->clearDepthStencil(g_dsID, 1.0f, 0);

		// ビューポート指定
		cmdList->setViewport(Viewport(0, 0, width, height));

		// マテリアルの指定
		//cmdList->setMaterial(g_matID);
		cmdList->setMaterial(g_lightMatID);

		// レンダーバッファの指定
		//cmdList->setRenderBuffer(g_rdID);
		cmdList->setRenderBuffer(g_litRdID);

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
			world *= Matrix::CreateRotationZXY(rot);
			world *= Matrix::CreateTranslation(pos);
			world = world.Transpose();
			pWorldBuffer1->UpdateBuffer(&world, sizeof(Matrix));

			// マテリアル
			cmdList->setMaterial(g_lightMatID);
			// レンダーバッファの指定
			cmdList->setRenderBuffer(g_litQuadID);
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
		proj = Matrix::CreateOrtho(width, height, 1.0f, 100.0f);
		proj = proj.Transpose();

		pPostMat->setMatrix("_mWorld", world);
		pPostMat->setMatrix("_mView", view);
		pPostMat->setMatrix("_mProj", proj);
		pPostMat->setTexture("_RT", pRT->m_texID);

		// マテリアルの更新
		pPostMat->setVector3("_Color", Vector3(1, 1, 1));
		static float _time;
		_time += 0.05f;
		pPostMat->setFloat("_Time", _time);


		// バッファバッファ指定
		cmdList->setBackBuffer();
		cmdList->clearBackBuffer(Color());

		// マテリアルの指定
		cmdList->setMaterial(g_postMatID);
		// レンダーバッファの指定
		cmdList->setRenderBuffer(g_postRdID);
		// 描画
		cmdList->render(g_postRdID, 1);
	}

	// バインド解除
	pPostMat->setTexture("_RT", core::NONE_TEXTURE_ID);
	cmdList->setMaterial(g_postMatID);

	// バックバッファへコピー
	cmdList->copyBackBuffer(pRT->m_texID);

}

/// @brief エンド
void TestScene::End()
{

}
