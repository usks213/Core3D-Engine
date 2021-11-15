/*****************************************************************//**
 * \file   Entity.h
 * \brief  エンティティ
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "Script.h"
#include "ComponentManager.h"
#include <unordered_map>

class Component;
class EntityManager;
class Transform;

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
	explicit Entity() :
		Object("Entity"), 
		m_transformID(MAX_INSTANCE_ID),
		m_pComponentManager(nullptr),
		// param
		m_isActive(true),
		m_isStatic(false),
		m_tag("Default"),
		m_layer("Default")
	{
	}

	/// @brief デストラクタ
	~Entity() = default;


	/// @brief コンポーネントの追加
	/// @tparam T コンポーネントクラス
	/// @return コンポーネントポインタ
	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* AddComponent()
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());

		// コンポーネントかスクリプトか
		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- スクリプト
			// 検索
			auto itr = m_scripts.find(typeID);
			if (m_scripts.end() != itr)
			{
				return m_pComponentManager->FindComponent<T>(itr->second);
			}
			// 新規生成
			T* pCom = m_pComponentManager->CreateComponent<T>(m_instanceID);
			pCom->m_parentID = m_instanceID;
			pCom->m_scriptID = T::GetScriptTypeID();
			// 格納
			m_scripts.emplace(T::GetScriptTypeID(), pCom->GetInstanceID());

			return pCom;
		}
		else
		{
			//--- コンポーネント
			// 検索
			auto itr = m_components.find(typeID);
			if (.end() != itr)
			{
				return m_pComponentManager->FindComponent<T>(itr->second);
			}
			// 新規生成
			T* pCom = m_pComponentManager->CreateComponent<T>(m_instanceID);
			pCom->m_parentID = m_instanceID;
			// 格納
			m_components.emplace(typeID, pCom->GetInstanceID());

			return pCom;
		}
	}

	/// @brief コンポーネントの削除
	/// @param pComponent コンポーネントポインタ
	void RemoveComponent(Component* pComponent)
	{
		TypeID typeID = pComponent->GetTypeID();
		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- スクリプト
			Script* pScript = static_cast<Script*>(pComponent);
			// 検索
			auto itr = m_scripts.find(pScript->m_scriptID);
			if (m_scripts.end() != itr)
			{
				m_pComponentManager->DestroyComponent(typeID, itr->second);
			}
		}
		else
		{
			//--- コンポーネント
			// 検索
			auto itr = m_components.find(typeID);
			if (m_components.end() != itr)
			{
				m_pComponentManager->DestroyComponent(typeID, itr->second);
			}
		}
	}

	/// @brief コンポーネントの取得
	/// @tparam T コンポーネントクラス
	/// @return コンポーネントポインタ
	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* GetComponent()
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());

		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- スクリプト
			ScriptID scriptID = T::GetScriptTypeID();
			// 検索
			auto itr = m_scripts.find(scriptID);
			if (m_scripts.end() != itr)
			{
				return m_pComponentManager->FindComponent<T>(itr->second);
			}
		}
		else
		{
			//--- コンポーネント
			// 検索
			auto itr = m_components.find(typeID);
			if (m_components.end() != itr)
			{
				return m_pComponentManager->FindComponent<T>(itr->second);
			}
		}
		// なし
		return nullptr;
	}

	/// @brief トランスフォームの取得
	/// @return 
	Transform* transform()
	{
		return m_pComponentManager->FindComponent<Transform>(m_transformID);
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
	/// @brief 保持しているスクリプトコンポーネント
	std::unordered_map<ScriptID, InstanceID> m_scripts;

	/// @brief トランスフォームID
	InstanceID				m_transformID;
	/// @brief コンポーネントマネージャー
	ComponentManager*		m_pComponentManager;

	//--- param

	bool					m_isActive;		///< アクティブフラグ
	bool					m_isStatic;		///< 静的フラグ
	std::string				m_tag;			///< タグ
	std::string				m_layer;		///< レイヤー
};

#endif // !_ENTITY_
