/*****************************************************************//**
 * \file   ProjectWindow.h
 * \brief プロジェクトウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "ProjectWindow.h"

#include <Core\Engine.h>
#include <Editor\Core\Editor.h>

using namespace Core;


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
	auto* pEditor = GetEditorWindowManager()->GetEditor();
	auto* pSceneMgr = pEditor->GetEngine()->GetSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;

	// ゲームの描画結果を表示

}
