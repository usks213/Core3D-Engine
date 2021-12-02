/*****************************************************************//**
 * \file   ProjectWindow.h
 * \brief  プロジェクトウィンドウ
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
		/// @brief コンストラクタ
		explicit ProjectWindow() noexcept;

		/// @brief デストラクタ
		~ProjectWindow() noexcept = default;

		/// @brief GUI表示コールバック
		void OnGUI() final override;

	private:

	};
}

#endif // !_PROJECT_WINDOW_


