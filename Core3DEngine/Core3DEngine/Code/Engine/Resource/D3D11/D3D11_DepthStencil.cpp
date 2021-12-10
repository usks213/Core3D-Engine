/*****************************************************************//**
 * \file   D3D11_DepthStencil.h
 * \brief  DirectX11デプスステンシル
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_DepthStencil.h"
#include <RHI\D3D11\D3D11_CommonState.h>

using namespace Core::D3D11;

/// @brief コンストラクタ
/// @param device デバイス
/// @param id デプスステンシルID
/// @param d3dTex d3dテクスチャ
D3D11DepthStencil::D3D11DepthStencil(ID3D11Device1* device, const Core::DepthStencilID& id, D3D11Texture& d3dTex) :
	Core::CoreDepthStencil(id, d3dTex),
	m_dsv(nullptr)
{
	// 深度ステンシルビュー
	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(D3D11_DSV_DIMENSION_TEXTURE2D, getTypeLessToDSVFormat(d3dTex.m_desc.format));
	if (d3dTex.m_desc.sampleDesc.isUse) dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	// 深度ステンシルビュー読み書き可
	CHECK_FAILED(device->CreateDepthStencilView(
		d3dTex.m_tex.Get(),
		&dsvDesc,
		m_dsv.ReleaseAndGetAddressOf())
	);

}

