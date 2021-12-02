/*****************************************************************//**
 * \file   ProjectWindow.h
 * \brief �v���W�F�N�g�E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "ProjectWindow.h"

#include <Core\Engine.h>
#include <Editor\Core\Editor.h>

using namespace Core;


 /// @brief �R���X�g���N�^
ProjectWindow::ProjectWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Project");
	SetWindowOpen(true);
	SetWindowFlags(
		ImGuiWindowFlags_NoScrollbar
	);
}

/// @brief GUI�\���R�[���o�b�N
void ProjectWindow::OnGUI()
{
	// ���݃V�[���̎擾
	auto* pEditor = GetEditorWindowManager()->GetEditor();
	auto* pSceneMgr = pEditor->GetEngine()->GetSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;

	// �Q�[���̕`�挋�ʂ�\��

}
