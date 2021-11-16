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

class ComponentManager final
{
public:
	ComponentManager();
	~ComponentManager();


	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* CreateComponent()
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// 生成
		auto pCom = std::make_unique<T>();
		auto pResult = pCom.get();
		// 格納
		m_componentLookupTable[typeID].emplace(pCom->GetInstanceID(), m_componentPool[typeID].size());
		m_componentPool[typeID].push_back(std::move(pCom));

		return pResult;
	}

	void DestroyComponent(const TypeID& typeID ,const InstanceID& instanceID);

	template<class T, bool isComBase = std::is_base_of_v<Component, T>>
	T* FindComponent(const InstanceID& instanceID)
	{
		static_assert(isComBase, "Not ComponentBase");
		static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
		// 検索
		auto itr = m_componentLookupTable[typeID].find(instanceID);
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

	Component* RegisterComponent(const TypeID& typeID, const InstanceID& instanceID, Component* pComponent);

private:
	/// @brief 型ごとのコンポーネントプール
	std::unordered_map<TypeID, std::vector<std::unique_ptr<Component>>>		m_componentPool;
	/// @brief コンポーネントのルックアップテーブル
	std::unordered_map<TypeID, std::unordered_map<InstanceID, std::size_t>> m_componentLookupTable;

	/// @brief 生成リスト
	std::unordered_map<TypeID, InstanceID>	m_createList;
	/// @brief 削除リスト
	std::unordered_map<TypeID, InstanceID>	m_destroyList;

	/// @brief アクティブコンポーネントリスト
	std::unordered_map<TypeID, std::vector<InstanceID>>						m_activeComponents;
	/// @brief アクティブコンポーネントテーブル
	std::unordered_map<TypeID, std::unordered_map<InstanceID, std::size_t>> m_activeComponentsTable;
	/// @brief 非アクティブコンポーネントリスト
	std::unordered_map<TypeID, std::vector<InstanceID>>						m_inactiveComponents;
	/// @brief 非アクティブコンポーネントテーブル
	std::unordered_map<TypeID, std::unordered_map<InstanceID, std::size_t>> m_inactiveComponentsTable;

};

#endif // !_COMPONENT_MANAGER_
