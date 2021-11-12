/*****************************************************************//**
 * \file   D3D12_RenderBuffer.h
 * \brief  DirectX12頂点バッファ・インデックスバッファ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/12
 *********************************************************************/
#ifndef _D3D12_RENDER_BUFFER_
#define _D3D12_RENDER_BUFFER_

#include <CoreRenderer/Core/Core_RenderBuffer.h>
#include "D3D12_Defines.h"

namespace d3d12
{
	/// @class D3D12RenderBuffer
	/// @brief DirectX12レンダーバッファ
	class D3D12RenderBuffer final : public core::CoreRenderBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id レンダーバッファID
		/// @param shader シェーダー
		/// @param mesh メッシュ
		explicit D3D12RenderBuffer(ID3D12Device* device, const core::RenderBufferID id, 
			const core::CoreShader& shader, const core::CoreMesh& mesh);

		/// @brief デストラクタ
		~D3D12RenderBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		ComPtr<ID3D12Resource>		m_pVertexBuffer;	///< 頂点バッファ
		ComPtr<ID3D12Resource>		m_pIndexBuffer;		///< インデックスバッファ

		D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView;	///< 頂点バッファビュー
		D3D12_INDEX_BUFFER_VIEW		m_indexBufferVew;	///< インデックスバッファビュー
	};
}

#endif // !_D3D12_RENDER_BUFFER_
