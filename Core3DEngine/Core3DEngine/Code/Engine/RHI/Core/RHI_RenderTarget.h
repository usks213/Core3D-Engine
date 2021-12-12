/*****************************************************************//**
 * \file   RHI_RenderTarget.h
 * \brief  レンダーターゲット
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_RENDER_TARGET_
#define _CORE_RENDER_TARGET_

#include "RHI_Texture.h"

namespace Core::RHI
{
	/// @class RenderTarget
	/// @brief レンダーターゲット
	class RenderTarget :public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		RenderTarget() {}

		/// @brief デストラクタ
		virtual ~RenderTarget() noexcept = default;

		/// @brief レンダーターゲットビューの取得
		/// @return 汎用ポインタ
		virtual void* GetRTV() = 0;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_CORE_RENDER_TARGET_
