/*****************************************************************//**
 * \file   Core_DepthStencil.h
 * \brief  �f�v�X�X�e���V��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_DEPTH_STENCIL_
#define _CORE_DEPTH_STENCIL_

#include "Core_Texture.h"

namespace core
{
	/// @brief �[�x�X�e���V��ID
	enum class DepthStencilID : std::uint32_t {};
	/// @brief ���݂��Ȃ��[�x�X�e���V��ID
	constexpr DepthStencilID NONE_DEPTH_STENCIL_ID = std::numeric_limits<DepthStencilID>::max();

	/// @class CoreDepthStencil
	/// @brief �[�x�X�e���V��
	class CoreDepthStencil
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param id �[�x�X�e���V��ID
		/// @param texture �e�N�X�`��
		explicit CoreDepthStencil(const DepthStencilID& id, CoreTexture& texture) :
			m_id(id), m_name(texture.m_desc.name), m_texID(texture.m_id)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~CoreDepthStencil() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		DepthStencilID	m_id;		///< �[�x�X�e���V��ID
		std::string		m_name;		///< ���O
		TextureID		m_texID;	///< �e�N�X�`��ID

	};
}

#endif // !_CORE_DEPTH_STENCIL_
