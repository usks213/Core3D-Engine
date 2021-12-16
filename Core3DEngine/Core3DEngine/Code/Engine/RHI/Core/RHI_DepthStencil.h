/*****************************************************************//**
 * \file   RHI_DepthStencil.h
 * \brief  �f�v�X�X�e���V��
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
	/// @brief �[�x�X�e���V��
	class DepthStencil : public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		DepthStencil() {}

		/// @brief �f�X�g���N�^
		virtual ~DepthStencil() noexcept = default;

		/// @brief �f�v�X�X�e���V���r���[�̎擾
		/// @return �ėp�|�C���^
		virtual void* GetDSV() = 0;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_RHI_DEPTH_STENCIL_
