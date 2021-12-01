/*****************************************************************//**
 * \file   EntityManager.h
 * \brief  エンティティマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _ENTITY_MANAGER_
#define _ENTITY_MANAGER_

#include "Object.h"
#include <memory>
#include <unordered_map>

#include "Entity.h"

class Scene;
class Entity;
class ComponentManager;
class TransformManager;

class EntityManager final
{
public:

	/// @brief コンストラクタ
	explicit EntityManager(Scene* pScene) noexcept : 
		m_pScene(pScene) ,m_entityPool()
	{
	}

	/// @brief デストラクタ
	~EntityManager() noexcept = default;

	/// @brief エンティティの生成
	/// @param name エンティティ名
	/// @param bActive アクティブ指定
	/// @param bStatic 静的指定
	/// @return エンティティポインタ
	Entity* CreateEntity(std::string_view name, bool bActive = true, 
		bool bStatic = false, const TransformID& parentID = NONE_TRANSFORM_ID);

	/// @brief エンティティの削除
	/// @param instanceID インスタンスID
	void DestroyEntity(const EntityID& entityID);

	/// @brief エンティティの検索
	/// @param entityID エンティティID
	/// @return あった エンティティポインタ / なし nullptr
	Entity* FindEntity(const EntityID& entityID);

	/// @brief コンポーネントマネージャー取得
	/// @return コンポーネントマネージャー
	ComponentManager* GetComponentManager();

	/// @brief トランスフォームマネージャー取得
	/// @return トランスフォームマネージャー
	TransformManager* GetTransformManager();

private:
	/// @brief 所属シーン
	Scene* m_pScene;

	/// @brief エンティティプール
	std::unordered_map<EntityID, std::unique_ptr<Entity>> m_entityPool;

};


#endif // !_ENTITY_MANAGER_

