/*****************************************************************//**
 * \file   ProjectWindow.h
 * \brief プロジェクトウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "ProjectWindow.h"

#include <CoreEditor\Core_Editor.h>
#include <CoreEngine\Core_Engine.h>

 /// @brief コンストラクタ
ProjectWindow::ProjectWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Project");
	SetWindowOpen(true);
	SetWindowFlags(
		ImGuiWindowFlags_NoScrollbar
	);
}

/// @brief GUI表示コールバック
void ProjectWindow::OnGUI()
{
	// 現在シーンの取得
	auto* pEditor = GetEditorWindowManager()->GetCoreEditor();
	auto* pSceneMgr = pEditor->getCoreEngine()->getSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;

	// ゲームの描画結果を表示

}
