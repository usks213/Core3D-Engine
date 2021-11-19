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
		Object("Component"), 
		m_pComponentManager(nullptr),
		m_entityID(NONE_ENTITY_ID),
		m_isActive(true)
	{
	}

	/// @brief コンストラクタ
	explicit Component(std::string_view name) noexcept :
		Object(name),
		m_pComponentManager(nullptr),
		m_entityID(NONE_ENTITY_ID),
		m_isActive(true)
	{
	}

	/// @brief デストラクタ
	virtual ~Component() noexcept = default;


	/// @brief 親エンティティの取得
	/// @return エンティティポインタ
	Entity* entity() noexcept;

	/// @brief トランスフォームの取得
	/// @return トランスフォームポインタ
	Transform* transform() noexcept;

	/// @brief アクティブ指定
	/// @param isActive フラグ
	void SetActive(bool isActive) noexcept;

public:
	//--- コールバック関数

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void OnEnable() = 0;
	virtual void OnDisable() = 0;

	virtual void OnStart() = 0;	///< 初回更新前に一度

protected:
	//--- none serialize param

	ComponentManager* m_pComponentManager;

	//--- serialize param

	/// @brief 親のエンティティID
	EntityID	m_entityID;
	/// @brief アクティブフラグ
	bool		m_isActive;

};

#endif // !_COMPONENT_
