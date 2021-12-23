/*****************************************************************//**
 * \file   D3D11_DepthStencil.h
 * \brief  DirectX11デプスステンシル
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_DepthStencil.h"
#include "D3D11_CommonState.h"

using namespace Core::RHI::D3D11;

/// @brief コンストラクタ
/// @param pDevice デバイス
/// @param desc テクスチャ情報
/// @param pData 初期化データ
D3D11DepthStencil::D3D11DepthStencil(ID3D11Device1* pDevice, ResourceDesc& desc, const ResourceData* pData)
{
	// テクスチャの作成
	CreateFromDesc(pDevice, desc, pData);

	// 深度ステンシルビュー
	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(D3D11_DSV_DIMENSION_TEXTURE2D, GetTypeLessToDSVFormat(m_desc.texture.format));
	if (m_desc.texture.sampleDesc.isUse) dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	// 深度ステンシルビュー読み書き可
	CHECK_FAILED(pDevice->CreateDepthStencilView(
		m_tex.Get(),
		&dsvDesc,
		m_dsv.ReleaseAndGetAddressOf())
	);

}

