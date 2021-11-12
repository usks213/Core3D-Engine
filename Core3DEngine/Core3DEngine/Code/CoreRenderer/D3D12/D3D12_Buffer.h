/*****************************************************************//**
 * \file   D3D12_Buffer.h
 * \brief  DirectX12Buffer
 * 
 * \author USAMI KOSHI
 * \date   2021/10/20
 *********************************************************************/
#ifndef _D3D12_Buffer_
#define _D3D12_Buffer_

#include <CoreRenderer/Core/Core_Buffer.h>
#include <CoreRenderer/D3D12/D3D12_Defines.h>

namespace d3d12
{
	/// @class D3D12Buffer
	/// @brief DirectX12バッファ-
	class D3D12Buffer final : public core::CoreBuffer
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
		explicit D3D12Buffer(ID3D12Device* device, const core::BufferID& id, 
			const core::BufferDesc& desc, const core::BufferData* pData = nullptr);

		/// @brief デストラクタ
		~D3D12Buffer() noexcept = default;

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
