/*****************************************************************//**
 * \file   D3D12_RenderBuffer.h
 * \brief  DirectX12���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@
 *
 * \author USAMI KOSHI
 * \date   2021/10/12
 *********************************************************************/

#include "D3D12_RenderBuffer.h"
using namespace d3d12;

/// @brief �R���X�g���N�^
/// @param device �f�o�C�X
/// @param id �����_�[�o�b�t�@ID
/// @param shader �V�F�[�_�[
/// @param mesh ���b�V��
D3D12RenderBuffer::D3D12RenderBuffer(ID3D12Device* device, const core::RenderBufferID id, 
	const core::CoreShader& shader, const core::CoreMesh& mesh) :
	core::CoreRenderBuffer(id, shader, mesh)
{
	// �q�[�v�v���p�e�F�̐ݒ�
	D3D12_HEAP_PROPERTIES prop = {};
	prop.Type = D3D12_HEAP_TYPE_UPLOAD;						// �s�[�v�̃^�C�v
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;	// �y�[�W���O�ݒ�
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;	// �������v�[���ݒ�
	prop.CreationNodeMask = 0;								// ����1
	prop.VisibleNodeMask = 0;								// ����1

	// ���\�[�X�̐ݒ�
	D3D12_RESOURCE_DESC d3dDesc = {};
	d3dDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;	// ���\�[�X�̎��
	d3dDesc.Alignment = 0;									// �z�u�w��H
	d3dDesc.Width = 0;										// ��Ōʎw��
	d3dDesc.Height = 1;										// �����͂P
	d3dDesc.DepthOrArraySize = 1;							// 3D�̓��\�[�X�̐[���A1D,2D�̔z��͔z��T�C�Y
	d3dDesc.MipLevels = 1;									// �o�b�t�@�͂P
	d3dDesc.Format = DXGI_FORMAT_UNKNOWN;					// �o�b�t�@��UNKNOWN
	d3dDesc.SampleDesc = DXGI_SAMPLE_DESC{ 1, 0 };			// �o�b�t�@�̓f�t�H���g
	d3dDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;		// �Ƃ肠��������I
	d3dDesc.Flags = D3D12_RESOURCE_FLAG_NONE;				// Vertex,Index���Ȃ�

	// ���_�o�b�t�@�̐���
	{
		auto vertexSize = m_vertexData.size * m_vertexData.count;
		d3dDesc.Width = vertexSize;
		CHECK_FAILED(device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&d3dDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_pVertexBuffer.GetAddressOf())
		));

		// �f�[�^�i�[
		void* pVerData = nullptr;
		CHECK_FAILED(m_pVertexBuffer->Map(0, nullptr, &pVerData));
		std::memcpy(pVerData, m_vertexData.buffer.get(), vertexSize);
		m_pVertexBuffer->Unmap(0, nullptr);

		// ���_�o�b�t�@�r���[
		m_vertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes = vertexSize;
		m_vertexBufferView.StrideInBytes = m_vertexData.size;
	}

	// �C���f�b�N�X�̐���
	if (m_indexData.size > 0 && m_indexData.count > 0)
	{
		// �C���f�b�N�X�o�b�t�@�̐���
		auto indexSize = m_indexData.size * m_indexData.count;
		d3dDesc.Width = indexSize;
		CHECK_FAILED(device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&d3dDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_pIndexBuffer.GetAddressOf())
		));

		// �f�[�^�i�[
		void* pVerData = nullptr;
		CHECK_FAILED(m_pIndexBuffer->Map(0, nullptr, &pVerData));
		std::memcpy(pVerData, mesh.m_indexData.data(), indexSize);
		m_pIndexBuffer->Unmap(0, nullptr);

		// �C���f�b�N�X�o�b�t�@�r���[
		m_indexBufferVew.BufferLocation = m_pIndexBuffer->GetGPUVirtualAddress();
		m_indexBufferVew.SizeInBytes = indexSize;
		m_indexBufferVew.Format = DXGI_FORMAT_R32_UINT;
	}
}
