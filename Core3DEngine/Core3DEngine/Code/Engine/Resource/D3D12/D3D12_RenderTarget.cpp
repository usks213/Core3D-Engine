/*****************************************************************//**
 * \file   D3D12_RenderTarget.h
 * \brief  DierectX12�����_�[�^�[�Q�b�g
 *
 * \author USAMI KOSHI
 * \date   2021/10/18
 *********************************************************************/

#include "D3D12_RenderTarget.h"
#include "D3D12_CommonState.h"
using namespace d3d12;


/// @brief �R���X�g���N�^
/// @param device �f�o�C�X
/// @param d3dTex d3d�e�N�X�`��
D3D12RenderTarget::D3D12RenderTarget(ID3D12Device* device, const core::RenderTargetID& id, D3D12Texture& d3dTex) :
	core::CoreRenderTarget(id, d3dTex),
	m_pHeapRTV(nullptr)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// �s�[�v�^�C�v
	desc.NumDescriptors = 1;		// �o�b�t�@��
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// �V�F�[�_�[���\�[�X��
	desc.NodeMask = 0;

	CHECK_FAILED(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_pHeapRTV.ReleaseAndGetAddressOf())));

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = d3d12::getDXGIFormat(d3dTex.m_desc.format);
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;	// MSAA off

	// MSAA
	if (d3dTex.m_desc.sampleDesc.isUse) rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;

	// �����_�[�^�[�Q�b�g�r���[�̐���
	device->CreateRenderTargetView(d3dTex.m_pTex.Get(), &rtvDesc, 
		m_pHeapRTV->GetCPUDescriptorHandleForHeapStart());

}
