/*****************************************************************//**
 * \file   InspectorWindow.h
 * \brief  �C���X�y�N�^�[�E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/25
 *********************************************************************/
#include "InspectorWindow.h"

#include <Editor\Core\Editor.h>
#include <Core\Engine.h>

using namespace Core;

 /// @brief �R���X�g���N�^
InspectorWindow::InspectorWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Inspector");
	SetWindowOpen(true);
	SetWindowFlags(
		ImGuiWindowFlags_HorizontalScrollbar
	);
}

/// @brief GUI�\���R�[���o�b�N
void InspectorWindow::OnGUI()
{
	// ���݃V�[���̎擾
	auto* pEditor = GetEditorWindowManager()->GetEditor();
	auto* pSceneMgr = pEditor->GetEngine()->GetSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;

	auto* pEntityMgr = pScene->GetEntityManager();
	auto* pComponentMgr = pScene->GetComponentManager();
	auto* pTransformMgr = pScene->GetTransformManager();
	
	// �I�𒆂̃I�u�W�F�N�g
	auto selectObject = GetEditorWindowManager()->GetSelectObject();
	switch (selectObject.objectType)
	{
	case EditorWindowManager::SelectObject::Type::Entity:
	{
		auto* pEntity = pEntityMgr->FindEntity(static_cast<EntityID>(selectObject.instanceID));
		if (pEntity == nullptr) break;
		// �C���X�y�N�^�[�\��
		pEntity->OnInspectorGUI();
		
	}
		break;
	case EditorWindowManager::SelectObject::Type::Resource:
		// ���\�[�X���̕\��

		break;
	}
	

}
