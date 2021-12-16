/*****************************************************************//**
 * \file   D3D12_RenderTarget.h
 * \brief  DierectX12レンダーターゲット
 *
 * \author USAMI KOSHI
 * \date   2021/10/18
 *********************************************************************/

#include "D3D12_RenderTarget.h"
#include <RHI\D3D12\D3D12_CommonState.h>
using namespace Core::D3D12;


/// @brief コンストラクタ
/// @param device デバイス
/// @param d3dTex d3dテクスチャ
D3D12RenderTarget::D3D12RenderTarget(ID3D12Device* device, const Core::RenderTargetID& id, D3D12Texture& d3dTex) :
	Core::CoreRenderTarget(id, d3dTex),
	m_pHeapRTV(nullptr)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// ピープタイプ
	desc.NumDescriptors = 1;		// バッファ数
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// シェーダーリソースか
	desc.NodeMask = 0;

	CHECK_FAILED(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_pHeapRTV.ReleaseAndGetAddressOf())));

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = Core::D3D12::GetDXGIFormat(d3dTex.m_desc.format);
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;	// MSAA off

	// MSAA
	if (d3dTex.m_desc.sampleDesc.isUse) rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;

	// レンダーターゲットビューの生成
	device->CreateRenderTargetView(d3dTex.m_pTex.Get(), &rtvDesc, 
		m_pHeapRTV->GetCPUDescriptorHandleForHeapStart());

}
