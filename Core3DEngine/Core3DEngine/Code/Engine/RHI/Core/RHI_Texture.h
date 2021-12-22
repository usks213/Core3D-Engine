/*****************************************************************//**
 * \file   RHI_Texture.h
 * \brief  �e�N�X�`��
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
	/// @brief �e�N�X�`��
	class Texture : public Resource
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		Texture() : Resource()
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~Texture() noexcept = default;

	};
}

#endif // !_RHI_TEXTURE_
