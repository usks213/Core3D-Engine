/*****************************************************************//**
 * \file   D3D11_RenderBuffer.h
 * \brief  DirectX11描画バッファ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_RENDER_BUFFER_
#define _D3D11_RENDER_BUFFER_

#include <CoreRenderer/Core/Core_RenderBuffer.h>
#include "D3D11_Defines.h"

namespace d3d11
{
	/// @class D3D11RenderBuffer
	/// @brief DirectX11レンダーバッファ
	class D3D11RenderBuffer final : public core::CoreRenderBuffer
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
		explicit D3D11RenderBuffer(ID3D11Device1* device, const core::RenderBufferID id, 
			const core::CoreShader& shader, const core::CoreMesh& mesh);

		/// @brief デストラクタ
		~D3D11RenderBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		ComPtr<ID3D11Buffer> m_vertexBuffer;	///< 頂点バッファ
		ComPtr<ID3D11Buffer> m_indexBuffer;		///< インデックスバッファ
	};
}

#endif // !_D3D11_RENDER_BUFFER_
