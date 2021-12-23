/*****************************************************************//**
 * \file   DepthStencil.h
 * \brief  デプスステンシル
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _DEPTH_STENCIL_
#define _DEPTH_STENCIL_

#include "Texture.h"

namespace Core
{
	/// @class DepthStencil
	/// @brief 深度ステンシル
	class DepthStencil : public Texture
	{
		DECLARE_RESOURCE_INFO(DepthStencil);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		DepthStencil() :
			Texture()
		{
		}

		/// @brief デストラクタ
		virtual ~DepthStencil() noexcept = default;


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_DEPTH_STENCIL_
