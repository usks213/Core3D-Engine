/*****************************************************************//**
 * \file   Material.h
 * \brief  マテリアル
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "Material.h"
#include <Resource\Core\ResourceManager.h>
#include <Core\Engine.h>
#include <RHI\Core\RHI_Renderer.h>
#include <RHI\Core\RHI_Device.h>

using namespace Core;

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

 /// @brief コンストラクタ
Material::Material() :
	m_isTransparent(false),
	m_blendState(RHI::BlendState::NONE),
	m_depthStencilState(RHI::DepthStencilState::ENABLE_TEST_AND_ENABLE_WRITE),
	m_rasterizeState(RHI::RasterizeState::CULL_NONE),
	m_shaderID(GraphicsShader::NONE_ID)
{
}

/// @brief シェーダーからマテリアルデータを作成
/// @param shader グラフィックスシェーダー
/// @return 成功 TRUE / 失敗 FALSE
bool Material::CreateMaterialData(const GraphicsShader& shader)
{
	auto* pEngine = GetResourceManager()->GetEngine();
	auto* pDevice = pEngine->GetRenderer()->GetDevice();
	auto pRHIShader = shader.GetRHIGraphicsShader();

	// バッファDesc
	RHI::ResourceDesc desc = {};
	desc.bindFlags = 0 | RHI::BindFlags::CONSTANT_BUFFER;
	desc.cpuAccessFlags = 0 | RHI::CPUAccessFlags::WRITE;
	desc.miscFlags = 0;
	desc.usage = RHI::Usage::DYNAMIC;
	desc.buffer.count = 1;

	// シェーダからマテリアルデータを生成
	for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		auto resourceLayout = pRHIShader->GetResourceLayout(stage);

		//--- CBuffer初期化
		for (const auto& cbLayout : pRHIShader->GetCBufferLayoutMap(stage))
		{
			// GPUBuffer確保
			desc.buffer.size = cbLayout.second.m_size;
			auto pBuffer = pDevice->CreateGPUBuffer(desc);

			// 変数データ格納
			for (const auto& var : cbLayout.second.m_variables)
			{
				auto& defaltVar = var.second.defaultVal;
				// 初期化子データがある場合は初期化する
				if (defaltVar.empty())
				{
					std::memset(pBuffer->GetData() + var.second.offset, 0, var.second.size);
				}
				else
				{
					std::memcpy(pBuffer->GetData() + var.second.offset,
						defaltVar.data(), var.second.size);	// 怪しい…
				}
			}

			// GPUBufferデータ
			m_cbufferData[stageIndex][cbLayout.first] = pBuffer;
		}

		//--- テクスチャ初期化
		for (const auto& tex : resourceLayout.m_localResource[static_cast<size_t>(RHI::ShaderResourceType::TEXTURE)])
		{
			m_textureData[stageIndex][tex.second.slot] = Texture::NONE_ID;
		}

		//--- サンプラ
		for (const auto& smp : resourceLayout.m_localResource[static_cast<size_t>(RHI::ShaderResourceType::SAMPLER)])
		{
			m_samplerData[stageIndex][smp.second.slot] = RHI::SamplerState::NONE;
		}
	}
}

//------------------------------------------------------------------------------
// protected methods
//------------------------------------------------------------------------------

/// @brief データ設定
void Material::SetData(const char* name, const void* data, RHI::GraphicsShaderStage stage)
{
	// RHIシェーダー取得
	auto pRHIShader = GetResourceManager();

	// 全ステージ探索
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// 全ステージで同じ名前のデータを更新
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto itr = m_cbufferVariableTable[stageIndex].find(name);

			// 一致したらバッファを更新
			if (m_cbufferVariableTable[stageIndex].end() != itr)
			{
				auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
				std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
			}
		}
	}
	else
	{
		// 指定ステージで検索・更新
		auto stageIndex = static_cast<size_t>(stage);
		auto itr = m_cbufferVariableTable[stageIndex].find(name);

		// 一致したらバッファを更新
		if (m_cbufferVariableTable[stageIndex].end() != itr)
		{
			auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
			std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
		}
	}
}

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief データ取得
void* Material::GetData(const char* name, RHI::GraphicsShaderStage stage)
{
	// 全ステージ探索
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// 全ステージで最小に見つけたデータ
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto itr = m_cbufferVariableTable[stageIndex].find(name);

			// 一致したらバッファを更新
			if (m_cbufferVariableTable[stageIndex].end() != itr)
			{
				auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
				return pBuffer->GetData() + itr->second.offset;
			}
		}
	}
	else
	{
		// 指定ステージで検索・更新
		auto stageIndex = static_cast<size_t>(stage);
		auto itr = m_cbufferVariableTable[stageIndex].find(name);

		// 一致したらバッファを更新
		if (m_cbufferVariableTable[stageIndex].end() != itr)
		{
			auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
			return pBuffer->GetData() + itr->second.offset;
		}
	}
}

/// @brief テクスチャ設定
void Material::SetTexture(const char* name, const Texture::ID textureID, RHI::GraphicsShaderStage stage)
{
	// 全ステージ探索
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// 全ステージで同じ名前のデータを更新
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto itr = m_textureData[stageIndex].find(name);

			// 一致したらテクスチャを格納
			if (m_cbufferVariableTable[stageIndex].end() != itr)
			{
				auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
				std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
			}
		}
	}
	else
	{
		// 指定ステージで検索・更新
		auto stageIndex = static_cast<size_t>(stage);
		auto itr = m_cbufferVariableTable[stageIndex].find(name);

		// 一致したらバッファを更新
		if (m_cbufferVariableTable[stageIndex].end() != itr)
		{
			auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
			std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
		}
	}
}

/// @brief テクスチャ取得
TextureID Material::GetTexture(const char* name, RHI::GraphicsShaderStage stage)
{
	// 検索
	for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		for (const auto& texData : m_textureData[stageIndex])
		{
			if (texData.second.name == name)
			{
				return texData.second.id;
			}
		}
	}
}

/// @brief サンプラ設定
void Material::SetSampler(const char* name, const SamplerState sampler, RHI::GraphicsShaderStage stage)
{
	// 検索
	for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		for (auto& samData : m_samplerData[stageIndex])
		{
			if (samData.second.name == name)
			{
				samData.second.state = sampler;
				return;
			}
		}
	}
}

/// @brief サンプラ取得
SamplerState Material::GetSampler(const char* name, RHI::GraphicsShaderStage stage)
{
	// 検索
	for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		for (auto& samData : m_samplerData[stageIndex])
		{
			if (samData.second.name == name)
			{
				return samData.second.state;
			}
		}
	}
}
