/*****************************************************************//**
 * \file   ComponentManager.h
 * \brief  コンポーネントマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/20
 *********************************************************************/
#include "ComponentManager.h"

using namespace Core;

 /// @brief コンポーネントを削除リストに登録
 /// @param typeID コンポーネントタイプID
 /// @param componentID コンポーネントID
void ComponentManager::DestroyComponent(const TypeID& typeID, const Component::ID& componentID)
{
	// 検索
	Component* pCom = FindComponent(typeID, componentID);
	if (pCom)
	{
		//　格納
		m_destroyList[typeID].push_back(componentID);
		// 削除時コールバック
		pCom->OnDestroy();
	}
}

/// @brief コンポーネントの検索
/// @param typeID コンポーネントタイプID
/// @param componentID コンポーネントID
/// @return コンポーネント型ポインタ or nullptr
Component* ComponentManager::FindComponent(const TypeID& typeID, const Component::ID& componentID)
{
	// 検索
	auto itr = m_componentLookupTable[typeID].find(componentID);
	if (m_componentLookupTable[typeID].end() == itr)
	{
		return nullptr;
	}
	return m_componentPool[typeID][itr->second].get();
}

/// @brief コンポーネントの有効指定
/// @param pComponent 対象のコンポーネントポインタ
/// @param isEnable 有効フラグ
void ComponentManager::SetComponentEnable(Component* pComponent, bool isEnable)
{
	//--- 各リストに存在したら削除
	auto typeID = pComponent->GetTypeID();
	auto comID = pComponent->GetComponentID();

	// 有効リスト
	auto enableItr = m_enableComponentsTable[typeID].find(comID);
	if (m_enableComponentsTable[typeID].end() != enableItr)
	{
		// 最後尾と入れ替え
		auto backComID = m_enableComponents[typeID].back();
		m_enableComponents[typeID][enableItr->second] = backComID;
		m_enableComponentsTable[typeID][backComID] = enableItr->second;
		// 削除
		m_enableComponents[typeID].pop_back();
		m_enableComponentsTable[typeID].erase(enableItr);
	}

	// 無効リスト
	auto disableItr = m_disableComponentsTable[typeID].find(comID);
	if (m_disableComponentsTable[typeID].end() != disableItr)
	{
		// 最後尾と入れ替え
		auto backComID = m_disableComponents[typeID].back();
		m_disableComponents[typeID][disableItr->second] = backComID;
		m_disableComponentsTable[typeID][backComID] = disableItr->second;
		// 削除
		m_disableComponents[typeID].pop_back();
		m_disableComponentsTable[typeID].erase(disableItr);
	}

	// 変更先に追加
	if (isEnable)
	{
		// 有効
		Index index = m_enableComponents[typeID].size();
		m_enableComponents[typeID].push_back(comID);
		m_enableComponentsTable[typeID].emplace(comID, index);
		//　コールバック
		pComponent->OnEnable();
	}
	else
	{
		// 無効
		Index index = m_disableComponents[typeID].size();
		m_disableComponents[typeID].push_back(comID);
		m_disableComponentsTable[typeID].emplace(comID, index);
		//　コールバック
		pComponent->OnDisable();
	}
}

/// @brief 削除リストの実行
void ComponentManager::CleanupComponent()
{
	for (auto& comList : m_destroyList)
	{
		auto typeID = comList.first;
		for (auto& comID : comList.second)
		{
			// 検索
			auto itr = m_componentLookupTable[typeID].find(comID);
			if (m_componentLookupTable[typeID].end() == itr) continue;

			// ID
			auto backComID = m_componentPool[typeID].back()->GetComponentID();
			// 最後尾と入れ替え
			m_componentPool[typeID][itr->second] = std::move(m_componentPool[typeID].back());
			m_componentLookupTable[typeID][backComID] = itr->second;

			// 削除
			m_componentPool[typeID].pop_back();
			m_componentLookupTable[typeID].erase(itr);
		}
	}
}

/// @brief 型ごとに一意なIDを作成
/// @param typeID 型ID
/// @return コンポーネントID
Component::ID ComponentManager::CreateComponentID(const TypeID& typeID)
{
	// ID作成
	Component::ID componentID = Component::NONE_ID;
	do
	{
		componentID = static_cast<Component::ID>(static_cast<BaseID>(rand()) % NONE_BASE_ID);
		auto itr = m_componentLookupTable[typeID].find(componentID);
		if (m_componentLookupTable[typeID].end() == itr)
		{
			break;
		}
	} while (true);

	return componentID;
}

/// @brief 生成リストに格納
/// @param pComponent コンポーネントポインタ
void ComponentManager::RegisterCreateList(Component* pComponent)
{
	// 生成リスト格納
	m_CreateList[pComponent->GetTypeID()].push_back(pComponent->GetComponentID());
	// 生成時コールバック
	pComponent->OnCreate();
}
