/*****************************************************************//**
 * \file   EntityManager.h
 * \brief  �G���e�B�e�B�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/17
 *********************************************************************/
#include "EntityManager.h"

#include "Scene.h"
#include "Entity.h"
#include "Component.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "TransformManager.h"


 /// @brief �G���e�B�e�B�̐���
 /// @param name �G���e�B�e�B��
 /// @param bActive �A�N�e�B�u�w��
 /// @param bStatic �ÓI�w��
 /// @return �G���e�B�e�B�|�C���^
Entity* EntityManager::CreateEntity(std::string_view name, bool bActive, bool bStatic)
{
	// ID�쐬
	EntityID entityID = NONE_ENTITY_ID;
	do
	{
		entityID = static_cast<EntityID>(rand() % std::numeric_limits<int>::max());
		auto itr = m_entityPool.find(entityID);
		if (m_entityPool.end() == itr)
		{
			break;
		}
	} while (true);

	// �}�l�[�W���[
	auto* pEntityManager = this;
	auto* pComponentManager = m_pScene->GetComponentManager();
	auto* pTransformManager = m_pScene->GetTransformManager();

	// �G���e�B�e�B����
	auto entity = std::make_unique<Entity>(entityID, name, pComponentManager, bActive, bStatic);
	auto* pEntity = entity.get();
	m_entityPool.emplace(entityID, std::move(entity));

	// �g�����X�t�H�[������


	return pEntity;
}

/// @brief �G���e�B�e�B�̍폜
/// @param entityID �C���X�^���XID
void EntityManager::DestroyEntity(const EntityID& entityID)
{

}

/// @brief �R���|�[�l���g�}�l�[�W���[�擾
/// @return �R���|�[�l���g�}�l�[�W���[
ComponentManager* EntityManager::GetComponentManager()
{
	return m_pScene->GetComponentManager();
}

/// @brief �g�����X�t�H�[���}�l�[�W���[�擾
/// @return �g�����X�t�H�[���}�l�[�W���[
TransformManager* EntityManager::GetTransformManager()
{
	return m_pScene->GetTransformManager();
}
