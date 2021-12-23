/*****************************************************************//**
 * \file   RHI_RenderTarget.h
 * \brief  �����_�[�^�[�Q�b�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_RENDER_TARGET_
#define _RHI_RENDER_TARGET_

#include "RHI_Texture.h"

namespace Core::RHI
{
	/// @class RenderTarget
	/// @brief �����_�[�^�[�Q�b�g
	class RenderTarget : virtual public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		RenderTarget() {}

		/// @brief �f�X�g���N�^
		virtual ~RenderTarget() noexcept = default;

		/// @brief �����_�[�^�[�Q�b�g�r���[�̎擾
		/// @return �ėp�|�C���^
		virtual void* GetRTV() = 0;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_RHI_RENDER_TARGET_
