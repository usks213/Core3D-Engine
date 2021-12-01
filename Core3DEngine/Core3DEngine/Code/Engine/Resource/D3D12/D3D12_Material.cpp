/*****************************************************************//**
 * \file   D3D12_Material.h
 * \brief  DirectX12�}�e���A��
 *
 * \author USAMI KOSHI
 * \date   2021/10/11
 *********************************************************************/

#include "D3D12_Material.h"
#include "D3D12_Shader.h"
using namespace d3d12;


namespace
{
	constexpr D3D12_SHADER_VISIBILITY SHADER_VISIBILITYS[static_cast<size_t>(core::ShaderStage::CS)] = {
		D3D12_SHADER_VISIBILITY_VERTEX,
		D3D12_SHADER_VISIBILITY_HULL,
		D3D12_SHADER_VISIBILITY_DOMAIN,
		D3D12_SHADER_VISIBILITY_GEOMETRY,
		D3D12_SHADER_VISIBILITY_PIXEL,
	};
}

/// @brief �R���X�g���N�^
/// @param device �f�o�C�X
/// @param id �}�e���A��ID
/// @param name �}�e���A����
/// @param shader �V�F�[�_
D3D12Material::D3D12Material(ID3D12Device* device, const core::MaterialID& id,
	const std::string& name, core::CoreShader& shader) :
	core::CoreMaterial(id,name,shader)
{
	// �R���X�^���g�o�b�t�@�̊m��(GPU)
	for (core::ShaderStage stage = core::ShaderStage::VS; stage < core::ShaderStage::CS; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		if (m_cbufferData[stageIndex].size() <= 0)
		{
			continue;
		}

		// �q�[�v�̍쐬
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;		// �s�[�v�^�C�v
		heapDesc.NumDescriptors = static_cast<UINT>(m_cbufferData[stageIndex].size());					// �o�b�t�@��
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	// �V�F�[�_�[���\�[�X��
		heapDesc.NodeMask = 0;	// ����0
		CHECK_FAILED(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(m_pCBufferHeap[stageIndex].GetAddressOf())));

		// �q�[�v�v���p�e�F�̐ݒ�
		D3D12_HEAP_PROPERTIES prop = {};
		prop.Type = D3D12_HEAP_TYPE_UPLOAD;			// �s�[�v�̃^�C�v
		prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;	// �y�[�W���O�ݒ�
		prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;		// �������v�[���ݒ�
		prop.CreationNodeMask = 0;								// ����1
		prop.VisibleNodeMask = 0;								// ����1

		// ���\�[�X�̐ݒ�
		D3D12_RESOURCE_DESC d3dDesc = {};
		d3dDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;	// ���\�[�X�̎��
		d3dDesc.Alignment = 0;								// �z�u�w��H
		d3dDesc.Width = 0;								// ��Ōʎw��
		d3dDesc.Height = 1;								// �����͂P
		d3dDesc.DepthOrArraySize = 1;								// 3D�̓��\�[�X�̐[���A1D,2D�̔z��͔z��T�C�Y
		d3dDesc.MipLevels = 1;								// �o�b�t�@�͂P
		d3dDesc.Format = DXGI_FORMAT_UNKNOWN;				// �o�b�t�@��UNKNOWN
		d3dDesc.SampleDesc = DXGI_SAMPLE_DESC{ 1, 0 };			// �o�b�t�@�̓f�t�H���g
		d3dDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;	// �Ƃ肠��������I
		d3dDesc.Flags = D3D12_RESOURCE_FLAG_NONE;			// CBuffer�͂Ȃ�

		// �q�[�v�n���h��
		auto handle = m_pCBufferHeap[stageIndex]->GetCPUDescriptorHandleForHeapStart();
		auto cbufferIncreSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		//--- CBuffer�m��
		for (auto& cbData : m_cbufferData[stageIndex])
		{
			// CBuffer�T�C�Y
			d3dDesc.Width	= (cbData.second.size % 256 + 1) * 256;
			// ���\�[�X����
			CHECK_FAILED(device->CreateCommittedResource(
				&prop,
				D3D12_HEAP_FLAG_NONE,
				&d3dDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(m_d3dCbuffer[stageIndex][cbData.first].GetAddressOf())
			));
			// �����̃f�[�^�i�[�Ȃ�
			cbData.second.isUpdate = true;

			// �萔�o�b�t�@�r���[�̍쐬
			D3D12_CONSTANT_BUFFER_VIEW_DESC cbufferDesc = {};
			cbufferDesc.BufferLocation = m_d3dCbuffer[stageIndex][cbData.first]->GetGPUVirtualAddress();
			cbufferDesc.SizeInBytes = (cbData.second.size % 256 + 1) * 256;
			device->CreateConstantBufferView(&cbufferDesc, handle);

			// �n���h���|�C���^���Z
			handle.ptr += cbufferIncreSize;

		}
	}
}
