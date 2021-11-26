/*****************************************************************//**
 * \file   Entity.h
 * \brief  �G���e�B�e�B
 *
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#include "Entity.h"

#include "EntityManager.h"
#include "TransformManager.h"

#include "ImGui\imgui.h"


 /// @brief �A�N�e�B�u�w��
 /// @param isActive �t���O
void Entity::SetActive(bool isActive)
{
	//--- Enable�X�V

	// �g�����X�t�H�[��

	// �R���|�[�l���g

	// �X�N���v�g
}

/// @brief �X�^�e�B�b�N�w��
/// @param isStatic �t���O
void Entity::SetStatic(bool isStatic)
{
	//--- Static�X�V

	// �g�����X�t�H�[��

}

 /// @brief �g�����X�t�H�[���̎擾
 /// @return �g�����X�t�H�[���|�C���^
Transform* Entity::transform() noexcept
{
	TransformManager* pTransformManager = m_pEntityManager->GetTransformManager();
	return pTransformManager->FindTransform(m_transformID);
}

/// @brief �C���X�y�N�^�[�\��
void Entity::DispInspector() noexcept
{
	int id = static_cast<int>(GetInstanceID());

	ImGui::BeginGroup();

	// �A�N�e�B�u
	ImGui::PushID(id++);
	if (ImGui::Checkbox("Active", &m_isActive))
	{
		SetActive(m_isActive);
	}
	ImGui::PopID();

	// �X�^�e�B�b�N
	ImGui::SameLine();
	ImGui::PushID(id++);
	if (ImGui::Checkbox("Static", &m_isStatic))
	{
		SetStatic(m_isStatic);
	}
	ImGui::PopID();

	// ���O
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

	// �^�O
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

	// ���C���[
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


	// �g�����X�t�H�[��
	auto* pTransform = m_pEntityManager->GetTransformManager()->FindTransform(m_transformID);
	if (pTransform)
	{
		if (pTransform->BeginInspectorGUI())
		{
			pTransform->DispInspector();
			pTransform->EndInspectorGUI();
		}
	}

	// �R���|�[�l���g
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


	// �X�N���v�g
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

/// @brief �R���|�[�l���g�}�l�[�W���[�擾
/// @return �R���|�[�l���g�}�l�[�W���[�|�C���^
ComponentManager* Entity::GetComponentManager() noexcept
{
	return m_pEntityManager->GetComponentManager();
}
