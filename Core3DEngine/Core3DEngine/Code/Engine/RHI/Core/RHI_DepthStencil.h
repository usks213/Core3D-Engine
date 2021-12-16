/*****************************************************************//**
 * \file   RHI_DepthStencil.h
 * \brief  デプスステンシル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_DEPTH_STENCIL_
#define _RHI_DEPTH_STENCIL_

#include "RHI_Texture.h"

namespace Core::RHI
{
	/// @class DepthStencil
	/// @brief 深度ステンシル
	class DepthStencil : public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		DepthStencil() {}

		/// @brief デストラクタ
		virtual ~DepthStencil() noexcept = default;

		/// @brief デプスステンシルビューの取得
		/// @return 汎用ポインタ
		virtual void* GetDSV() = 0;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_RHI_DEPTH_STENCIL_
