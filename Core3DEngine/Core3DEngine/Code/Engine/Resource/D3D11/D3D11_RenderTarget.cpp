/*****************************************************************//**
 * \file   D3D11_RenderTarget.h
 * \brief  DirectX11�����_�[�^�[�Q�b�g
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_RenderTarget.h"
#include "D3D11_CommonState.h"
using namespace d3d11;


/// @brief �R���X�g���N�^
/// @param device �f�o�C�X
/// @param d3dTex d3d�e�N�X�`��
D3D11RenderTarget::D3D11RenderTarget(ID3D11Device1* device, const core::RenderTargetID& id, D3D11Texture& d3dTex) :
	core::CoreRenderTarget(id, d3dTex),
	m_rtv(nullptr)
{
	// �����_���[�^�[�Q�b�g�r���[
	CD3D11_RENDER_TARGET_VIEW_DESC rtvDesc(D3D11_RTV_DIMENSION_TEXTURE2D, getDXGIFormat(d3dTex.m_desc.format));
	if (d3dTex.m_desc.sampleDesc.isUse) rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	// ����
	CHECK_FAILED(device->CreateRenderTargetView(
		d3dTex.m_tex.Get(),
		&rtvDesc,
		m_rtv.ReleaseAndGetAddressOf())
	);
}
