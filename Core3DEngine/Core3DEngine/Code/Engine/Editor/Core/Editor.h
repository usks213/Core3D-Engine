/*****************************************************************//**
 * \file   Editor.h
 * \brief  �R�A�G�f�B�^�[
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _CORE_EDITOR_
#define _CORE_EDITOR_

#include "EditorWindowManager.h"

namespace Core
{
	class Engine;
	namespace RHI
	{
		class CommandList;
	}

	/// @brief �R�A�G�f�B�^�[�N���X
	class Editor
	{
	public:
		/// @brief �R���X�g���N�^
		/// @param pEngine �G���W���|�C���^
		explicit Editor() noexcept :
			m_pEngine(nullptr)
		{
			m_pEditorWindowManager = std::make_unique<EditorWindowManager>(this);
		}

		/// @brief �f�X�g���N�^
		virtual ~Editor() noexcept = default;

		/// @brief �X�V����
		void DispEditor()
		{
			/// @brief �E�B���h�E�̕\��
			m_pEditorWindowManager->DispWindow();
		}

		/// @brief �I������
		virtual void finalize() = 0;

		/// @brief �V�����`��t���[���쐬
		virtual void NewFrame() = 0;

		/// @brief �`��
		/// @param cmdList �R�}���h���X�g
		virtual void Render(RHI::CommandList* cmdList) = 0;

		//--- �Q�b�^�[ ---

		/// @brief �G���W���̎擾
		/// @return �G���W���̃|�C���^
		Engine* GetEngine() const noexcept { return m_pEngine; }

		/// @brief �G���W���̐ݒ�
		/// @param pEngine �G���W���̃|�C���^
		void SetEngine(Engine* pEngine) noexcept { m_pEngine = pEngine; }

		/// @brief �G�f�B�^�[�E�B���h�E�}�l�[�W���[�擾
		/// @return �G�f�B�^�[�E�B���h�E�}�l�[�W���[�|�C���^
		EditorWindowManager* GetEditorWindowManager() 
		{
			return m_pEditorWindowManager.get();
		}

	private:
		/// @brief �G���W���|�C���^
		Engine* m_pEngine;

		/// @brief �G�f�B�^�[�E�B���h�E�}�l�[�W���[
		std::unique_ptr<EditorWindowManager> m_pEditorWindowManager;

	};
}

#endif // !_CORE_EDITOR_
