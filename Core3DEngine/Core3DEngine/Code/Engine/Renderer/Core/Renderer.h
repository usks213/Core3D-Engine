/*****************************************************************//**
 * \file   Renderer.h
 * \brief  �����_���[�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_RENDERER_
#define _CORE_RENDERER_

#include <memory>

namespace Core
{
	// �O�錾
	class Engine;
	class Device;
	class CommandList;

	/// @brief �����_���[�̃x�[�X�N���X
	/// @class Renderer
	class Renderer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit Renderer() :
			m_pCoreEngine(nullptr)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~Renderer() noexcept = default;

		/// @brief �I������
		virtual void finalize() = 0;

		/// @brief �t���[���J�n
		virtual void beginFrame() = 0;
		/// @brief �t���[���I��
		virtual void endFrame() = 0;


		/// @brief �G���W���̎擾
		/// @return �G���W���̃|�C���^
		Engine* GetEngine() const noexcept { return m_pCoreEngine; }

		/// @brief �G���W���̐ݒ�
		/// @param pCoreEngine �G���W���̃|�C���^
		void SetEngine(Engine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief �f�o�C�X�̎擾
		/// @return �f�o�C�X�̃|�C���^
		virtual Device* getDevice() = 0;

		/// @brief �R�}���h���X�g�̎擾
		/// @return �R�}���h���X�g�̃|�C���^
		virtual CommandList* getCommandList() = 0;

		/// @brief �R�s�[�R���X�g���N�^�폜
		Renderer(const Renderer&) = delete;
		/// @brief ���[�u�R���X�g���N�^�폜
		Renderer(Renderer&&) = delete;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		Engine* m_pCoreEngine;	///< �G���W���̃|�C���^

		///< �f�o�C�X�N���X

		///< �R���e�X�g�N���X

	};
}

#endif // !_CORE_RENDERER_
