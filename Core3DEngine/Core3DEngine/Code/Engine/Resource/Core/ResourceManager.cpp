/*****************************************************************//**
 * \file   ResourceManager.h
 * \brief  リソースマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#include "ResourceManager.h"

using namespace Core;

 /// @brief リソースを削除リストに登録
 /// @param typeID リソースタイプID
 /// @param resourceID リソースID
void ResourceManager::DestroyResource(const TypeID& typeID, const ResourceID& resourceID)
{
	// 検索
	Resource* pResource = GetResource(typeID, resourceID);
	if (pResource)
	{
		//　格納
		m_destroyList[typeID].push_back(resourceID);
	}
}

/// @brief リソースの検索
/// @param typeID リソースタイプID
/// @param resourceID リソースID
/// @return リソースポインタ or nullptr
Resource* ResourceManager::GetResource(const TypeID& typeID, const ResourceID& resourceID)
{
	// 検索
	auto itr = m_resourcePool[typeID].find(resourceID);
	if (m_resourcePool[typeID].end() == itr)
	{
		return nullptr;
	}
	return itr->second.get();
}

/// @brief 削除リストの実行
void ResourceManager::CleanupResource()
{
	for (auto& resoures : m_destroyList)
	{
		auto typeID = resoures.first;
		for (auto& id : resoures.second)
		{
			// 検索
			auto itr = m_resourcePool[typeID].find(id);
			if (m_resourcePool[typeID].end() == itr) continue;

			// 削除
			m_resourcePool[typeID].erase(itr);
		}
	}
}
