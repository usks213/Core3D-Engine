/*****************************************************************//**
 * \file   D3D12_DescriptorPool.h
 * \brief  DirectX12�f�B�X�N���v�^�v�[��
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#include "D3D12_DescriptorPool.h"
using namespace d3d12;


 /// @brief �R���X�g���N�^
 /// @param pDevice D3D12�f�o�C�X
 /// @param type �q�[�v�^�C�v
 /// @param maxDespCount �ő�f�B�X�N���v�^��
D3D12DescriptorPool::D3D12DescriptorPool(ID3D12Device* pDevice, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT maxDespCount):
	m_pHeap(nullptr),
	m_curCount(0),
	m_maxCount(maxDespCount),
	m_typeSize(pDevice->GetDescriptorHandleIncrementSize(type))
{
	// �q�[�v�m��
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = m_maxCount;
	heapDesc.Type = type;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	CHECK_FAILED(pDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_pHeap)));
}


/// @brief �v�[�����烁�����m��
/// @return �f�B�X�N���v�^�A�h���X
D3D12DescriptorHandle D3D12DescriptorPool::Allocate()
{
	D3D12DescriptorHandle address;
	m_curCount.fetch_add(1);
	address.CPUHandle.ptr = m_pHeap->GetCPUDescriptorHandleForHeapStart().ptr + m_curCount.load() * m_typeSize;
	address.GPUHandle.ptr = m_pHeap->GetGPUDescriptorHandleForHeapStart().ptr + m_curCount.load() * m_typeSize;
	return address;
}
