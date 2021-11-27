/*****************************************************************//**
 * \file   D3D12_Texture.h
 * \brief  DirectX12テクスチャ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/14
 *********************************************************************/
#ifndef _D3D12_TEXTURE_
#define _D3D12_TEXTURE_

#include <CoreRenderer/Core/Core_Texture.h>
#include "D3D12_Defines.h"

namespace d3d12
{
	/// @class D3D12Texture
	/// @brief DirectX12テクスチャ
	class D3D12Texture final : public core::CoreTexture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ(ファイル読み込み)
		/// @param id テクスチャID
		/// @param filepath ファイルパス
		explicit D3D12Texture(ID3D12Device* pDevice, const core::TextureID& id, const std::string& filepath);

		/// @brief コンストラクタ(Descから生成)
		/// @param id テクスチャID
		/// @param desc テクスチャDesc
		explicit D3D12Texture(ID3D12Device* pDevice, const core::TextureID& id, core::TextureDesc& desc,
			const core::TextureData* pData = nullptr, const D3D12_CLEAR_VALUE* pClear = nullptr);

		/// @brief デストラクタ
		~D3D12Texture() noexcept = default;
		
		/// @brief リソースポインタの取得
		/// @return リソース型
		void* GetResource() override { return m_pTex.Get(); }

		/// @brief SRVポインタの取得
		/// @return SRV型
		void* GetSRV() override { return (void*)m_GPUHandle.ptr; }

		/// @brief UAVポインタの取得
		/// @return UAV型
		void* GetUAV() override { return (void*)m_GPUHandle.ptr; }

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		ComPtr<ID3D12DescriptorHeap>		m_pTexHeap;	///< ヒープ
		ComPtr<ID3D12Resource>				m_pTex;		///< テクスチャ
		D3D12_RESOURCE_STATES				m_eState;	///< リソースの状態
		D3D12_CPU_DESCRIPTOR_HANDLE			m_CPUHandle;	///< CPUハンドル
		D3D12_GPU_DESCRIPTOR_HANDLE			m_GPUHandle;	///< GPUハンドル
	};
}

#endif // !_D3D12_TEXTURE_
