/*****************************************************************//**
 * \file   TransformManager.h
 * \brief  トランスフォームマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/17
 *********************************************************************/
#include "TransformManager.h"

#include "Scene.h"
#include "Transform.h"
#include "ComponentManager.h"


Transform* TransformManager::CreateTransform(
	const EntityID& entityID, bool bActive, bool bStatic, const TransformID& parentID)
{
	auto pComponentManager = m_pScene->GetComponentManager();
	// 新規生成
	Transform* pTransform = pComponentManager->CreateComponent<Transform>(entityID, (bActive & !bStatic));
	pTransform->m_pTransformManager = this;

	// 親がいるか
	Transform* pParent = FindTransform(parentID);
	if (pParent == nullptr)
	{
		// ルートに格納
		RegisterRoot(pTransform->GetTransformID());
	}
	else
	{
		// 親の子格納
		pParent->AddChild(pTransform->GetTransformID());
	}

	return pTransform;
}

void TransformManager::DestroyTransform(const TransformID& transformID)
{
	// 検索
	Transform* pTransform = FindTransform(transformID);
	if (pTransform)
	{
		// ルートから削除
		RemoveRoot(transformID);
		// コンポーネントマネージャーから削除
		auto pComponentManager = m_pScene->GetComponentManager();
		pComponentManager->DestroyComponent(pTransform->GetTypeID(), pTransform->GetComponentID());
	}
}

Transform* TransformManager::FindTransform(const TransformID& transformID)
{
	// コンポーネントマネージャーから検索
	auto pComponentManager = m_pScene->GetComponentManager();
	return pComponentManager->FindComponent<Transform>(static_cast<ComponentID>(transformID));
}

void TransformManager::CreateRelation(const TransformID& transformID, const TransformID& parentID)
{
	Transform* pTransfrom = FindTransform(transformID);
	Transform* pParent = FindTransform(parentID);
	// どちらかが存在しない場合ははじく
	if (pTransfrom == nullptr || pParent == nullptr) return;

	// 自分の子に自分を親として指定できない
	if (FindParentRelation(pParent, pTransfrom) != nullptr) return;

	// 現在の親から削除
	DestroyRelation(transformID, pTransfrom->m_parent);

	// ルートから削除
	RemoveRoot(transformID);

	// 自分の親に設定
	pTransfrom->m_parent = parentID;
	// 親の子に設定
	pParent->m_childs.push_back(transformID);

	//--- 行列再計算
	
	// 親の逆行列を反映
	auto invParent = pParent->m_globalMatrix.Invert();
	auto invParentScale = Vector3(1, 1, 1) / pParent->m_globalScale;
	auto localMatrix = pTransfrom->m_localMatrix * invParent;
	// 位置
	pTransfrom->m_localPosition = localMatrix.Translation();
	// 回転
	Matrix invSca = Matrix::CreateScale(pTransfrom->m_localPosition * invParentScale);
	invSca = invSca.Invert();
	pTransfrom->m_localRotation = Quaternion::CreateFromRotationMatrix(invSca * localMatrix);
	// 拡縮
	pTransfrom->m_localScale = pTransfrom->m_localScale * invParentScale;

	// マトリックス更新
	// 拡縮
	pTransfrom->m_localMatrix = Matrix::CreateScale(pTransfrom->m_localScale);
	// 回転
	pTransfrom->m_localMatrix *= Matrix::CreateFromQuaternion(pTransfrom->m_localRotation);
	// 移動
	pTransfrom->m_localMatrix *= Matrix::CreateTranslation(pTransfrom->m_localPosition);

}

void TransformManager::DestroyRelation(const TransformID& transformID, const TransformID& parentID)
{
	Transform* pTransfrom = FindTransform(transformID);
	Transform* pParent = FindTransform(parentID);
	// どちらかが存在しない場合ははじく
	if (pTransfrom == nullptr || pParent == nullptr) return;

	// 親の子から自分を削除
	auto itr = std::find(pParent->m_childs.begin(), pParent->m_childs.end(), transformID);
	if (pParent->m_childs.end() != itr)
	{
		pParent->m_childs.erase(itr);
	}

	// 自分をルートへ
	RegisterRoot(transformID);
	pTransfrom->m_parent = NONE_TRANSFORM_ID;

	//--- 行列再計算

	// グローバル
	auto global = pTransfrom->m_globalMatrix;
	// 位置
	pTransfrom->m_localPosition = global.Translation();
	// 回転
	Matrix invSca = Matrix::CreateScale(pTransfrom->m_globalScale);
	invSca = invSca.Invert();
	pTransfrom->m_localRotation = Quaternion::CreateFromRotationMatrix(invSca * global);
	// 拡縮
	pTransfrom->m_localScale = pTransfrom->m_globalScale;

	// マトリックス更新
	// 拡縮
	pTransfrom->m_localMatrix = Matrix::CreateScale(pTransfrom->m_localScale);
	// 回転
	pTransfrom->m_localMatrix *= Matrix::CreateFromQuaternion(pTransfrom->m_localRotation);
	// 移動
	pTransfrom->m_localMatrix *= Matrix::CreateTranslation(pTransfrom->m_localPosition);

}


//---------------------------------------------------------------------------
//	private methods
//---------------------------------------------------------------------------

void TransformManager::RegisterRoot(const TransformID& transformID)
{
	// 検索
	auto itr = m_rootTransformTable.find(transformID);

	// 既に格納済み
	if (m_rootTransformTable.end() != itr)
	{
		return;
	}

	// 新規格納
	m_rootTransformTable.emplace(transformID, m_rootTransforms.size());
	m_rootTransforms.push_back(transformID);
}

void TransformManager::RemoveRoot(const TransformID& transformID)
{
	// 検索
	auto itr = m_rootTransformTable.find(transformID);

	// 存在しない
	if (m_rootTransformTable.end() == itr)
	{
		return;
	}

	// 最後尾と入れ替え
	Index index = itr->second;
	auto backTransformID = m_rootTransforms.back();

	m_rootTransforms[index] = backTransformID;
	m_rootTransforms.pop_back();

	m_rootTransformTable[backTransformID] = index;
	m_rootTransformTable.erase(itr);
}

/// @brief 開始位置から親を探索し、検索値を親に持つ値を返す
/// @param pBegin 開始位置
/// @param pFind 検索対象
/// @return 一致した値 or nullptr
Transform* TransformManager::FindParentRelation(Transform* pBegin, Transform* pFind)
{
	// 親の検索
	Transform* pParent = FindTransform(pBegin->m_parent);
	if (pParent == nullptr)
	{
		return nullptr;
	}

	// 一致した
	if (pParent->GetTransformID() == pFind->GetTransformID())
	{
		return pBegin;
	}

	return FindParentRelation(pParent, pFind);
}
