/*****************************************************************//**
 * \file   RenderTarget.h
 * \brief  レンダーターゲット
 * 
 * \author USAMI KOSHI
 * \date   2021/12/16
 *********************************************************************/
#ifndef _RENDER_TARGET_
#define _RENDER_TARGET_

#include "Texture.h"
#include <RHI\Core\RHI_RenderTarget.h>

namespace Core
{
	/// @class RenderTarget
	/// @brief レンダーターゲット
	class RenderTarget : public Texture
	{
		DECLARE_RESOURCE_INFO(RenderTarget);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		RenderTarget() :
			Texture()
		{
		}

		/// @brief デストラクタ
		~RenderTarget() noexcept = default;

		/// @brief RHIレンダーターゲット取得
		/// @return レンダーターゲットのスマートポインタ
		std::shared_ptr<RHI::RenderTarget> GetRHIRenderTarget()
		{
			return std::static_pointer_cast<RHI::RenderTarget>(m_pRHITexture);
		}

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_RENDER_TARGET_
