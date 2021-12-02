/*****************************************************************//**
 * \file   EditorWindow.h
 * \brief  �G�f�B�^�[�E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _EDITOR_WINDOW_
#define _EDITOR_WINDOW_

#include <Core/TypeHash.h>
#include <ImGui/imgui.h>

namespace Core
{

	class EditorWindowManager;

	/// @brief �G�f�B�^�[�E�B���h�E
	class EditorWindow
	{
	public:
		friend class EditorWindowManager;
		using WindowFlags = ImGuiWindowFlags;	///< ImGui�E�B���h�E�t���O
		using WindowFlag = ImGuiWindowFlags_;	///< ImGui�E�B���h�E�t���O
	public:

		/// @brief �R���X�g���N�^
		explicit EditorWindow() noexcept;

		/// @brief �f�X�g���N�^
		virtual ~EditorWindow() noexcept = default;

		/// @brief �E�B���h�E�̕\��
		void DispWindow();

		/// @brief GUI�\���R�[���o�b�N
		virtual void OnGUI() = 0;


		//----- �Q�b�^�[�E�Z�b�^�[ -----

		/// @brief �G�f�B�^�[�E�B���h�E�}�l�[�W���[�̎擾
		/// @return �G�f�B�^�[�E�B���h�E�}�l�[�W���[�̃|�C���^
		EditorWindowManager* GetEditorWindowManager() const noexcept
		{
			return m_pManager;
		}

		/// @brief �E�B���h�E�̕\���w��
		/// @param isDisp �\���t���O
		void SetWindowDisp(bool isDisp) noexcept { m_isDisp = isDisp; }
		/// @brief �E�B���h�E�̕\���t���O�̎擾
		/// @return �\���t���O
		bool GetWinodwDisp() const noexcept { return m_isDisp; }

		/// @brief �E�B���h�E���̎w��
		/// @param name �E�B���h�E��
		void SetWindowName(std::string_view name) noexcept { m_name = name; }
		/// @brief �E�B���h�E���̎擾
		/// @return �E�B���h�E��
		std::string_view GetWindowName() const noexcept { return m_name; }

		/// @brief �E�B���h�E�J�w��
		/// @param isOpne �J�t���O
		void SetWindowOpen(bool isOpne) noexcept { m_isOpne = isOpne; }
		/// @brief �E�B���h�E�J�t���O�̎擾
		/// @return �J�t���O
		bool GetWindowOpen() const noexcept { return m_isOpne; }

		/// @brief �E�B���h�E�t���O�̎擾
		/// @param flags �E�B���h�E�t���O
		void SetWindowFlags(WindowFlags flags) noexcept { m_flags = flags; }
		/// @brief �E�B���h�E�t���O�̎擾
		/// @return �E�B���h�E�t���O
		WindowFlags GetWindowFlags() const noexcept { return m_flags; }

	private:
		EditorWindowManager* m_pManager;

		bool			m_isDisp;		///< �\���t���O

		std::string		m_name;			///< �E�B���h�E��
		bool			m_isOpne;		///< �J�t���O
		WindowFlags		m_flags;		///< �E�B���h�E�t���O

		ImVec2			m_size;			///< �E�B���h�E�̃T�C�Y
		ImVec2			m_pos;			///< �E�B���h�E�̍��W
	};
}

#endif // !_EDITOR_WINDOW_

