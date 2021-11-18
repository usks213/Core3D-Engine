/*****************************************************************//**
 * \file   EntityManager.h
 * \brief  エンティティマネージャー
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


 /// @brief エンティティの生成
 /// @param name エンティティ名
 /// @param bActive アクティブ指定
 /// @param bStatic 静的指定
 /// @return エンティティポインタ
Entity* EntityManager::CreateEntity(std::string_view name, bool bActive, bool bStatic)
{
	// ID作成
	InstanceID instanceID = MAX_INSTANCE_ID;
	do
	{
		instanceID = static_cast<InstanceID>(rand() % std::numeric_limits<int>::max());
		auto itr = m_entityPool.find(instanceID);
		if (m_entityPool.end() == itr)
		{
			break;
		}
	} while (true);

	// マネージャー
	auto* pEntityManager = this;
	auto* pComponentManager = m_pScene->GetComponentManager();
	auto* pTransformManager = m_pScene->GetTransformManager();

	// エンティティ生成
	auto entity = std::make_unique<Entity>(instanceID, name, pComponentManager, bActive, bStatic);
	auto* pEntity = entity.get();
	m_entityPool.emplace(instanceID, std::move(entity));

	// トランスフォーム生成


	return pEntity;
}

/// @brief エンティティの削除
/// @param instanceID インスタンスID
void EntityManager::DestroyEntity(const InstanceID& instanceID)
{

}

/// @brief コンポーネントマネージャー取得
/// @return コンポーネントマネージャー
ComponentManager* EntityManager::GetComponentManager()
{
	return m_pScene->GetComponentManager();
}

/// @brief トランスフォームマネージャー取得
/// @return トランスフォームマネージャー
TransformManager* EntityManager::GetTransformManager()
{
	return m_pScene->GetTransformManager();
}
