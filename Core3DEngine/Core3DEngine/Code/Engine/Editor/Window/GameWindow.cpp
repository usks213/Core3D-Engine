/*****************************************************************//**
 * \file   GameWindow.h
 * \brief  ゲームウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "GameWindow.h"

#include <Core\Engine.h>
#include <Editor\Core\Editor.h>
#include <Renderer\Core\Device.h>

using namespace Core;

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
	auto* pEditor = GetEditorWindowManager()->GetEditor();
	auto* pSceneMgr = pEditor->GetEngine()->GetSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;
	auto* pDevice = pEditor->GetEngine()->GetRenderer()->getDevice();

	// ゲームの描画結果を表示
	auto resultID = pScene->GetSceneResult();
	auto pResultRT = pDevice->GetRenderTarget(resultID);
	auto pResultTex = pDevice->getTexture(pResultRT->m_texID);
	ImGui::Image((ImTextureID)pResultTex->GetSRV(), ImVec2(16 * 45, 9 * 45));
}
