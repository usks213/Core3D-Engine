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
class EntityManager;
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
		m_pEntityManager(nullptr),
		m_parentID(MAX_INSTANCE_ID),
		m_isActive(true)
	{
	}

	/// @brief コンストラクタ
	/// @param name コンポーネント名
	explicit Component(std::string_view name) noexcept :
		Object(name), 
		m_pEntityManager(nullptr),
		m_parentID(MAX_INSTANCE_ID),
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

	EntityManager* m_pEntityManager;

	//--- serialize param

	/// @brief 親のエンティティID
	InstanceID	m_parentID;
	/// @brief アクティブフラグ
	bool		m_isActive;

};

#endif // !_COMPONENT_
