/*****************************************************************//**
 * \file   Entity.h
 * \brief  エンティティ
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "Object.h"
#include <unordered_map>

class Component;
class EntityManager;
class ComponentManager;

/// @brief エンティティ
class Entity final : public Object
{
	friend class Component;
	friend class EntityManager;
public:
	/// @brief オブジェクト情報
	DECLARE_OBJECT_INFO(Entity);

	/// @brief コンストラクタ
	/// @param id エンティティID
	/// @param entity エンティティ
	explicit Entity(ComponentManager* pComponentManager, const InstanceID& id,
		std::string_view name, const InstanceID& transformID) :
		Object(id, name), 
		m_transformID(transformID),
		m_pComponentManager(pComponentManager)
	{
	}

	/// @brief デストラクタ
	~Entity() = default;


	template<class T>
	constexpr T* AddComponent()
	{
		constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// 検索

	}


	///// @brief シリアライズ化
	//template<class T>
	//void serialize(T& archive)
	//{
	//	Object::serialize(archive);
	//	archive(
	//		CEREAL_NVP(m_entity),
	//		CEREAL_NVP(m_parentID),
	//		CEREAL_NVP(m_childsID)
	//	);
	//}

private:
	/// @brief 保持しているコンポーネント
	std::unordered_map<TypeID, InstanceID> m_components;
	/// @brief トランスフォームID
	InstanceID				m_transformID;
	/// @brief コンポーネントマネージャー
	ComponentManager*		m_pComponentManager;

};

#endif // !_ENTITY_
