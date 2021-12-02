/*****************************************************************//**
 * \file   GameWindow.h
 * \brief  ゲームウィンドウ
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
		/// @brief コンストラクタ
		explicit GameWindow() noexcept;

		/// @brief デストラクタ
		~GameWindow() noexcept = default;

		/// @brief GUI表示コールバック
		void OnGUI() final override;

	private:

	};
}

#endif // !_GAME_WINDOW_


