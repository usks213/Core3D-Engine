/*****************************************************************//**
 * \file   GameWindow.h
 * \brief  ゲームウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "GameWindow.h"

#include <CoreEditor\Core_Editor.h>
#include <CoreEngine\Core_Engine.h>

 /// @brief コンストラクタ
GameWindow::GameWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Game");
	SetWindowOpen(true);
	SetWindowFlags(
		ImGuiWindowFlags_NoScrollbar
	);
}

/// @brief GUI表示コールバック
void GameWindow::OnGUI()
{
	// 現在シーンの取得
	auto* pEditor = GetEditorWindowManager()->GetCoreEditor();
	auto* pSceneMgr = pEditor->getCoreEngine()->getSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;

	// ゲームの描画結果を表示

}
