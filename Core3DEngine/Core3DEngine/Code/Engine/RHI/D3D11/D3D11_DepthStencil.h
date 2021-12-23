/*****************************************************************//**
 * \file   D3D11_DepthStencil.h
 * \brief  DirectX11デプスステンシル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_DEPTH_STENCIL_
#define _D3D11_DEPTH_STENCIL_

#include <RHI/Core/RHI_DepthStencil.h>
#include "D3D11_Texture.h"
#include <memory>

namespace Core::RHI::D3D11
{
	/// @class D3D11DepthStencil
	/// @brief DreictX11深度ステンシル
	class D3D11DepthStencil final : public DepthStencil, public D3D11Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param pDevice デバイス
		/// @param desc テクスチャ情報
		/// @param pData 初期化データ
		explicit D3D11DepthStencil(ID3D11Device1* pDevice, ResourceDesc& desc, const ResourceData* pData = nullptr);

		/// @brief デストラクタ
		~D3D11DepthStencil() noexcept = default;

		/// @brief デプスステンシルビューの取得
		/// @return 汎用ポインタ
		void* GetDSV() override { return m_dsv.Get(); }

	protected:
		//------------------------------------------------------------------------------
		// public variables 
		//------------------------------------------------------------------------------

		/// @brief D3D11深度ステンシルビュー
		ComPtr<ID3D11DepthStencilView>		m_dsv;
	};
}

#endif // !_D3D11_DEPTH_STENCIL_
