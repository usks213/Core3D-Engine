/*****************************************************************//**
 * \file   Transform.h
 * \brief  トランスフォーム
 *
 * \author USAMI KOSHI
 * \date   2021/011/21
 *********************************************************************/
#include "Transform.h"

#include "TransformManager.h"
#include "ImGui\imgui.h"


 /// @brief インスペクター表示
void Transform::OnInspectorGUI()
{
	int id = static_cast<int>(GetTransformID());
	ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
	float InputWith = 150.0f;

	// ローカル座標
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

	// ローカル回転(オイラー角)
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

	// ローカルスケール
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

 /// @brief ローカル座標指定
 /// @param pos 座標
void Transform::position(Vector3 pos)
{
	m_isDirty = true;
	m_localPosition = pos;
}

/// @brief ローカル回転指定
/// @param rot クォータニオン
void Transform::rotation(Quaternion rot)
{
	m_isDirty = true;
	m_localRotation = rot;
}

/// @brief ローカルスケール指定
/// @param scale スケール
void Transform::scale(Vector3 scale)
{
	m_isDirty = true;
	m_localScale = scale;
}

/// @brief オイラー角指定
/// @param euler オイラー角
void Transform::euler(Vector3 euler)
{
	m_isDirty = true;
	m_localRotation = Quaternion::CreateFromYawPitchRoll(
		Mathf::ToRadians(euler.y), Mathf::ToRadians(euler.x), Mathf::ToRadians(euler.z));
}

/// @brief オイラー角取得
/// @return オイラー角
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

/// @brief 親のトランスフォーム指定
/// @param parentID 親のトランスフォームID
void Transform::SetParent(const TransformID& parentID)
{
	m_pTransformManager->CreateRelation(GetTransformID(), parentID);
}

/// @brief 親のトランスフォーム取得
/// @return トランスフォームポインタ
Transform* Transform::GetParent()
{
	return m_pTransformManager->FindTransform(m_parent);
}

/// @brief 自身をルートに戻す
void Transform::ReturnRoot()
{
	m_pTransformManager->DestroyRelation(GetTransformID(), m_parent);
}

/// @brief 子のトランスフォームを追加
/// @param childID 子のトランスフォームID
void Transform::AddChild(const TransformID& childID)
{
	m_pTransformManager->CreateRelation(childID, GetTransformID());
}

/// @brief 指定した子のトランスフォームを取得
/// @param index インデックス
/// @return トランスフォームポインタ
Transform* Transform::GetChild(std::size_t index)
{
	if (index < m_childs.size())
	{
		return m_pTransformManager->FindTransform(m_childs[index]);
	}
	return nullptr;
}

/// @brief 子のトランスフォームを削除
/// @param childID 子のトランスフォームID
void Transform::RemoveChild(const TransformID& childID)
{
	m_pTransformManager->DestroyRelation(childID, GetTransformID());
}

/// @brief ローカルマトリックス更新
void Transform::UpdateLocalMatrix()
{
	m_isDirty = false;

	// ワールドマトリックス更新
	Matrix world = Matrix::CreateScale(m_localScale);
	world *= Matrix::CreateFromQuaternion(m_localRotation);
	world *= Matrix::CreateTranslation(m_localPosition);
	m_localMatrix = world;
}
