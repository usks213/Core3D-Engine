/*****************************************************************//**
 * \file   RHI_Texture.h
 * \brief  テクスチャ
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_TEXTURE_
#define _RHI_TEXTURE_

#include "RHI_Resource.h"

namespace Core::RHI
{
	/// @class Texture
	/// @brief テクスチャ
	class Texture : public Resource
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		Texture() : Resource()
		{
		}

		/// @brief デストラクタ
		virtual ~Texture() noexcept = default;

	};
}

#endif // !_RHI_TEXTURE_
