/*****************************************************************//**
 * \file   RHI_GraphicsShader.h
 * \brief  �O���t�B�b�N�X�V�F�[�_�[
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RHI_GRAPHICS_SHADER_
#define _RHI_GRAPHICS_SHADER_

#include <limits>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <array>

#include "RHI_ShaderCBufferLayout.h"
#include "RHI_ShaderInputLayout.h"
#include "RHI_ShaderResourceLayout.h"

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace Core::RHI
{
	/// @brief �V�F�[�_�[�����p�\����
	struct GraphicsShaderDesc
	{
		std::uint32_t	m_stages;	// �V�F�[�_�[�X�e�[�W�t���O
		std::string		m_name;		// �V�F�[�_�[��
		// �V�F�[�_�}�N��
	};

	/// @class GraphicsShader
	/// @brief �V�F�[�_
	class GraphicsShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit GraphicsShader(GraphicsShaderDesc shaderDesc) :
			m_desc(shaderDesc)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~GraphicsShader() noexcept = default;


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_�[�������
		GraphicsShaderDesc  m_desc;
		/// @brief �V�F�[�_�[�}�N���̃n�b�V���l


		/// @brief �C���v�b�g���C�A�E�g
		ShaderInputLayout								m_inputLayout;
		/// @brief ���\�[�X�e�[�u��
		ShaderResourceLayout							m_resourceLayout[static_cast<std::size_t>(GraphicsShaderStage::MAX)];
		/// @brief CBuffer���C�A�E�g
		std::unordered_map<Slot, ShaderCBufferLayout>	m_cbufferLayout[static_cast<std::size_t>(GraphicsShaderStage::MAX)];

	};
}

#endif // !_RHI_GRAPHICS_SHADER_
