/*****************************************************************//**
 * \file   HierarchyWindow.h
 * \brief  ヒエラルキーウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#include "HierarchyWindow.h"

using namespace Core;


 /// @brief コンストラクタ
HierarchyWindow::HierarchyWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Hierarchy");
	SetWindowOpen(true);
	SetWindowFlags(
		WindowFlag::ImGuiWindowFlags_HorizontalScrollbar
	);
}

/// @brief GUI表示コールバック
void HierarchyWindow::OnGUI()
{
	// 現在シーンの取得
	auto* pSceneMgr = GetEditorWindowManager()->GetEditor()->GetEngine()->GetSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;
	auto* pTransformManager = pScene->GetTransformManager();

	// ルートへ戻すボタン
	ImGui::Button("Return Root", ImVec2(200, 30));
	if (ImGui::BeginDragDropTarget()) {
		// Some processing...
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(TransformID));
			TransformID payload_n = *(const TransformID*)payload->Data;
			// 親子関係再構築
			auto* pTransform = pTransformManager->FindTransform(payload_n);
			if (pTransform) pTransform->ReturnRoot();
		}
		ImGui::EndDragDropTarget();
	}

	// シーンの階層構造を取得
	auto& rootList = pTransformManager->GetRootTransforms();
	for (const auto& parent : rootList)
	{
		DispEntity(pScene->GetTransformManager(), parent);
	}
}

void HierarchyWindow::DispEntity(TransformManager* pTransformManager, const TransformID& parentID)
{
	// 親の取得
	auto* pTransform = pTransformManager->FindTransform(parentID);
	if (pTransform == nullptr) return;
	auto* pEntity = pTransform->entity();
	if (pEntity == nullptr) return;
	int id = static_cast<int>(pTransform->GetInstanceID());
	auto selectObject = GetEditorWindowManager()->GetSelectObject();

	// 子ノードがあるか
	ImGui::PushID(id++);
	bool open = ImGui::TreeNodeEx(pEntity->GetName().data(),
		ImGuiTreeNodeFlags_FramePadding |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		(pTransform->GetChildCount() ? 0 : ImGuiTreeNodeFlags_Leaf) | 
		(selectObject.objectType == EditorWindowManager::SelectObject::Type::Entity && 
		 selectObject.instanceID == pEntity->GetInstanceID() ? ImGuiTreeNodeFlags_Selected : 0)
	);
	ImGui::PopID();

	// ドラッグ時
	ImGui::PushID(id++);
	if (ImGui::BeginPopupContextItem()) {
		// Some processing...
		ImGui::Text("Move Parent");
		ImGui::EndPopup();
	}
	ImGui::PopID();
	// クリック
	if (ImGui::IsItemClicked()) {
		// 選択IDを格納
		GetEditorWindowManager()->SetSelectObject(
			EditorWindowManager::SelectObject::Type::Entity, pEntity->GetInstanceID());
	}
	// ドロップ
	if (ImGui::BeginDragDropTarget()) {
		// Some processing...
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(TransformID));
			TransformID payload_n = *(const TransformID*)payload->Data;
			// 親子関係再構築
			auto* pDrop = pTransformManager->FindTransform(payload_n);
			if (pDrop) pTransform->AddChild(payload_n);
		}
		ImGui::EndDragDropTarget();
	}
	// ドラッグ
	if (ImGui::BeginDragDropSource()) {
		// Some processing...
		TransformID id = pTransform->GetTransformID();
		ImGui::SetDragDropPayload("DND_DEMO_CELL", &id, sizeof(TransformID));
		ImGui::Text("Move Parent");
		ImGui::EndDragDropSource();
	}
	// ノード内
	if (open) {
		// 子の表示
		for (const auto& child : pTransform->GetChildList())
		{
			DispEntity(pTransformManager, child);
		}
		ImGui::TreePop();
	}
}
