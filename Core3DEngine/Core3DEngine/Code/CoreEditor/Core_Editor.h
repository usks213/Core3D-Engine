/*****************************************************************//**
 * \file   Core_Editor.h
 * \brief  �R�A�G�f�B�^�[
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _CORE_EDITOR_
#define _CORE_EDITOR_

#include "Core/EditorWindowManager.h"

namespace core
{
	class CoreEngine;
	class CoreCommandList;

	/// @brief �R�A�G�f�B�^�[�N���X
	class CoreEditor
	{
	public:
		/// @brief �R���X�g���N�^
		/// @param pEngine �G���W���|�C���^
		explicit CoreEditor() noexcept :
			m_pCoreEngine(nullptr)
		{
			m_pEditorWindowManager = std::make_unique<EditorWindowManager>(this);
		}

		/// @brief �f�X�g���N�^
		virtual ~CoreEditor() noexcept = default;

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
		virtual void Render(CoreCommandList* cmdList) = 0;

		//--- �Q�b�^�[ ---

		/// @brief �G���W���̎擾
		/// @return �G���W���̃|�C���^
		CoreEngine* getCoreEngine() const noexcept { return m_pCoreEngine; }

		/// @brief �G���W���̐ݒ�
		/// @param pCoreEngine �G���W���̃|�C���^
		void setCoreEngine(CoreEngine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief �G�f�B�^�[�E�B���h�E�}�l�[�W���[�擾
		/// @return �G�f�B�^�[�E�B���h�E�}�l�[�W���[�|�C���^
		EditorWindowManager* GetEditorWindowManager() 
		{
			return m_pEditorWindowManager.get();
		}

	private:
		/// @brief �G���W���|�C���^
		CoreEngine* m_pCoreEngine;

		/// @brief �G�f�B�^�[�E�B���h�E�}�l�[�W���[
		std::unique_ptr<EditorWindowManager> m_pEditorWindowManager;

	};
}

#endif // !_CORE_EDITOR_
