/*****************************************************************//**
 * \file   Core_RenderTarget.h
 * \brief  �����_�[�^�[�Q�b�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_RENDER_TARGET_
#define _CORE_RENDER_TARGET_

#include "Core_Texture.h"

namespace core
{
	/// @brief �����_�[�^�[�Q�b�gID
	enum class RenderTargetID : std::uint32_t {};
	/// @brief ���݂��Ȃ������_�[�^�[�Q�b�gID
	constexpr RenderTargetID NONE_RENDER_TARGET_ID = std::numeric_limits<RenderTargetID>::max();

	/// @class CoreRenderTarget
	/// @brief �����_�[�^�[�Q�b�g
	class CoreRenderTarget
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param id �����_�[�^�[�Q�b�gID
		/// @param texture �e�N�X�`��
		explicit CoreRenderTarget(const RenderTargetID& id, core::CoreTexture& texture) :
			m_id(id), m_name(texture.m_desc.name), m_texID(texture.m_id)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~CoreRenderTarget() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief �����_�[�^�[�Q�b�gID
		RenderTargetID	m_id;
		/// @brief ���O
		std::string		m_name;
		/// @brief �e�N�X�`��ID
		TextureID		m_texID;

	};
}

#endif // !_CORE_RENDER_TARGET_
