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
	friend class Entity;
	friend class ComponentManager;
public:

	/// @brief コンストラクタ
	explicit Component() noexcept :
		Object(), 
		m_pComponentManager(nullptr),
		m_entityID(NONE_ENTITY_ID),
		m_isEnable(true)
	{
	}

	/// @brief デストラクタ
	virtual ~Component() noexcept = default;

	/// @brief コンポーネントID取得
	/// @return コンポーネントID
	ComponentID GetComponentID() noexcept
	{
		return static_cast<ComponentID>(GetInstanceID()); 
	}

	///// @brief 親エンティティの取得
	///// @return エンティティポインタ
	//Entity* entity() noexcept;

	///// @brief トランスフォームの取得
	///// @return トランスフォームポインタ
	//Transform* transform() noexcept;

	/// @brief 使用フラグ指定
	/// @param isEnable フラグ
	void SetEnable(bool isEnable) noexcept;

	bool GetEnable() { return m_isEnable; }

public:
	//--- コールバック関数

	virtual void OnCreate() {}
	virtual void OnDestroy() {}

	virtual void OnEnable() {}
	virtual void OnDisable() {}

	virtual void OnStart() {} ///< 初回更新前に一度

	virtual void DispInspector() noexcept override {}

protected:
	//--- none serialize param

	ComponentManager* m_pComponentManager;

	//--- serialize param

	/// @brief 親のエンティティID
	EntityID	m_entityID;
	/// @brief アクティブフラグ
	bool		m_isEnable;

};

#endif // !_COMPONENT_
