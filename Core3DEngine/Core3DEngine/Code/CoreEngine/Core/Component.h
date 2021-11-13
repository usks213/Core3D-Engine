/*****************************************************************//**
 * \file   Component.h
 * \brief  コンポーネント
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "Object.h"

class ComponentManager;

/// @brief コンポーネント
class Component final : public Object
{
	friend class ComponentManager;
public:
	/// @brief オブジェクト情報
	DECLARE_OBJECT_INFO(Component);

	/// @brief コンストラクタ
	/// @param id コンポーネントID
	/// @param entity コンポーネント
	explicit Component(const InstanceID& id, std::string_view name) :
		Object(id, name)
	{
	}

	/// @brief デストラクタ
	~Component() = default;


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
