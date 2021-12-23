/*****************************************************************//**
 * \file   DepthStencil.h
 * \brief  �f�v�X�X�e���V��
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
	/// @brief �[�x�X�e���V��
	class DepthStencil : public Texture
	{
		DECLARE_RESOURCE_INFO(DepthStencil);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		DepthStencil() :
			Texture()
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~DepthStencil() noexcept = default;


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_DEPTH_STENCIL_
