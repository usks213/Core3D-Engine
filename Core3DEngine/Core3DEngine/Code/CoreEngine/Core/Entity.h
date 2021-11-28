/*****************************************************************//**
 * \file   Entity.h
 * \brief  エンティティ
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _ENTITY_
#define _ENTITY_

#include "ComponentManager.h"
#include "Script.h"

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
	explicit Entity() noexcept :
		Object(), 
		m_pEntityManager(nullptr),
		// components
		m_transformID(NONE_TRANSFORM_ID),
		m_components(),
		m_scripts(),
		// param
		m_name("Entity"),
		m_isActive(true),
		m_isStatic(false),
		m_tag("Default"),
		m_layer("Default")
	{
	}

	explicit Entity(const EntityID& id,
		EntityManager* pEntityManager,
		std::string_view name,
		bool bActive, bool bStatic) noexcept :
		// 
		Object(static_cast<InstanceID>(id)),
		m_pEntityManager(pEntityManager),
		// components
		m_transformID(NONE_TRANSFORM_ID),
		m_components(),
		m_scripts(),
		// param
		m_name(name),
		m_isActive(bActive),
		m_isStatic(bStatic),
		m_tag("Default"),
		m_layer("Default")
	{
	}

	/// @brief デストラクタ
	~Entity() noexcept = default;

	/// @brief 自身のエンティティIDの取得
	/// @return エンティティID
	[[nodiscard]] EntityID GetEntityID() noexcept
	{
		return static_cast<EntityID>(GetInstanceID());
	}

	/// @brief 名前の取得
	/// @return 名前
	[[nodiscard]] std::string_view GetName() noexcept { return m_name; }

	/// @brief 名前の指定
	/// @param name エンティティ名
	void SetName(std::string_view name) noexcept { m_name = name; }


	/// @brief コンポーネントの追加
	/// @tparam T スクリプト型クラス
	/// @return コンポーネントポインタ
	template<class T, typename = std::enable_if_t<std::is_base_of_v<Component, T> && std::is_base_of_v<Script, T>>>
	T* AddComponent(T* Type = nullptr)
	{
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		static constexpr ScriptID scriptID = T::GetScriptTypeID();
		ComponentManager* pComponentManager = GetComponentManager();

		// スクリプトか
		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- スクリプト
			// 検索
			auto itr = m_scripts.find(scriptID);
			if (m_scripts.end() != itr)
			{
				return pComponentManager->FindComponent<T>(itr->second);
			}
			// 新規生成
			T* pCom = pComponentManager->CreateComponent<T>(GetEntityID(), m_isActive);
			// 格納
			m_scripts.emplace(scriptID, pCom->GetComponentID());

			return pCom;
		}

		return nullptr;
	}

	/// @brief コンポーネントの追加
	/// @tparam T コンポーネントクラス
	/// @return コンポーネントポインタ
	template<class T, typename = std::enable_if_t<std::is_base_of_v<Component, T> && !std::is_base_of_v<Script, T>>>
	T* AddComponent()
	{
		//static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		ComponentManager* pComponentManager = GetComponentManager();
		//--- コンポーネント
		// 検索
		auto itr = m_components.find(typeID);
		if (m_components.end() != itr)
		{
			return pComponentManager->FindComponent<T>(itr->second);
		}
		// 新規生成
		T* pCom = pComponentManager->CreateComponent<T>(GetEntityID(), m_isActive);
		// 格納
		m_components.emplace(typeID, pCom->GetComponentID());

		return pCom;
	}

	/// @brief コンポーネントの削除
	/// @param pComponent コンポーネントポインタ
	void RemoveComponent(Component* pComponent)
	{
		ComponentManager* pComponentManager = GetComponentManager();
		TypeID typeID = pComponent->GetTypeID();
		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- スクリプト
			Script* pScript = static_cast<Script*>(pComponent);
			// 検索
			auto itr = m_scripts.find(pScript->GetScriptID());
			if (m_scripts.end() != itr)
			{
				pComponentManager->DestroyComponent(typeID, itr->second);
			}
		}
		else
		{
			//--- コンポーネント
			// 検索
			auto itr = m_components.find(typeID);
			if (m_components.end() != itr)
			{
				pComponentManager->DestroyComponent(typeID, itr->second);
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
		ComponentManager* pComponentManager = GetComponentManager();

		if (typeID == static_cast<TypeID>(Script::GetTypeHash()))
		{
			//--- スクリプト
			ScriptID scriptID = T::GetScriptTypeID();
			// 検索
			auto itr = m_scripts.find(scriptID);
			if (m_scripts.end() != itr)
			{
				return pComponentManager->FindComponent<T>(itr->second);
			}
		}
		else
		{
			//--- コンポーネント
			// 検索
			auto itr = m_components.find(typeID);
			if (m_components.end() != itr)
			{
				return pComponentManager->FindComponent<T>(itr->second);
			}
		}
		// なし
		return nullptr;
	}

	/// @brief アクティブ指定
	/// @param isActive フラグ
	void SetActive(bool isActive);

	/// @brief スタティック指定
	/// @param isStatic フラグ
	void SetStatic(bool isStatic);

	/// @brief トランスフォームの取得
	/// @return トランスフォームポインタ
	Transform* transform() noexcept;

	/// @brief インスペクター表示
	void OnInspectorGUI() override;

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

	/// @brief コンポーネントマネージャー取得
	/// @return コンポーネントマネージャーポインタ
	ComponentManager* GetComponentManager() noexcept;

private:
	//--- none serialize param

	/// @brief エンティティマネージャー
	EntityManager*		m_pEntityManager;

	//--- serialize param

	/// @brief トランスフォームID
	TransformID								 m_transformID;
	/// @brief 保持しているコンポーネント
	std::unordered_map<TypeID, ComponentID>	 m_components;
	/// @brief 保持しているスクリプトコンポーネント
	std::unordered_map<ScriptID, ComponentID> m_scripts;

	std::string				m_name;			///< エンティティ名
	bool					m_isActive;		///< アクティブフラグ
	bool					m_isStatic;		///< 静的フラグ
	std::string				m_tag;			///< タグ
	std::string				m_layer;		///< レイヤー
};

#endif // !_ENTITY_
