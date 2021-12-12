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
	class D3D11RenderTarget final : public RenderTarget
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param pDevice デバイス
		/// @param desc テクスチャ情報
		/// @param pData 初期化データ
		explicit D3D11RenderTarget(ID3D11Device1* pDevice, TextureDesc& desc, const TextureData* pData = nullptr);

		/// @brief デストラクタ
		~D3D11RenderTarget() noexcept = default;

		/// @brief リソースポインタの取得
		/// @return リソース型
		void* GetResource() override { return m_tex.GetResource(); }

		/// @brief SRVポインタの取得
		/// @return SRV型
		void* GetSRV() override { return m_tex.GetSRV(); }

		/// @brief UAVポインタの取得
		/// @return UAV型
		void* GetUAV() override { return m_tex.GetUAV(); }

		/// @brief レンダーターゲットビューの取得
		/// @return 汎用ポインタ
		void* GetRTV() override { return m_rtv.Get(); }

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief D3D11テクスチャ
		D3D11Texture						m_tex;

		/// @brief D3D11レンダーターゲットビュー
		ComPtr<ID3D11RenderTargetView>		m_rtv;
	};
}

#endif // !_D3D11_RENDER_TARGET_
