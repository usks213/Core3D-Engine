/*****************************************************************//**
 * \file   D3D12_GPUBuffer.h
 * \brief  DirectX12Buffer
 * 
 * \author USAMI KOSHI
 * \date   2021/10/20
 *********************************************************************/
#ifndef _D3D12_Buffer_
#define _D3D12_Buffer_

#include <Resource/Core/GPUBuffer.h>
#include <RHI/D3D12/D3D12_Defines.h>

namespace Core::D3D12
{
	/// @class D3D12GPUBuffer
	/// @brief DirectX12バッファ-
	class D3D12GPUBuffer final : public Core::GPUBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id バッファID
		/// @param desc バッファDesc
		/// @param data 初期化データ
		explicit D3D12GPUBuffer(ID3D12Device* device, const Core::GPUBufferID& id, 
			const Core::GPUBufferDesc& desc, const Core::GPUBufferData* pData = nullptr);

		/// @brief デストラクタ
		~D3D12GPUBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief ディスクリプタヒープ
		ComPtr<ID3D12DescriptorHeap>	m_pHeap;
		/// @brief バッファリソース
		ComPtr<ID3D12Resource>		m_pBuffer;
		/// @brief リソースの状態
		D3D12_RESOURCE_STATES			m_eState;
	};
}

#endif // !_D3D12_Buffer_
