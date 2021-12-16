/*****************************************************************//**
 * \file   RenderTarget.h
 * \brief  �����_�[�^�[�Q�b�g
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
	/// @brief �����_�[�^�[�Q�b�g
	class RenderTarget : public Texture
	{
		DECLARE_RESOURCE_INFO(RenderTarget);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		RenderTarget() :
			Texture()
		{
		}

		/// @brief �f�X�g���N�^
		~RenderTarget() noexcept = default;

		/// @brief RHI�����_�[�^�[�Q�b�g�擾
		/// @return �����_�[�^�[�Q�b�g�̃X�}�[�g�|�C���^
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
