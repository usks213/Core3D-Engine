/*****************************************************************//**
 * \file   D3D11_DepthStencil.h
 * \brief  DirectX11�f�v�X�X�e���V��
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_DepthStencil.h"
#include "D3D11_CommonState.h"
using namespace d3d11;

/// @brief �R���X�g���N�^
/// @param device �f�o�C�X
/// @param id �f�v�X�X�e���V��ID
/// @param d3dTex d3d�e�N�X�`��
D3D11DepthStencil::D3D11DepthStencil(ID3D11Device1* device, const core::DepthStencilID& id, D3D11Texture& d3dTex) :
	core::CoreDepthStencil(id, d3dTex),
	m_dsv(nullptr)
{
	// �[�x�X�e���V���r���[
	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(D3D11_DSV_DIMENSION_TEXTURE2D, getTypeLessToDSVFormat(d3dTex.m_desc.format));
	if (d3dTex.m_desc.sampleDesc.isUse) dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	// �[�x�X�e���V���r���[�ǂݏ�����
	CHECK_FAILED(device->CreateDepthStencilView(
		d3dTex.m_tex.Get(),
		&dsvDesc,
		m_dsv.ReleaseAndGetAddressOf())
	);

}

