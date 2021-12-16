/*****************************************************************//**
 * \file   D3D11_RenderTarget.h
 * \brief  DirectX11�����_�[�^�[�Q�b�g
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_RenderTarget.h"
#include "D3D11_CommonState.h"

using namespace Core::RHI::D3D11;


/// @brief �R���X�g���N�^
/// @param pDevice �f�o�C�X
/// @param desc �e�N�X�`�����
/// @param pData �������f�[�^
D3D11RenderTarget::D3D11RenderTarget(ID3D11Device1* pDevice, TextureDesc& desc, const TextureData* pData) :
	m_rtv(nullptr)
{
	// �e�N�X�`���̍쐬
	m_tex.CreateFromDesc(pDevice, desc, pData);

	// �����_���[�^�[�Q�b�g�r���[
	CD3D11_RENDER_TARGET_VIEW_DESC rtvDesc(D3D11_RTV_DIMENSION_TEXTURE2D, GetDXGIFormat(m_desc.format));
	if (m_desc.sampleDesc.isUse) rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	// ����
	CHECK_FAILED(pDevice->CreateRenderTargetView(
		static_cast<ID3D11Resource*>(m_tex.GetResource()),
		&rtvDesc,
		m_rtv.ReleaseAndGetAddressOf())
	);
}
