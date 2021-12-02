/*****************************************************************//**
 * \file   D3D12_Texture.h
 * \brief  DirectX12テクスチャ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/14
 *********************************************************************/
#ifndef _D3D12_TEXTURE_
#define _D3D12_TEXTURE_

#include <Resource/Core/Texture.h>
#include <Renderer\D3D12\D3D12_DescriptorPool.h>

namespace Core::D3D12
{
	/// @class D3D12Texture
	/// @brief DirectX12テクスチャ
	class D3D12Texture final : public Core::CoreTexture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ(ファイル読み込み)
		/// @param id テクスチャID
		/// @param filepath ファイルパス
		explicit D3D12Texture(ID3D12Device* pDevice, D3D12DescriptorPool* pDescriptorPool, 
			const Core::TextureID& id, const std::string& filepath);

		/// @brief コンストラクタ(Descから生成)
		/// @param id テクスチャID
		/// @param desc テクスチャDesc
		explicit D3D12Texture(ID3D12Device* pDevice, D3D12DescriptorPool* pDescriptorPool,
			const Core::TextureID& id, Core::TextureDesc& desc,
			const Core::TextureData* pData = nullptr, const D3D12_CLEAR_VALUE* pClear = nullptr);

		/// @brief デストラクタ
		~D3D12Texture() noexcept = default;
		
		/// @brief リソースポインタの取得
		/// @return リソース型
		void* GetResource() override { return m_pTex.Get(); }

		/// @brief SRVポインタの取得
		/// @return SRV型
		void* GetSRV() override { return (void*)m_handle.GPUHandle.ptr; }

		/// @brief UAVポインタの取得
		/// @return UAV型
		void* GetUAV() override { return (void*)m_handle.GPUHandle.ptr; }

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		//ComPtr<ID3D12DescriptorHeap>		m_pTexHeap;	///< ヒープ
		ComPtr<ID3D12Resource>				m_pTex;		///< テクスチャ
		D3D12_RESOURCE_STATES				m_eState;	///< リソースの状態
		D3D12DescriptorHandle				m_handle;	///< ディスクリプタアドレス
	};
}

#endif // !_D3D12_TEXTURE_
