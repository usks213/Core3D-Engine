/*****************************************************************//**
 * \file   Transform.h
 * \brief  �g�����X�t�H�[��
 *
 * \author USAMI KOSHI
 * \date   2021/011/21
 *********************************************************************/
#include "Transform.h"

#include "TransformManager.h"
#include "ImGui\imgui.h"


 /// @brief �C���X�y�N�^�[�\��
void Transform::OnInspectorGUI()
{
	int id = static_cast<int>(GetTransformID());
	ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
	float InputWith = 150.0f;

	// ���[�J�����W
	Vector3 pos = position();
	ImGui::Text("Position");
	ImGui::SameLine();
	ImGui::PushID(id++);
	ImGui::PushItemWidth(InputWith);
	if (ImGui::InputFloat3("", (float*)&pos, "%.2f", flags))
	{
		position(pos);
	}
	ImGui::PopItemWidth();
	ImGui::PopID();

	// ���[�J����](�I�C���[�p)
	Vector3 rot = euler();
	ImGui::Text("Rotation");
	ImGui::SameLine();
	ImGui::PushID(id++);
	ImGui::PushItemWidth(InputWith);
	if (ImGui::InputFloat3("", (float*)&rot, "%.2f", flags))
	{
		euler(rot);
	}
	ImGui::PopItemWidth();
	ImGui::PopID();

	// ���[�J���X�P�[��
	Vector3 sca = scale();
	ImGui::Text("Scale   ");
	ImGui::SameLine();
	ImGui::PushID(id++);
	ImGui::PushItemWidth(InputWith);
	if (ImGui::InputFloat3("", (float*)&m_localScale, "%.2f", flags))
	{
		scale(sca);
	}
	ImGui::PopItemWidth();
	ImGui::PopID();

}

 /// @brief ���[�J�����W�w��
 /// @param pos ���W
void Transform::position(Vector3 pos)
{
	m_isDirty = true;
	m_localPosition = pos;
}

/// @brief ���[�J����]�w��
/// @param rot �N�H�[�^�j�I��
void Transform::rotation(Quaternion rot)
{
	m_isDirty = true;
	m_localRotation = rot;
}

/// @brief ���[�J���X�P�[���w��
/// @param scale �X�P�[��
void Transform::scale(Vector3 scale)
{
	m_isDirty = true;
	m_localScale = scale;
}

/// @brief �I�C���[�p�w��
/// @param euler �I�C���[�p
void Transform::euler(Vector3 euler)
{
	m_isDirty = true;
	m_localRotation = Quaternion::CreateFromYawPitchRoll(
		Mathf::ToRadians(euler.y), Mathf::ToRadians(euler.x), Mathf::ToRadians(euler.z));
}

/// @brief �I�C���[�p�擾
/// @return �I�C���[�p
const Vector3 Transform::euler()
{
	float& x = m_localRotation.x;
	float& y = m_localRotation.y;
	float& z = m_localRotation.z;
	float& w = m_localRotation.w;
	Vector3 euler;
	euler.x = Mathf::ToDegrees(atan2(2.0f * (x * w - y * z), (w * w - x * x - y * y + z * z)));
	euler.y = Mathf::ToDegrees(asin(2.0f * (x * z + y * w)));
	euler.z = Mathf::ToDegrees(atan2(2.0f * (z * w - x * y), (w * w + x * x - y * y - z * z)));

	//Matrix m = Matrix::CreateFromQuaternion(m_localRotation);
	//euler.x = Mathf::ToDegrees(atan2(m._32, m._33));
	//euler.y = Mathf::ToDegrees(asin(m._31));
	//euler.z = Mathf::ToDegrees(atan2(m._21, m._11));

	return euler;
}

/// @brief �e�̃g�����X�t�H�[���w��
/// @param parentID �e�̃g�����X�t�H�[��ID
void Transform::SetParent(const TransformID& parentID)
{
	m_pTransformManager->CreateRelation(GetTransformID(), parentID);
}

/// @brief �e�̃g�����X�t�H�[���擾
/// @return �g�����X�t�H�[���|�C���^
Transform* Transform::GetParent()
{
	return m_pTransformManager->FindTransform(m_parent);
}

/// @brief ���g�����[�g�ɖ߂�
void Transform::ReturnRoot()
{
	m_pTransformManager->DestroyRelation(GetTransformID(), m_parent);
}

/// @brief �q�̃g�����X�t�H�[����ǉ�
/// @param childID �q�̃g�����X�t�H�[��ID
void Transform::AddChild(const TransformID& childID)
{
	m_pTransformManager->CreateRelation(childID, GetTransformID());
}

/// @brief �w�肵���q�̃g�����X�t�H�[�����擾
/// @param index �C���f�b�N�X
/// @return �g�����X�t�H�[���|�C���^
Transform* Transform::GetChild(std::size_t index)
{
	if (index < m_childs.size())
	{
		return m_pTransformManager->FindTransform(m_childs[index]);
	}
	return nullptr;
}

/// @brief �q�̃g�����X�t�H�[�����폜
/// @param childID �q�̃g�����X�t�H�[��ID
void Transform::RemoveChild(const TransformID& childID)
{
	m_pTransformManager->DestroyRelation(childID, GetTransformID());
}

/// @brief ���[�J���}�g���b�N�X�X�V
void Transform::UpdateLocalMatrix()
{
	m_isDirty = false;

	// ���[���h�}�g���b�N�X�X�V
	Matrix world = Matrix::CreateScale(m_localScale);
	world *= Matrix::CreateFromQuaternion(m_localRotation);
	world *= Matrix::CreateTranslation(m_localPosition);
	m_localMatrix = world;
}
