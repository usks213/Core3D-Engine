/*****************************************************************//**
 * \file   Texture.h
 * \brief  �e�N�X�`��
 * 
 * \author USAMI KOSHI
 * \date   2021/12/16
 *********************************************************************/
#ifndef _TEXTURE_
#define _TEXTURE_

#include <Resource\Core\Resource.h>
#include <RHI\Core\RHI_Texture.h>

namespace Core
{
	/// @class Texture
	/// @brief �e�N�X�`��
	class Texture : public Resource
	{
		DECLARE_RESOURCE_INFO(Texture);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		Texture() :
			m_pRHITexture(nullptr)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~Texture() noexcept = default;

		/// @brief RHI�e�N�X�`���̎擾
		/// @return RHI�e�N�X�`���̃X�}�[�g�|�C���^
		std::shared_ptr<RHI::Texture> GetRHITexture()
		{
			return m_pRHITexture;
		}

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		std::shared_ptr<RHI::Texture>	m_pRHITexture;	///< RHI�e�N�X�`��


	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

	};
}

#endif // !_TEXTURE_
