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

		/// @brief �V�F�[�_�[���擾
		/// @return �V�F�[�_�[Desc�̎Q��
		GraphicsShaderDesc& GetDesc() { return m_desc; }

		/// @brief �V�F�[�_�[�C���v�b�g���C�A�E�g���擾
		/// @return �V�F�[�_�[�C���v�b�g���C�A�E�g�̎Q��
		ShaderInputLayout& GetInputLayout() { return m_inputLayout; }

		/// @brief �V�F�[�_�[���\�[�X���C�A�E�g���擾
		/// @param stage �O���t�B�b�N�X�V�F�[�_�[�X�e�[�W
		/// @return �V�F�[�_�[���\�[�X���C�A�E�g�̎Q��
		ShaderResourceLayout& GetResourceLayout(GraphicsShaderStage stage)
		{
			return m_resourceLayout[static_cast<std::size_t>(stage)];
		}

		/// @brief �V�F�[�_�[CBuffer���C�A�E�g�̃}�b�v���擾
		/// @param stage �O���t�B�b�N�X�V�F�[�_�[�X�e�[�W
		/// @return �V�F�[�_�[CBuffer���C�A�E�g�̃}�b�v�̎Q��
		std::vector<ShaderCBufferLayout>& GetCBufferLayoutList(GraphicsShaderStage stage)
		{
			return m_cbufferLayout[static_cast<std::size_t>(stage)];
		}

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
		ShaderInputLayout					m_inputLayout;
		/// @brief ���\�[�X�e�[�u��
		ShaderResourceLayout				m_resourceLayout[static_cast<std::size_t>(GraphicsShaderStage::MAX)];
		/// @brief CBuffer���C�A�E�g
		std::vector<ShaderCBufferLayout>	m_cbufferLayout[static_cast<std::size_t>(GraphicsShaderStage::MAX)];

	};
}

#endif // !_RHI_GRAPHICS_SHADER_
