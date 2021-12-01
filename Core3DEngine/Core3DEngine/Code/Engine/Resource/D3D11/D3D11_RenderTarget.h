/*****************************************************************//**
 * \file   D3D11_RenderTarget.h
 * \brief  DirectX11レンダーターゲット
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_RENDER_TARGET_
#define _D3D11_RENDER_TARGET_

#include <CoreRenderer/Core/Core_RenderTarget.h>
#include "D3D11_Texture.h"


namespace d3d11
{
	/// @class D3D11RenderTarget
	/// @brief DirectX11レンダーターゲット
	class D3D11RenderTarget final : public core::CoreRenderTarget
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id レンダーターゲットID
		/// @param d3dTex d3dテクスチャ
		explicit D3D11RenderTarget(ID3D11Device1* device, const core::RenderTargetID& id, D3D11Texture& d3dTex);

		/// @brief デストラクタ
		~D3D11RenderTarget() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief D3D11レンダーターゲットビュー
		ComPtr<ID3D11RenderTargetView>		m_rtv;
	};
}

#endif // !_D3D11_RENDER_TARGET_
