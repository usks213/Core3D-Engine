/*****************************************************************//**
 * \file   D3D11_DepthStencil.h
 * \brief  DirectX11デプスステンシル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_DEPTH_STENCIL_
#define _D3D11_DEPTH_STENCIL_

#include <CoreRenderer/Core/Core_DepthStencil.h>
#include "D3D11_Texture.h"

namespace d3d11
{
	/// @class D3D11DepthStencil
	/// @brief DreictX11深度ステンシル
	class D3D11DepthStencil final : public core::CoreDepthStencil
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param device デバイス
		/// @param id デプスステンシルID
		/// @param d3dTex d3dテクスチャ
		explicit D3D11DepthStencil(ID3D11Device1* device, const core::DepthStencilID& id, D3D11Texture& d3dTex);

		/// @brief デストラクタ
		~D3D11DepthStencil() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief D3D11深度ステンシルビュー
		ComPtr<ID3D11DepthStencilView>		m_dsv;
	};
}

#endif // !_D3D11_DEPTH_STENCIL_
