/*****************************************************************//**
 * \file   D3D12_DepthStencil.h
 * \brief  DirectX12�f�v�X�X�e���V��
 *
 * \author USAMI KOSHI
 * \date   2021/10/18
 *********************************************************************/

#include "D3D12_DepthStencil.h"
#include "D3D12_CommonState.h"
using namespace d3d12;

/// @brief �R���X�g���N�^
/// @param device �f�o�C�X
/// @param id �f�v�X�X�e���V��ID
/// @param d3dTex d3d�e�N�X�`��
D3D12DepthStencil::D3D12DepthStencil(ID3D12Device* device, const core::DepthStencilID& id, D3D12Texture& d3dTex) :
	core::CoreDepthStencil(id, d3dTex),
	m_pHeapDSV(nullptr)
{
	//�[�x�̂��߂̃f�X�N���v�^�q�[�v�쐬
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};//�[�x�Ɏg����Ƃ��������킩��΂���
	dsvHeapDesc.NumDescriptors = 1;//�[�x�r���[1�̂�
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//�f�v�X�X�e���V���r���[�Ƃ��Ďg��
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_pHeapDSV.ReleaseAndGetAddressOf()));

	//�[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = d3d12::getTypeLessToDSVFormat(d3dTex.m_desc.format); //�f�v�X�l��32bit�g�p
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;//�t���O�͓��ɂȂ�

	// MSAA
	if(d3dTex.m_desc.sampleDesc.isUse) dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;

	device->CreateDepthStencilView(d3dTex.m_pTex.Get(), &dsvDesc,
		m_pHeapDSV->GetCPUDescriptorHandleForHeapStart());

}

