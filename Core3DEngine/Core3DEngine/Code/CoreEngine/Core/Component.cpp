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
