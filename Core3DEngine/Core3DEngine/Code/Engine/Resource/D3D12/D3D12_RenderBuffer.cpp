/*****************************************************************//**
 * \file   D3D12_RenderBuffer.h
 * \brief  DirectX12頂点バッファ・インデックスバッファ
 *
 * \author USAMI KOSHI
 * \date   2021/10/12
 *********************************************************************/

#include "D3D12_RenderBuffer.h"
using namespace d3d12;

/// @brief コンストラクタ
/// @param device デバイス
/// @param id レンダーバッファID
/// @param shader シェーダー
/// @param mesh メッシュ
D3D12RenderBuffer::D3D12RenderBuffer(ID3D12Device* device, const core::RenderBufferID id, 
	const core::CoreShader& shader, const core::CoreMesh& mesh) :
	core::CoreRenderBuffer(id, shader, mesh)
{
	// ヒーププロパテェの設定
	D3D12_HEAP_PROPERTIES prop = {};
	prop.Type = D3D12_HEAP_TYPE_UPLOAD;						// ピープのタイプ
	prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;	// ページング設定
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;	// メモリプール設定
	prop.CreationNodeMask = 0;								// 今は1
	prop.VisibleNodeMask = 0;								// 今は1

	// リソースの設定
	D3D12_RESOURCE_DESC d3dDesc = {};
	d3dDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;	// リソースの種別
	d3dDesc.Alignment = 0;									// 配置指定？
	d3dDesc.Width = 0;										// 後で個別指定
	d3dDesc.Height = 1;										// 高さは１
	d3dDesc.DepthOrArraySize = 1;							// 3Dはリソースの深さ、1D,2Dの配列は配列サイズ
	d3dDesc.MipLevels = 1;									// バッファは１
	d3dDesc.Format = DXGI_FORMAT_UNKNOWN;					// バッファはUNKNOWN
	d3dDesc.SampleDesc = DXGI_SAMPLE_DESC{ 1, 0 };			// バッファはデフォルト
	d3dDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;		// とりあえずこれ！
	d3dDesc.Flags = D3D12_RESOURCE_FLAG_NONE;				// Vertex,Indexもなし

	// 頂点バッファの生成
	{
		auto vertexSize = m_vertexData.size * m_vertexData.count;
		d3dDesc.Width = vertexSize;
		CHECK_FAILED(device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&d3dDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_pVertexBuffer.GetAddressOf())
		));

		// データ格納
		void* pVerData = nullptr;
		CHECK_FAILED(m_pVertexBuffer->Map(0, nullptr, &pVerData));
		std::memcpy(pVerData, m_vertexData.buffer.get(), vertexSize);
		m_pVertexBuffer->Unmap(0, nullptr);

		// 頂点バッファビュー
		m_vertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes = vertexSize;
		m_vertexBufferView.StrideInBytes = m_vertexData.size;
	}

	// インデックスの生成
	if (m_indexData.size > 0 && m_indexData.count > 0)
	{
		// インデックスバッファの生成
		auto indexSize = m_indexData.size * m_indexData.count;
		d3dDesc.Width = indexSize;
		CHECK_FAILED(device->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&d3dDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(m_pIndexBuffer.GetAddressOf())
		));

		// データ格納
		void* pVerData = nullptr;
		CHECK_FAILED(m_pIndexBuffer->Map(0, nullptr, &pVerData));
		std::memcpy(pVerData, mesh.m_indexData.data(), indexSize);
		m_pIndexBuffer->Unmap(0, nullptr);

		// インデックスバッファビュー
		m_indexBufferVew.BufferLocation = m_pIndexBuffer->GetGPUVirtualAddress();
		m_indexBufferVew.SizeInBytes = indexSize;
		m_indexBufferVew.Format = DXGI_FORMAT_R32_UINT;
	}
}
