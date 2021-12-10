/*****************************************************************//**
 * \file   D3D12_DepthStencil.h
 * \brief  DirectX12デプスステンシル
 *
 * \author USAMI KOSHI
 * \date   2021/10/18
 *********************************************************************/

#include "D3D12_DepthStencil.h"
#include <RHI\D3D12\D3D12_CommonState.h>

using namespace Core::D3D12;

/// @brief コンストラクタ
/// @param device デバイス
/// @param id デプスステンシルID
/// @param d3dTex d3dテクスチャ
D3D12DepthStencil::D3D12DepthStencil(ID3D12Device* device, const Core::DepthStencilID& id, D3D12Texture& d3dTex) :
	Core::CoreDepthStencil(id, d3dTex),
	m_pHeapDSV(nullptr)
{
	//深度のためのデスクリプタヒープ作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};//深度に使うよという事がわかればいい
	dsvHeapDesc.NumDescriptors = 1;//深度ビュー1つのみ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//デプスステンシルビューとして使う
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_pHeapDSV.ReleaseAndGetAddressOf()));

	//深度ビュー作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = Core::D3D12::getTypeLessToDSVFormat(d3dTex.m_desc.format); //デプス値に32bit使用
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;//フラグは特になし

	// MSAA
	if(d3dTex.m_desc.sampleDesc.isUse) dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;

	device->CreateDepthStencilView(d3dTex.m_pTex.Get(), &dsvDesc,
		m_pHeapDSV->GetCPUDescriptorHandleForHeapStart());

}

