/*****************************************************************//**
 * \file   D3D12_DescriptorPool.h
 * \brief  DirectX12ディスクリプタプール
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _D3D12_DESCRIPTOR_POOL_
#define _D3D12_DESCRIPTOR_POOL_

#include "D3D12_Defines.h"
#include <atomic>

namespace d3d12
{
	/// @brief DirectX12デストラクタアドレス
	struct D3D12DescriptorHandle
	{
		D3D12_CPU_DESCRIPTOR_HANDLE CPUHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE GPUHandle;
	};

	/// @brief DirectX12ディスクリプタプール
	class D3D12DescriptorPool
	{
	public:
		/// @brief コンストラクタ
		/// @param pDevice D3D12デバイス
		/// @param type ヒープタイプ
		/// @param maxDespCount 最大ディスクリプタ数
		explicit D3D12DescriptorPool(ID3D12Device* pDevice, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT maxDespCount);

		/// @brief デストラクタ
		~D3D12DescriptorPool() noexcept = default;

		/// @brief プールからメモリ確保
		/// @return ディスクリプタアドレス
		D3D12DescriptorHandle Allocate();

		/// @brief ディスクリプタヒープ取得
		/// @return DirectXディスクリプタヒープ
		ID3D12DescriptorHeap* GetDescriptorHeap() { return m_pHeap.Get(); }

	private:
		ComPtr<ID3D12DescriptorHeap>	m_pHeap;
		std::atomic<UINT32>				m_curCount;
		UINT							m_maxCount;
		UINT							m_typeSize;
	};
}

#endif // !_D3D12_DESCRIPTOR_POOL_

