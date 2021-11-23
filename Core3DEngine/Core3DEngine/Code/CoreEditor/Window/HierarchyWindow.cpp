/*****************************************************************//**
 * \file   HierarchyWindow.h
 * \brief  ヒエラルキーウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#include "HierarchyWindow.h"


 /// @brief コンストラクタ
HierarchyWindow::HierarchyWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("ヒエラルキー");
	SetWindowOpen(true);
	SetWindowFlags(
		WindowFlags::ImGuiWindowFlags_HorizontalScrollbar
	);
}

/// @brief GUI表示コールバック
void HierarchyWindow::OnGUI()
{
	// 現在シーンの取得

}
