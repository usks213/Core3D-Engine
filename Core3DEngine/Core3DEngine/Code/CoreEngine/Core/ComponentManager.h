/*****************************************************************//**
 * \file   ComponentManager.h
 * \brief  コンポーネントマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _COMPONENT_MANAGER_
#define _COMPONENT_MANAGER_

#include "Component.h"

#include <memory>
#include <vector>
#include <unordered_map>

class Scene;

class ComponentManager final
{
public:
	/// @brief コンストラクタ
	/// @param pScene シーンポインタ
	explicit ComponentManager(Scene* pScene) noexcept :
		m_pScene(pScene)
	{
	}

	/// @brief デストラクタ
	~ComponentManager() noexcept = default;


	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* CreateComponent(const EntityID& entityID, bool isEnable)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// ID生成

		// 生成
		auto pCom = std::make_unique<T>();
		auto pResult = pCom.get();
		pResult->m_instanceID = ;
		pResult->m_entityID = entityID;
		pResult->m_isEnable = isEnable;
		// 格納
		m_componentLookupTable[typeID].emplace(pCom->GetComponentID(), m_componentPool[typeID].size());
		m_componentPool[typeID].push_back(std::move(pCom));

		return pResult;
	}

	void DestroyComponent(const TypeID& typeID ,const ComponentID& componentID);

	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* FindComponent(const ComponentID& componentID)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// 検索
		auto itr = m_componentLookupTable[typeID].find(componentID);
		if (m_componentLookupTable[typeID].end()) == itr)
		{
			return nullptr;
		}
		return static_cast<T*>(m_componentPool[typeID][itr->second].get());
	}

	/// @brief 削除リストの実行
	void CleanupComponent();

	/// @brief コンポーネントのシリアライズ
	void Serialize();

	/// @brief コンポーネントのデシリアライズ
	void Deserialize();

private:

	Component* RegisterComponent(const TypeID& typeID, const ComponentID& componentID, Component* pComponent);

private:
	/// @brief vectorIndex
	using Index = std::size_t;

	//--- serialize param

	/// @brief 型ごとのコンポーネントプール
	std::unordered_map<TypeID, std::vector<std::unique_ptr<Component>>>		m_componentPool;

	//--- none serialize param

	/// @brief 所属シーン
	Scene* m_pScene;

	/// @brief コンポーネントのルックアップテーブル
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_componentLookupTable;

	/// @brief 生成リスト
	std::unordered_map<TypeID, ComponentID>	m_createList;
	/// @brief 削除リスト
	std::unordered_map<TypeID, ComponentID>	m_destroyList;

	/// @brief アクティブコンポーネントリスト
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_activeComponents;
	/// @brief アクティブコンポーネントテーブル
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_activeComponentsTable;
	/// @brief 非アクティブコンポーネントリスト
	std::unordered_map<TypeID, std::vector<ComponentID>>					m_inactiveComponents;
	/// @brief 非アクティブコンポーネントテーブル
	std::unordered_map<TypeID, std::unordered_map<ComponentID, Index>>		m_inactiveComponentsTable;

};

#endif // !_COMPONENT_MANAGER_
