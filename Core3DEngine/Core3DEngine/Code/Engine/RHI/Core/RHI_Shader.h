/*****************************************************************//**
 * \file   RHI_Shader.h
 * \brief  �V�F�[�_�[
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_SHADER_
#define _CORE_SHADER_

#include <limits>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <array>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace Core::RHI
{
	/// @brief �V�F�[�_�[�����p�\����
	struct ShaderDesc
	{
		std::uint32_t	m_stages;	// �V�F�[�_�[�X�e�[�W�t���O
		std::string		m_name;		// �V�F�[�_�[��
		// �V�F�[�_�}�N��
	};

	/// @class Shader
	/// @brief �V�F�[�_
	class Shader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit Shader(ShaderDesc shaderDesc) :
			m_desc(shaderDesc)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~Shader() noexcept = default;

	public:


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_�[�������
		ShaderDesc  m_desc;
		/// @brief �}�N���̃n�b�V���l

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------


	};
}

#endif // !_CORE_SHADER_
