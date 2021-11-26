/*****************************************************************//**
 * \file   Entity.h
 * \brief  エンティティ
 *
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#include "Entity.h"

#include "EntityManager.h"
#include "TransformManager.h"

#include "ImGui\imgui.h"


 /// @brief アクティブ指定
 /// @param isActive フラグ
void Entity::SetActive(bool isActive)
{
	//--- Enable更新

	// トランスフォーム

	// コンポーネント

	// スクリプト
}

/// @brief スタティック指定
/// @param isStatic フラグ
void Entity::SetStatic(bool isStatic)
{
	//--- Static更新

	// トランスフォーム

}

 /// @brief トランスフォームの取得
 /// @return トランスフォームポインタ
Transform* Entity::transform() noexcept
{
	TransformManager* pTransformManager = m_pEntityManager->GetTransformManager();
	return pTransformManager->FindTransform(m_transformID);
}

/// @brief インスペクター表示
void Entity::DispInspector() noexcept
{
	int id = static_cast<int>(GetInstanceID());

	ImGui::BeginGroup();

	// アクティブ
	ImGui::PushID(id++);
	if (ImGui::Checkbox("Active", &m_isActive))
	{
		SetActive(m_isActive);
	}
	ImGui::PopID();

	// スタティック
	ImGui::SameLine();
	ImGui::PushID(id++);
	if (ImGui::Checkbox("Static", &m_isStatic))
	{
		SetStatic(m_isStatic);
	}
	ImGui::PopID();

	// 名前
	{
		char szName[128] = {};
		std::memcpy(szName, m_name.data(), m_name.size());
		ImGui::PushID(id++);
		ImGui::PushItemWidth(100);
		if (ImGui::InputText("Name", szName, 128, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			m_name = szName;
		}
		ImGui::PopID();
	}

	// タグ
	{
		char szTag[32] = {};
		std::memcpy(szTag, m_tag.data(), m_tag.size());
		ImGui::PushID(id++);
		ImGui::PushItemWidth(100);
		if (ImGui::InputText("Tag", szTag, 32, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			m_tag = szTag;
		}
		ImGui::PopID();
	}

	// レイヤー
	{
		char szLayer[32] = {};
		std::memcpy(szLayer, m_layer.data(), m_layer.size());
		ImGui::PushID(id++);
		ImGui::PushItemWidth(100);
		if (ImGui::InputText("Layer", szLayer, 32, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			m_layer = szLayer;
		}
		ImGui::PopID();
	}

	ImGui::EndGroup();


	// トランスフォーム
	auto* pTransform = m_pEntityManager->GetTransformManager()->FindTransform(m_transformID);
	if (pTransform)
	{
		if (pTransform->BeginInspectorGUI())
		{
			pTransform->DispInspector();
			pTransform->EndInspectorGUI();
		}
	}

	// コンポーネント
	for (const auto& comID : m_components)
	{
		auto* pCom = m_pEntityManager->GetComponentManager()->FindComponent(comID.first, comID.second);
		if (pCom)
		{
			if (pCom->BeginInspectorGUI())
			{
				pCom->DispInspector();
				pCom->EndInspectorGUI();
			}
		}
	}


	// スクリプト
	for (const auto& scriptID : m_scripts)
	{
		auto* pScript = m_pEntityManager->GetComponentManager()->FindComponent(
			static_cast<TypeID>(Script::GetTypeHash()), scriptID.second);
		if (pScript)
		{
			if (pScript->BeginInspectorGUI())
			{
				pScript->DispInspector();
				pScript->EndInspectorGUI();
			}
		}
	}

}

/// @brief コンポーネントマネージャー取得
/// @return コンポーネントマネージャーポインタ
ComponentManager* Entity::GetComponentManager() noexcept
{
	return m_pEntityManager->GetComponentManager();
}
