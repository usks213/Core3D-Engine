/*****************************************************************//**
 * \file   InspectorWindow.h
 * \brief  インスペクターウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/25
 *********************************************************************/
#include "InspectorWindow.h"

#include <CoreEditor\Core_Editor.h>
#include <CoreEngine\Core_Engine.h>

 /// @brief コンストラクタ
InspectorWindow::InspectorWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Inspector");
	SetWindowOpen(true);
	SetWindowFlags(
		ImGuiWindowFlags_HorizontalScrollbar
	);
}

/// @brief GUI表示コールバック
void InspectorWindow::OnGUI()
{
	// 現在シーンの取得
	auto* pEditor = GetEditorWindowManager()->GetCoreEditor();
	auto* pSceneMgr = pEditor->getCoreEngine()->getSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;

	auto* pEntityMgr = pScene->GetEntityManager();
	auto* pComponentMgr = pScene->GetComponentManager();
	auto* pTransformMgr = pScene->GetTransformManager();
	
	// 選択中のオブジェクト
	auto selectObject = GetEditorWindowManager()->GetSelectObject();
	switch (selectObject.objectType)
	{
	case EditorWindowManager::SelectObject::Type::Entity:
	{
		auto* pEntity = pEntityMgr->FindEntity(static_cast<EntityID>(selectObject.instanceID));
		if (pEntity == nullptr) break;
		// インスペクター表示
		pEntity->OnInspectorGUI();
		
	}
		break;
	case EditorWindowManager::SelectObject::Type::Resource:
		// リソース情報の表示

		break;
	}
	

}
