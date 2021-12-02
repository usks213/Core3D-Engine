/*****************************************************************//**
 * \file   GameWindow.h
 * \brief  �Q�[���E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#ifndef _GAME_WINDOW_
#define _GAME_WINDOW_

#include <Editor/Core/EditorWindow.h>

namespace Core
{
	class GameWindow final : public EditorWindow
	{
		DECLARE_TYPE_INFO(GameWindow);
	public:
		/// @brief �R���X�g���N�^
		explicit GameWindow() noexcept;

		/// @brief �f�X�g���N�^
		~GameWindow() noexcept = default;

		/// @brief GUI�\���R�[���o�b�N
		void OnGUI() final override;

	private:

	};
}

#endif // !_GAME_WINDOW_


