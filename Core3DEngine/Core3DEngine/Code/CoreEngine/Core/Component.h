/*****************************************************************//**
 * \file   Component.h
 * \brief  コンポーネント
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _COMPONENT_
#define _COMPONENT_

#include "Object.h"

class Entity;
class Transform;
class ComponentManager;

/// @brief コンポーネント
class Component : public Object
{
	friend class ComponentManager;
public:

	/// @brief コンストラクタ
	/// @param id コンポーネントID
	/// @param entity コンポーネント
	explicit Component(const InstanceID& id, std::string_view name) :
		Object(id, name)
	{
	}

	/// @brief デストラクタ
	virtual ~Component() = default;


	/// @brief 親エンティティの取得
	/// @return エンティティポインタ
	Entity* GetParent();

	/// @brief トランスフォームの取得
	/// @return トランスフォームポインタ
	Transform* GetTransform();



protected:

	/// @brief 親のエンティティID
	InstanceID m_parentID;


};

#endif // !_COMPONENT_
