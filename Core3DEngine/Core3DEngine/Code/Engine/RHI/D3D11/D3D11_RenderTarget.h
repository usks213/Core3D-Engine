/*****************************************************************//**
 * \file   D3D11_RenderTarget.h
 * \brief  DirectX11レンダーターゲット
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _D3D11_RENDER_TARGET_
#define _D3D11_RENDER_TARGET_

#include <RHI/Core/RHI_RenderTarget.h>
#include "D3D11_Texture.h"


namespace Core::RHI::D3D11
{
	/// @class D3D11RenderTarget
	/// @brief DirectX11レンダーターゲット
	class D3D11RenderTarget final : public RenderTarget, public D3D11Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param pDevice デバイス
		/// @param desc テクスチャ情報
		/// @param pData 初期化データ
		explicit D3D11RenderTarget(ID3D11Device1* pDevice, ResourceDesc& desc, const ResourceData* pData = nullptr);

		/// @brief デストラクタ
		~D3D11RenderTarget() noexcept = default;

		/// @brief レンダーターゲットビューの取得
		/// @return 汎用ポインタ
		void* GetRTV() override { return m_rtv.Get(); }

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief D3D11レンダーターゲットビュー
		ComPtr<ID3D11RenderTargetView>		m_rtv;
	};
}

#endif // !_D3D11_RENDER_TARGET_
