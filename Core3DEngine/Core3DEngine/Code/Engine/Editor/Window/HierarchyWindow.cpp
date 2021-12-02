/*****************************************************************//**
 * \file   HierarchyWindow.h
 * \brief  �q�G�����L�[�E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#include "HierarchyWindow.h"

using namespace Core;


 /// @brief �R���X�g���N�^
HierarchyWindow::HierarchyWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Hierarchy");
	SetWindowOpen(true);
	SetWindowFlags(
		WindowFlag::ImGuiWindowFlags_HorizontalScrollbar
	);
}

/// @brief GUI�\���R�[���o�b�N
void HierarchyWindow::OnGUI()
{
	// ���݃V�[���̎擾
	auto* pSceneMgr = GetEditorWindowManager()->GetEditor()->GetEngine()->GetSceneManager();
	auto* pScene = pSceneMgr->GetCurrentScene();
	if (pScene == nullptr) return;
	auto* pTransformManager = pScene->GetTransformManager();

	// ���[�g�֖߂��{�^��
	ImGui::Button("Return Root", ImVec2(200, 30));
	if (ImGui::BeginDragDropTarget()) {
		// Some processing...
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(TransformID));
			TransformID payload_n = *(const TransformID*)payload->Data;
			// �e�q�֌W�č\�z
			auto* pTransform = pTransformManager->FindTransform(payload_n);
			if (pTransform) pTransform->ReturnRoot();
		}
		ImGui::EndDragDropTarget();
	}

	// �V�[���̊K�w�\�����擾
	auto& rootList = pTransformManager->GetRootTransforms();
	for (const auto& parent : rootList)
	{
		DispEntity(pScene->GetTransformManager(), parent);
	}
}

void HierarchyWindow::DispEntity(TransformManager* pTransformManager, const TransformID& parentID)
{
	// �e�̎擾
	auto* pTransform = pTransformManager->FindTransform(parentID);
	if (pTransform == nullptr) return;
	auto* pEntity = pTransform->entity();
	if (pEntity == nullptr) return;
	int id = static_cast<int>(pTransform->GetInstanceID());
	auto selectObject = GetEditorWindowManager()->GetSelectObject();

	// �q�m�[�h�����邩
	ImGui::PushID(id++);
	bool open = ImGui::TreeNodeEx(pEntity->GetName().data(),
		ImGuiTreeNodeFlags_FramePadding |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		(pTransform->GetChildCount() ? 0 : ImGuiTreeNodeFlags_Leaf) | 
		(selectObject.objectType == EditorWindowManager::SelectObject::Type::Entity && 
		 selectObject.instanceID == pEntity->GetInstanceID() ? ImGuiTreeNodeFlags_Selected : 0)
	);
	ImGui::PopID();

	// �h���b�O��
	ImGui::PushID(id++);
	if (ImGui::BeginPopupContextItem()) {
		// Some processing...
		ImGui::Text("Move Parent");
		ImGui::EndPopup();
	}
	ImGui::PopID();
	// �N���b�N
	if (ImGui::IsItemClicked()) {
		// �I��ID���i�[
		GetEditorWindowManager()->SetSelectObject(
			EditorWindowManager::SelectObject::Type::Entity, pEntity->GetInstanceID());
	}
	// �h���b�v
	if (ImGui::BeginDragDropTarget()) {
		// Some processing...
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
		{
			IM_ASSERT(payload->DataSize == sizeof(TransformID));
			TransformID payload_n = *(const TransformID*)payload->Data;
			// �e�q�֌W�č\�z
			auto* pDrop = pTransformManager->FindTransform(payload_n);
			if (pDrop) pTransform->AddChild(payload_n);
		}
		ImGui::EndDragDropTarget();
	}
	// �h���b�O
	if (ImGui::BeginDragDropSource()) {
		// Some processing...
		TransformID id = pTransform->GetTransformID();
		ImGui::SetDragDropPayload("DND_DEMO_CELL", &id, sizeof(TransformID));
		ImGui::Text("Move Parent");
		ImGui::EndDragDropSource();
	}
	// �m�[�h��
	if (open) {
		// �q�̕\��
		for (const auto& child : pTransform->GetChildList())
		{
			DispEntity(pTransformManager, child);
		}
		ImGui::TreePop();
	}
}
