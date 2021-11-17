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

class Entity;

class EntityManager final
{
public:

	/// @brief コンストラクタ
	explicit EntityManager() noexcept : 
		m_entityPool()
	{
	}

	/// @brief デストラクタ
	~EntityManager() noexcept = default;

	/// @brief エンティティの生成
	/// @param name エンティティ名
	/// @param bActive アクティブ指定
	/// @param bStatic 静的指定
	/// @return エンティティポインタ
	Entity* CreateEntity(std::string_view name, bool bActive = true, bool bStatic = false);

	/// @brief エンティティの削除
	/// @param instanceID インスタンスID
	void DestroyEntity(const InstanceID& instanceID);

private:
	/// @brief エンティティプール
	std::unordered_map<InstanceID, std::unique_ptr<Entity>> m_entityPool;



};


#endif // !_ENTITY_MANAGER_

