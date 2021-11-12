/*****************************************************************//**
 * \file   D3D12_Material.h
 * \brief  DirectX12マテリアル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/11
 *********************************************************************/
#ifndef _D3D12_MATERIAL_
#define _D3D12_MATERIAL_

#include <CoreRenderer/Core/Core_Material.h>
#include <CoreRenderer/Core/Core_ShaderResource.h>
#include <CoreRenderer/D3D12/D3D12_Defines.h>

namespace d3d12
{
	/// @class D3D12Material
	/// @brief Directx11マテリアル
	class D3D12Material final :public core::CoreMaterial
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id マテリアルID
		/// @param name マテリアル名
		/// @param shader シェーダ
		explicit D3D12Material(ID3D12Device* device, const core::MaterialID& id,
			const std::string& name, core::CoreShader& shader);

		/// @brief デストラクタ
		~D3D12Material() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief 全ステージ、スロット分のヒープ領域
		std::array<ComPtr<ID3D12DescriptorHeap>, 
			static_cast<size_t>(core::ShaderStage::MAX)>	m_pCBufferHeap;

		/// @brief 全ステージ、スロット分のCBufferリソースポインタ
		std::array<std::unordered_map<std::uint32_t, ComPtr<ID3D12Resource>>,
			static_cast<size_t>(core::ShaderStage::MAX)>	m_d3dCbuffer;

	};
}

#endif // !_D3D12_MATERIAL_
