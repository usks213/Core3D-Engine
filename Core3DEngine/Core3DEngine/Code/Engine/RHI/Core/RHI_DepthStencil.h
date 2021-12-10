/*****************************************************************//**
 * \file   RHI_DepthStencil.h
 * \brief  �f�v�X�X�e���V��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_DEPTH_STENCIL_
#define _CORE_DEPTH_STENCIL_

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

		/// @brief �R���X�g���N�^(�t�@�C���ǂݍ���)
		/// @param id �e�N�X�`��ID
		/// @param filepath �t�@�C���p�X
		explicit DepthStencil(const std::string& filepath) :
			Texture(filepath)
		{}

		/// @brief �R���X�g���N�^(Desc���琶��)
		/// @param id �e�N�X�`��ID
		/// @param desc �e�N�X�`��Desc
		explicit DepthStencil(TextureDesc& desc, const TextureData* pData = nullptr) : 
			Texture(desc, pData)
		{}

		/// @brief �f�X�g���N�^
		virtual ~DepthStencil() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_CORE_DEPTH_STENCIL_
