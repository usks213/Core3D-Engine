/*****************************************************************//**
 * \file   RHI_ShaderResourceLayout.h
 * \brief  シェーダーリソースレイアウト
 *
 * \author USAMI KOSHI
 * \date   2021/12/10
 *********************************************************************/
#ifndef RHI_SHADER_RESOURCE_LAYOUT_
#define RHI_SHADER_RESOURCE_LAYOUT_

#include "RHI_ShaderUtil.h"
#include "RHI_CommonState.h"
#include <unordered_map>
#include <memory>

namespace Core::RHI
{
	class ShaderResourceLayout
	{
	public:
		ShaderResourceLayout();
		~ShaderResourceLayout();

		/// @brief シェーダーリソースバインド情報
		struct ShaderResoureData
		{
			//std::string			name;
			//ShaderResourceType	type;
			Slot		slot		= 0;
			Space		space		= 0;
			RootIndex	rootIndex	= 0;
		};

	public:
		//--- シェーダーリソースバインド情報(ディスクリプタ) ---

		/// @brief ローカルリソースバインド情報
		std::unordered_map<std::string, ShaderResoureData> m_localResource[static_cast<size_t>(ShaderResourceType::MAX)];

		/// @brief グローバルリソースバインド情報
		std::unordered_map<std::string, ShaderResoureData> m_globalResource[static_cast<size_t>(ShaderResourceType::MAX)];

	};

	//class ConstantBuffer;
	//class GPUBuffer;
	//class Texture;

	//class ShaderResourceTable
	//{
	//public:
	//	ShaderResourceTable();
	//	~ShaderResourceTable();

	//	bool SetConstantBuffer(GraphicsShaderStage stage, std::string_view name, std::shared_ptr<ConstantBuffer> constantBuffer);

	//	bool SetGPUBuffer(GraphicsShaderStage stage, std::string_view name, std::shared_ptr<GPUBuffer> gupBuffer);

	//	bool SetTexture(GraphicsShaderStage stage, std::string_view name, std::shared_ptr<Texture> texture);

	//	bool SetSampler(GraphicsShaderStage stage, std::string_view name, SamplerState samplerState);

	//private:

	//	// テーブルレイアウト
	//	ShaderResourceLayout									m_layout;
	//	// コンスタントバッファの配列
	//	std::unordered_map<Slot, std::shared_ptr<ConstantBuffer>>	m_ConstantBuffers[static_cast<size_t>(GraphicsShaderStage::MAX)];
	//	// GPUバッファの配列
	//	std::unordered_map<Slot, std::shared_ptr<GPUBuffer>>		m_GPUBuffers[static_cast<size_t>(GraphicsShaderStage::MAX)];
	//	// テクスチャの配列
	//	std::unordered_map<Slot, std::shared_ptr<Texture>>			m_Textures[static_cast<size_t>(GraphicsShaderStage::MAX)];
	//	// サンプラーの配列
	//	std::unordered_map<Slot, SamplerState>						m_Samplers[static_cast<size_t>(GraphicsShaderStage::MAX)];

	//};
}

#endif // !RHI_SHADER_RESOURCE_LAYOUT_


