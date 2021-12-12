/*****************************************************************//**
 * \file   Material.h
 * \brief  マテリアル
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "Material.h"
using namespace Core;

 /// @brief コンストラクタ
CoreMaterial::CoreMaterial(const MaterialID& id, const std::string& name, const CoreShader& shader) :
	m_id(id),
	m_name(name),
	m_isTransparent(false),
	m_blendState(BlendState::NONE),
	m_depthStencilState(DepthStencilState::ENABLE_TEST_AND_ENABLE_WRITE),
	m_rasterizeState(RasterizeState::CULL_NONE),
	m_shaderID(shader.m_id),
	m_shaderType(shader.m_type),
	m_cbufferCount(0)
{
	// シェーダからマテリアルデータを生成
	for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		//--- CBuffer確保
		auto stageIndex = static_cast<size_t>(stage);
		for (const auto& cbLayout : shader.m_cbufferLayouts[stageIndex])
		{
			auto& cbData = m_cbufferData[stageIndex][cbLayout.first];
			// 名前
			cbData.name = cbLayout.second.name;
			// バッファデータ確保
			cbData.data = std::make_unique<std::byte[]>(cbLayout.second.size);
			// バッファサイズ
			cbData.size = cbLayout.second.size;
			// 更新フラグ
			cbData.isUpdate = true;
			// カウント加算
			++m_cbufferCount;

			// 変数データ格納
			for (const auto& var : cbLayout.second.variables)
			{
				const auto& defaltVar = shader.m_cbufferDefaults.find(var.name);
				// 初期化子データがある場合は初期化する
				if (defaltVar != shader.m_cbufferDefaults.end())
				{
					std::memcpy(cbData.data.get() + var.offset, 
						defaltVar->second.get(), var.size);	// 怪しい…
				}
				else
				{
					std::memset(cbData.data.get() + var.offset, 0, var.size);
				}

				// CBuffer変数データ
				m_cbufferVariable.emplace(var.name, var);
			}
		}

		//--- テクスチャ初期化
		for (const auto& tex : shader.m_dynamicBindData[stageIndex][static_cast<size_t>(BindType::TEXTURE)])
		{
			m_textureData[stageIndex][tex.second.slot].name = tex.second.name;
			m_textureData[stageIndex][tex.second.slot].id = NONE_TEXTURE_ID;
		}

		//--- サンプラ
		for (const auto& smp : shader.m_dynamicBindData[stageIndex][static_cast<size_t>(BindType::SAMPLER)])
		{
			m_samplerData[stageIndex][smp.second.slot].name = smp.second.name;
			m_samplerData[stageIndex][smp.second.slot].state = SamplerState::NONE;
		}
	}
}

/// @brief データ設定
void CoreMaterial::setData(const char* name, const void* data)
{
	for (const auto& var : m_cbufferVariable)
	{
		if (var.second.name == name)
		{
			auto& cbData = m_cbufferData[var.second.stage][var.second.slot];
			std::memcpy(cbData.data.get() + var.second.offset, data, var.second.size);
			cbData.isUpdate = true;
			break;
		}
	}

	//// 検索
	//for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	//{
	//	auto stageIndex = static_cast<size_t>(stage);
	//	for (const auto& cbLayout : m_pShader->m_cbufferLayouts[stageIndex])
	//	{
	//		bool bBreak = false;
	//		// 変数データ
	//		for (const auto& var : cbLayout.second.variables)
	//		{
	//			// 一致した
	//			if (var.name == name)
	//			{
	//				auto& cbData = m_cbufferData[stageIndex][cbLayout.first];
	//				std::memcpy(cbData.data.get() + var.offset, data, var.size);
	//				cbData.isUpdate = true;
	//				bBreak = true;
	//				break;
	//			}
	//		}
	//		if (bBreak) break;
	//	}
	//}
}

/// @brief データ取得
void* CoreMaterial::getData(const char* name)
{
	for (const auto& var : m_cbufferVariable)
	{
		if (var.second.name == name)
		{
			return m_cbufferData[var.second.stage][var.second.slot].data.get() + var.second.offset;
		}
	}

	return nullptr;

	//// 検索
	//for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	//{
	//	auto stageIndex = static_cast<size_t>(stage);
	//	for (const auto& cbLayout : m_pShader->m_cbufferLayouts[stageIndex])
	//	{
	//		bool bBreak = false;
	//		// 変数データ
	//		for (const auto& var : cbLayout.second.variables)
	//		{
	//			// 一致した
	//			if (var.name == name)
	//			{
	//				auto& cbData = m_cbufferData[stageIndex][cbLayout.first];
	//				return cbData.data.get() + var.offset;
	//			}
	//		}
	//		if (bBreak) break;
	//	}
	//}
}

/// @brief テクスチャ設定
void CoreMaterial::setTexture(const char* name, const TextureID textureID)
{
	// 検索
	for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		for (auto& texData : m_textureData[stageIndex])
		{
			if (texData.second.name == name)
			{
				texData.second.id = textureID;
				return;
			}
		}
	}
}

/// @brief テクスチャ取得
TextureID CoreMaterial::getTexture(const char* name)
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
void CoreMaterial::setSampler(const char* name, const SamplerState sampler)
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
SamplerState CoreMaterial::GetSampler(const char* name)
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
