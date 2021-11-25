/*****************************************************************//**
 * \file   TransformManager.h
 * \brief  �g�����X�t�H�[���}�l�[�W���[
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
	// �V�K����
	Transform* pTransform = pComponentManager->CreateComponent<Transform>(entityID, (bActive & !bStatic));
	pTransform->m_pTransformManager = this;

	// �e�����邩
	Transform* pParent = FindTransform(parentID);
	if (pParent == nullptr)
	{
		// ���[�g�Ɋi�[
		RegisterRoot(pTransform->GetTransformID());
	}
	else
	{
		// �e�̎q�i�[
		pParent->AddChild(pTransform->GetTransformID());
	}

	return pTransform;
}

void TransformManager::DestroyTransform(const TransformID& transformID)
{
	// ����
	Transform* pTransform = FindTransform(transformID);
	if (pTransform)
	{
		// ���[�g����폜
		RemoveRoot(transformID);
		// �R���|�[�l���g�}�l�[�W���[����폜
		auto pComponentManager = m_pScene->GetComponentManager();
		pComponentManager->DestroyComponent(pTransform->GetTypeID(), pTransform->GetComponentID());
	}
}

Transform* TransformManager::FindTransform(const TransformID& transformID)
{
	// �R���|�[�l���g�}�l�[�W���[���猟��
	auto pComponentManager = m_pScene->GetComponentManager();
	return pComponentManager->FindComponent<Transform>(static_cast<ComponentID>(transformID));
}

void TransformManager::CreateRelation(const TransformID& transformID, const TransformID& parentID)
{
	Transform* pTransfrom = FindTransform(transformID);
	Transform* pParent = FindTransform(parentID);
	// �ǂ��炩�����݂��Ȃ��ꍇ�͂͂���
	if (pTransfrom == nullptr || pParent == nullptr) return;

	// �����̎q�Ɏ�����e�Ƃ��Ďw��ł��Ȃ�
	if (FindParentRelation(pParent, pTransfrom) != nullptr) return;

	// ���݂̐e����폜
	DestroyRelation(transformID, pTransfrom->m_parent);

	// ���[�g����폜
	RemoveRoot(transformID);

	// �����̐e�ɐݒ�
	pTransfrom->m_parent = parentID;
	// �e�̎q�ɐݒ�
	pParent->m_childs.push_back(transformID);

	//--- �s��Čv�Z
	
	// �e�̋t�s��𔽉f
	auto invParent = pParent->m_globalMatrix.Invert();
	auto invParentScale = Vector3(1, 1, 1) / pParent->m_globalScale;
	auto localMatrix = pTransfrom->m_localMatrix * invParent;
	// �ʒu
	pTransfrom->m_localPosition = localMatrix.Translation();
	// ��]
	Matrix invSca = Matrix::CreateScale(pTransfrom->m_localPosition * invParentScale);
	invSca = invSca.Invert();
	pTransfrom->m_localRotation = Quaternion::CreateFromRotationMatrix(invSca * localMatrix);
	// �g�k
	pTransfrom->m_localScale = pTransfrom->m_localScale * invParentScale;

	// �}�g���b�N�X�X�V
	// �g�k
	pTransfrom->m_localMatrix = Matrix::CreateScale(pTransfrom->m_localScale);
	// ��]
	pTransfrom->m_localMatrix *= Matrix::CreateFromQuaternion(pTransfrom->m_localRotation);
	// �ړ�
	pTransfrom->m_localMatrix *= Matrix::CreateTranslation(pTransfrom->m_localPosition);

}

void TransformManager::DestroyRelation(const TransformID& transformID, const TransformID& parentID)
{
	Transform* pTransfrom = FindTransform(transformID);
	Transform* pParent = FindTransform(parentID);
	// �ǂ��炩�����݂��Ȃ��ꍇ�͂͂���
	if (pTransfrom == nullptr || pParent == nullptr) return;

	// �e�̎q���玩�����폜
	auto itr = std::find(pParent->m_childs.begin(), pParent->m_childs.end(), transformID);
	if (pParent->m_childs.end() != itr)
	{
		pParent->m_childs.erase(itr);
	}

	// ���������[�g��
	RegisterRoot(transformID);
	pTransfrom->m_parent = NONE_TRANSFORM_ID;

	//--- �s��Čv�Z

	// �O���[�o��
	auto global = pTransfrom->m_globalMatrix;
	// �ʒu
	pTransfrom->m_localPosition = global.Translation();
	// ��]
	Matrix invSca = Matrix::CreateScale(pTransfrom->m_globalScale);
	invSca = invSca.Invert();
	pTransfrom->m_localRotation = Quaternion::CreateFromRotationMatrix(invSca * global);
	// �g�k
	pTransfrom->m_localScale = pTransfrom->m_globalScale;

	// �}�g���b�N�X�X�V
	// �g�k
	pTransfrom->m_localMatrix = Matrix::CreateScale(pTransfrom->m_localScale);
	// ��]
	pTransfrom->m_localMatrix *= Matrix::CreateFromQuaternion(pTransfrom->m_localRotation);
	// �ړ�
	pTransfrom->m_localMatrix *= Matrix::CreateTranslation(pTransfrom->m_localPosition);

}


//---------------------------------------------------------------------------
//	private methods
//---------------------------------------------------------------------------

void TransformManager::RegisterRoot(const TransformID& transformID)
{
	// ����
	auto itr = m_rootTransformTable.find(transformID);

	// ���Ɋi�[�ς�
	if (m_rootTransformTable.end() != itr)
	{
		return;
	}

	// �V�K�i�[
	m_rootTransformTable.emplace(transformID, m_rootTransforms.size());
	m_rootTransforms.push_back(transformID);
}

void TransformManager::RemoveRoot(const TransformID& transformID)
{
	// ����
	auto itr = m_rootTransformTable.find(transformID);

	// ���݂��Ȃ�
	if (m_rootTransformTable.end() == itr)
	{
		return;
	}

	// �Ō���Ɠ���ւ�
	Index index = itr->second;
	auto backTransformID = m_rootTransforms.back();

	m_rootTransforms[index] = backTransformID;
	m_rootTransforms.pop_back();

	m_rootTransformTable[backTransformID] = index;
	m_rootTransformTable.erase(itr);
}

/// @brief �J�n�ʒu����e��T�����A�����l��e�Ɏ��l��Ԃ�
/// @param pBegin �J�n�ʒu
/// @param pFind �����Ώ�
/// @return ��v�����l or nullptr
Transform* TransformManager::FindParentRelation(Transform* pBegin, Transform* pFind)
{
	// �e�̌���
	Transform* pParent = FindTransform(pBegin->m_parent);
	if (pParent == nullptr)
	{
		return nullptr;
	}

	// ��v����
	if (pParent->GetTransformID() == pFind->GetTransformID())
	{
		return pBegin;
	}

	return FindParentRelation(pParent, pFind);
}
