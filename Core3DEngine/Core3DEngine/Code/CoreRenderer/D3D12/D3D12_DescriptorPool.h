/*****************************************************************//**
 * \file   D3D12_DescriptorPool.h
 * \brief  DirectX12�f�B�X�N���v�^�v�[��
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
	/// @brief DirectX12�f�X�g���N�^�A�h���X
	struct D3D12DescriptorHandle
	{
		D3D12_CPU_DESCRIPTOR_HANDLE CPUHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE GPUHandle;
	};

	/// @brief DirectX12�f�B�X�N���v�^�v�[��
	class D3D12DescriptorPool
	{
	public:
		/// @brief �R���X�g���N�^
		/// @param pDevice D3D12�f�o�C�X
		/// @param type �q�[�v�^�C�v
		/// @param maxDespCount �ő�f�B�X�N���v�^��
		explicit D3D12DescriptorPool(ID3D12Device* pDevice, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT maxDespCount);

		/// @brief �f�X�g���N�^
		~D3D12DescriptorPool() noexcept = default;

		/// @brief �v�[�����烁�����m��
		/// @return �f�B�X�N���v�^�A�h���X
		D3D12DescriptorHandle Allocate();

		/// @brief �f�B�X�N���v�^�q�[�v�擾
		/// @return DirectX�f�B�X�N���v�^�q�[�v
		ID3D12DescriptorHeap* GetDescriptorHeap() { return m_pHeap.Get(); }

	private:
		ComPtr<ID3D12DescriptorHeap>	m_pHeap;
		std::atomic<UINT32>				m_curCount;
		UINT							m_maxCount;
		UINT							m_typeSize;
	};
}

#endif // !_D3D12_DESCRIPTOR_POOL_

