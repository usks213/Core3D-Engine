/*****************************************************************//**
 * \file   GameWindow.h
 * \brief  �Q�[���E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "GameWindow.h"

#include <CoreEditor\Core_Editor.h>
#include <CoreEngine\Core_Engine.h>
#include <CoreRenderer\Core\Core_Device.h>


 /// @brief �R���X�g���N�^
GameWindow::GameWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Game");
	SetWindowOpen(true);
	SetWindowFlags(
		ImGuiWindowFlags_NoScrollbar
	);
}

/// @brief GUI�\���R�[���o�b�N
void GameWindow::OnGUI()
{
	// ���݃V�[���̎擾
	auto* pEditor = GetEditorWindowManager()->GetCoreEditor();
	auto* pSceneMgr = pEditor->getCoreEngine()->getSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;
	auto* pDevice = pEditor->getCoreEngine()->getRenderer()->getDevice();

	// �Q�[���̕`�挋�ʂ�\��
	auto resultID = pScene->GetSceneResult();
	auto pResultRT = pDevice->getRenderTarget(resultID);
	auto pResultTex = pDevice->getTexture(pResultRT->m_texID);
	ImGui::Image((ImTextureID)pResultTex->GetSRV(), ImVec2(16 * 45, 9 * 45));
}
