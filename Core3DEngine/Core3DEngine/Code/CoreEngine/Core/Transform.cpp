/*****************************************************************//**
 * \file   Transform.h
 * \brief  トランスフォーム
 *
 * \author USAMI KOSHI
 * \date   2021/011/21
 *********************************************************************/
#include "Transform.h"

#include "TransformManager.h"


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
