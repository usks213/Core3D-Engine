/*****************************************************************//**
 * \file   D3D12_DescriptorPool.h
 * \brief  DirectX12ディスクリプタプール
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#include "D3D12_DescriptorPool.h"
using namespace d3d12;


 /// @brief コンストラクタ
 /// @param pDevice D3D12デバイス
 /// @param type ヒープタイプ
 /// @param maxDespCount 最大ディスクリプタ数
D3D12DescriptorPool::D3D12DescriptorPool(ID3D12Device* pDevice, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT maxDespCount):
	m_pHeap(nullptr),
	m_curCount(0),
	m_maxCount(maxDespCount),
	m_typeSize(pDevice->GetDescriptorHandleIncrementSize(type))
{
	// ヒープ確保
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = m_maxCount;
	heapDesc.Type = type;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	CHECK_FAILED(pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_pHeap)));
}


/// @brief プールからメモリ確保
/// @return ディスクリプタアドレス
D3D12DescriptorHandle D3D12DescriptorPool::Allocate()
{
	D3D12DescriptorHandle address;
	m_curCount.fetch_add(1);
	address.CPUHandle.ptr = m_pHeap->GetCPUDescriptorHandleForHeapStart().ptr + m_curCount.load() * m_typeSize;
	address.GPUHandle.ptr = m_pHeap->GetGPUDescriptorHandleForHeapStart().ptr + m_curCount.load() * m_typeSize;
	return address;
}
