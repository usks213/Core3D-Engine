/*****************************************************************//**
 * \file   D3D11_DepthStencil.h
 * \brief  DirectX11�f�v�X�X�e���V��
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_DepthStencil.h"
#include "D3D11_CommonState.h"

using namespace Core::RHI::D3D11;

/// @brief �R���X�g���N�^
/// @param pDevice �f�o�C�X
/// @param desc �e�N�X�`�����
/// @param pData �������f�[�^
D3D11DepthStencil::D3D11DepthStencil(ID3D11Device1* pDevice, ResourceDesc& desc, const ResourceData* pData)
{
	// �e�N�X�`���̍쐬
	CreateFromDesc(pDevice, desc, pData);

	// �[�x�X�e���V���r���[
	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(D3D11_DSV_DIMENSION_TEXTURE2D, GetTypeLessToDSVFormat(m_desc.texture.format));
	if (m_desc.texture.sampleDesc.isUse) dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	// �[�x�X�e���V���r���[�ǂݏ�����
	CHECK_FAILED(pDevice->CreateDepthStencilView(
		m_tex.Get(),
		&dsvDesc,
		m_dsv.ReleaseAndGetAddressOf())
	);

}

