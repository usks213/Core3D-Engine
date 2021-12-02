/*****************************************************************//**
 * \file   Component.h
 * \brief  �R���|�[�l���g
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

 /// @brief �e�G���e�B�e�B�̎擾
 /// @return �G���e�B�e�B�|�C���^
Entity* Component::entity() noexcept
{
	return m_pComponentManager->GetScene()->GetEntityManager()->FindEntity(m_entityID);
}

/// @brief �g�����X�t�H�[���̎擾
/// @return �g�����X�t�H�[���|�C���^
Transform* Component::transform() noexcept
{
	auto* pEntity = entity();
	if (pEntity == nullptr) return nullptr;

	return m_pComponentManager->GetScene()->GetTransformManager()->FindTransform(pEntity->m_transformID);
}

/// @brief �g�p�t���O�w��
/// @param isEnable �t���O
void Component::SetEnable(bool isEnable) noexcept
{

}

/// @brief �R���|�[�l���g���̎擾(�X�N���v�g�p�����)
/// @return �R���|�[�l���g��
std::string_view Component::GetComponentName() noexcept
{
	return GetTypeName();
}

/// @brief �C���X�y�N�^�[�\���̊J�n
/// @return �m�[�h���J���Ă��邩
bool Component::BeginInspectorGUI()
{
	// �R���|�[�l���g�̃w�b�_�[���\��
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

	// �g�p�t���O
	ImGui::SameLine();
	ImGui::PushID(id++);
	ImGui::Checkbox("", &m_isEnable);
	ImGui::PopID();

	// �R���|�[�l���g��
	ImGui::SameLine();
	ImGui::PushID(id++);
	ImGui::Text(GetComponentName().data());
	ImGui::PopID();


	return isOpen;
}

/// @brief �C���X�y�N�^�[�\���̏I��
void Component::EndInspectorGUI()
{
	// �m�[�h�I��
	ImGui::TreePop();
}
