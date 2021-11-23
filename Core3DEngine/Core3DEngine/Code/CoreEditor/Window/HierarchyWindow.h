/*****************************************************************//**
 * \file   HierarchyWindow.h
 * \brief  ヒエラルキーウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _HIERARCHY_WINDOW_
#define _HIERARCHY_WINDOW_

#include <CoreEditor/Core/EditorWindow.h>

class HierarchyWindow final : public EditorWindow
{
public:
	/// @brief コンストラクタ
	explicit HierarchyWindow() noexcept;

	/// @brief デストラクタ
	~HierarchyWindow() noexcept = default;

	/// @brief GUI表示コールバック
	void OnGUI() final override;

private:

};


#endif // !_HIERARCHY_WINDOW_

