/*****************************************************************//**
 * \file   GraphicsShader.h
 * \brief  �O���t�B�b�N�X�V�F�[�_�[
 * 
 * \author USAMI KOSHI
 * \date   2021/12/16
 *********************************************************************/
#ifndef _GRAPHICS_SHADER_
#define _GRAPHICS_SHADER_

#include <Resource\Core\Resource.h>
#include <RHI\Core\RHI_GraphicsShader.h>

namespace Core
{
	/// @brief �O���t�B�b�N�X�V�F�[�_�[
	class GraphicsShader : public Resource
	{
		DECLARE_RESOURCE_INFO(GraphicsShader);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		GraphicsShader() :
			m_pRHIGraphicsShader(nullptr)
		{
		}

		/// @brief �f�X�g���N�^
		~GraphicsShader() noexcept = default;

		/// @brief RHI�O���t�B�b�N�X�V�F�[�_�[�̎擾
		/// @return RHI�O���t�B�b�N�X�V�F�[�_�[�̃X�}�[�g�|�C���^
		std::shared_ptr<RHI::GraphicsShader> GetRHIGraphicsShader()
		{
			return m_pRHIGraphicsShader;
		}

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		std::shared_ptr<RHI::GraphicsShader> m_pRHIGraphicsShader;	///< RHI�O���t�B�b�N�X�V�F�[�_�[

	};
}

#endif // !_GRAPHICS_SHADER_
