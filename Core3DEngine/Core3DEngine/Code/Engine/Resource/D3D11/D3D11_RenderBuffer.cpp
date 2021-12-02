/*****************************************************************//**
 * \file   D3D11_RenderBuffer.h
 * \brief  DirectX11描画バッファ
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "D3D11_RenderBuffer.h"
using namespace Core::D3D11;

/// @brief コンストラクタ
/// @param device デバイス
/// @param id レンダーバッファID
/// @param shader シェーダー
/// @param mesh メッシュ
D3D11RenderBuffer::D3D11RenderBuffer(ID3D11Device1* device, const Core::RenderBufferID id, 
	const Core::CoreShader& shader, const Core::CoreMesh& mesh) :
	Core::CoreRenderBuffer(id, shader, mesh)
{
	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA initData = {};

	// 頂点バッファの生成
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = m_vertexData.size * m_vertexData.count;
	initData.pSysMem = m_vertexData.buffer.get();
	CHECK_FAILED(device->CreateBuffer(&desc, &initData, m_vertexBuffer.GetAddressOf()));

	// インデックスの生成
	if (m_indexData.size > 0 && m_indexData.count > 0)
	{
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = m_indexData.size * m_indexData.count;
		initData.pSysMem = mesh.m_indexData.data();
		CHECK_FAILED(device->CreateBuffer(&desc, &initData, m_indexBuffer.GetAddressOf()));
	}
}
