/*****************************************************************//**
 * \file   RHI_RenderTarget.h
 * \brief  �����_�[�^�[�Q�b�g
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
	/// @brief �����_�[�^�[�Q�b�g
	class RenderTarget :public Texture
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^(�t�@�C���ǂݍ���)
		/// @param id �e�N�X�`��ID
		/// @param filepath �t�@�C���p�X
		explicit RenderTarget(const std::string& filepath) :
			Texture(filepath)
		{}

		/// @brief �R���X�g���N�^(Desc���琶��)
		/// @param id �e�N�X�`��ID
		/// @param desc �e�N�X�`��Desc
		explicit RenderTarget(TextureDesc& desc, const TextureData* pData = nullptr) :
			Texture(desc, pData)
		{}

		/// @brief �f�X�g���N�^
		virtual ~RenderTarget() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_CORE_RENDER_TARGET_
