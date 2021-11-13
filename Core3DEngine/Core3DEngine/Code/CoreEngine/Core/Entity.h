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

class EntityManager;

/// @brief エンティティ
class Entity final : public Object
{
	friend class EntityManager;
public:
	/// @brief オブジェクト情報
	DECLARE_OBJECT_INFO(Entity);

	/// @brief コンストラクタ
	/// @param id エンティティID
	/// @param entity エンティティ
	explicit Entity(const InstanceID& id, std::string_view name) :
		Object(id, name)
	{
	}

	/// @brief デストラクタ
	~Entity() = default;


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

protected:


private:

};

#endif // !_ENTITY_
