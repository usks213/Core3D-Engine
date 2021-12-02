/*****************************************************************//**
 * \file   Component.h
 * \brief  コンポーネント
 *
 * \author USAMI KOSHI
 * \date   2021/11/25
 *********************************************************************/
#include "Component.h"

#include "Scene.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "TransformManager.h"

#include "ImGui\imgui.h"

using namespace Core;

 /// @brief 親エンティティの取得
 /// @return エンティティポインタ
Entity* Component::entity() noexcept
{
	return m_pComponentManager->GetScene()->GetEntityManager()->FindEntity(m_entityID);
}

/// @brief トランスフォームの取得
/// @return トランスフォームポインタ
Transform* Component::transform() noexcept
{
	auto* pEntity = entity();
	if (pEntity == nullptr) return nullptr;

	return m_pComponentManager->GetScene()->GetTransformManager()->FindTransform(pEntity->m_transformID);
}

/// @brief 使用フラグ指定
/// @param isEnable フラグ
void Component::SetEnable(bool isEnable) noexcept
{

}

/// @brief コンポーネント名の取得(スクリプト継承先も)
/// @return コンポーネント名
std::string_view Component::GetComponentName() noexcept
{
	return GetTypeName();
}

/// @brief インスペクター表示の開始
/// @return ノードが開いているか
bool Component::BeginInspectorGUI()
{
	// コンポーネントのヘッダー情報表示
	int id = static_cast<int>(GetInstanceID());
	ImGui::PushID(id++);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
	bool isOpen = ImGui::TreeNodeEx("",
		ImGuiTreeNodeFlags_FramePadding |
		ImGuiTreeNodeFlags_DefaultOpen | 
		ImGuiTreeNodeFlags_OpenOnDoubleClick
	);
	ImGui::PopStyleVar();
	ImGui::PopID();

	// 使用フラグ
	ImGui::SameLine();
	ImGui::PushID(id++);
	ImGui::Checkbox("", &m_isEnable);
	ImGui::PopID();

	// コンポーネント名
	ImGui::SameLine();
	ImGui::PushID(id++);
	ImGui::Text(GetComponentName().data());
	ImGui::PopID();


	return isOpen;
}

/// @brief インスペクター表示の終了
void Component::EndInspectorGUI()
{
	// ノード終了
	ImGui::TreePop();
}
