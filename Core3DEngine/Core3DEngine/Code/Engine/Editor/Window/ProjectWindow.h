/*****************************************************************//**
 * \file   ProjectWindow.h
 * \brief  �v���W�F�N�g�E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#ifndef _PROJECT_WINDOW_
#define _PROJECT_WINDOW_

#include <Editor/Core/EditorWindow.h>

namespace Core
{
	class ProjectWindow final : public EditorWindow
	{
		DECLARE_TYPE_INFO(ProjectWindow);
	public:
		/// @brief �R���X�g���N�^
		explicit ProjectWindow() noexcept;

		/// @brief �f�X�g���N�^
		~ProjectWindow() noexcept = default;

		/// @brief GUI�\���R�[���o�b�N
		void OnGUI() final override;

	private:

	};
}

#endif // !_PROJECT_WINDOW_


