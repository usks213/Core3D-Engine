/*****************************************************************//**
 * \file   D3D12_Buffer.h
 * \brief  DirectX12Buffer
 *
 * \author USAMI KOSHI
 * \date   2021/10/20
 *********************************************************************/

#include "D3D12_Buffer.h"
using namespace d3d12;

 /// @brief �R���X�g���N�^
 /// @param device �f�o�C�X
 /// @param id �o�b�t�@ID
 /// @param desc �o�b�t�@Desc
 /// @param data �������f�[�^
D3D12Buffer::D3D12Buffer(ID3D12Device* device, const core::BufferID& id, const core::BufferDesc& desc, const core::BufferData* pData) :
	core::CoreBuffer(id, desc),
	m_pHeap(nullptr),
	m_pBuffer(nullptr),
	m_eState(D3D12_RESOURCE_STATE_GENERIC_READ)
{
	// �q�[�v�̍쐬
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;		// �s�[�v�^�C�v
	heapDesc.NumDescriptors = 1;					// �o�b�t�@��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	// �V�F�[�_�[���\�[�X��
	heapDesc.NodeMask = 0;	// ����0
	CHECK_FAILED(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_pHeap.GetAddressOf())));

	// �q�[�v�v���p�e�F�̐ݒ�
	D3D12_HEAP_PROPERTIES prop = {};
	prop.Type = D3D12_HEAP_TYPE_UPLOAD;					// �s�[�v�̃^�C�v
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;	// �y�[�W���O�ݒ�
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;	// �������v�[���ݒ�
	prop.CreationNodeMask = 0;							// ����0
	prop.VisibleNodeMask = 0;								// ����0

	// ���\�[�X�̐ݒ�
	D3D12_RESOURCE_DESC d3dDesc = {};
	d3dDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;	// ���\�[�X�̎��
	d3dDesc.Alignment = 0;								// �z�u�w��H
	d3dDesc.Height = 1;								// �����͂P
	d3dDesc.DepthOrArraySize = 1;								// 3D�̓��\�[�X�̐[���A1D,2D�̔z��͔z��T�C�Y
	d3dDesc.MipLevels = 1;								// �o�b�t�@�͂P
	d3dDesc.Format = DXGI_FORMAT_UNKNOWN;				// �o�b�t�@��UNKNOWN
	d3dDesc.SampleDesc = DXGI_SAMPLE_DESC{ 1, 0 };			// �o�b�t�@�̓f�t�H���g
	d3dDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;	// �Ƃ肠��������I
	d3dDesc.Flags = D3D12_RESOURCE_FLAG_NONE;			// CBuffer�͂Ȃ�

	// CBuffer�̏ꍇ��256�A���C�����g
	auto width = desc.size * desc.count;
	if (desc.bindFlags & core::BindFlags::CONSTANT_BUFFER)
	{
		const UINT64 MAX_SIZE = 256;
		d3dDesc.Width = (width / MAX_SIZE + 1) * MAX_SIZE;
	}
	else
	{
		d3dDesc.Width = width;
	}

	// CPU�f�[�^�쐬
	m_aData.resize(d3dDesc.Width);
	if (pData)
	{
		std::memcpy(m_aData.data(), pData->pInitData, pData->size);
		m_isUpdate = false;
	}

	// ���\�[�X����
	CHECK_FAILED(device->CreateCommittedResource(
		&prop,
		D3D12_HEAP_FLAG_NONE,
		&d3dDesc,
		m_eState,
		nullptr,
		IID_PPV_ARGS(m_pBuffer.GetAddressOf())
	));

	// �����l���
	if (pData)
	{
		void* pBuffer = nullptr;
		CHECK_FAILED(m_pBuffer->Map(0, nullptr, &pBuffer));
		if (pBuffer)
		{
			std::memcpy(pBuffer, pData->pInitData, pData->size);
			m_pBuffer->Unmap(0, nullptr);
		}
	}

	// �r���[�̍쐬
	if (desc.bindFlags & core::BindFlags::CONSTANT_BUFFER)
	{
		// �萔�o�b�t�@�r���[�̍쐬
		m_type = BufferType::CBV;
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = m_pBuffer->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = d3dDesc.Width;
		device->CreateConstantBufferView(&cbvDesc, m_pHeap->GetCPUDescriptorHandleForHeapStart());
	}
	if (desc.bindFlags & core::BindFlags::SHADER_RESOURCE)
	{
		// �V�F�[�_�[���\�[�X�r���[�̍쐬
		m_type = BufferType::SRV;
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.NumElements = desc.count;
		if (desc.miscFlags & core::MiscFlags::BUFFER_STRUCTURED)
		{
			srvDesc.Buffer.StructureByteStride = desc.size;
			srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
		}
		else if (desc.miscFlags & core::MiscFlags::BUFFER_ALLOW_RAW_VIEWS)
		{
			srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;
		}
		device->CreateShaderResourceView(m_pBuffer.Get() ,&srvDesc, 
			m_pHeap->GetCPUDescriptorHandleForHeapStart());
	}
	if (desc.bindFlags & core::BindFlags::UNORDERED_ACCESS)
	{
		// ���s���A�N�Z�X�r���[�̍쐬
		m_type = BufferType::UAV;
		D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;

		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = desc.count;
		if (desc.miscFlags & core::MiscFlags::BUFFER_STRUCTURED)
		{
			uavDesc.Buffer.StructureByteStride = desc.size;
			uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
			// UAV�J�E���^�[
			if(desc.uavFlag == core::BufferUAVFlag::COUNTER)
			{
				uavDesc.Buffer.CounterOffsetInBytes = 0; // �悭�킩��Ȃ��c
			}
		}
		else if (desc.miscFlags & core::MiscFlags::BUFFER_ALLOW_RAW_VIEWS && 
				desc.uavFlag == core::BufferUAVFlag::RAW)
		{
			uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
			uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
		}

		device->CreateUnorderedAccessView(m_pBuffer.Get(), nullptr, &uavDesc, 
			m_pHeap->GetCPUDescriptorHandleForHeapStart());
	}
}
