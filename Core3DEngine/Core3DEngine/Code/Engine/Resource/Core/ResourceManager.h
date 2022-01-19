/*****************************************************************//**
 * \file   ResourceManager.h
 * \brief  リソースマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include <Utils\Util_Singleton.h>
#include "Resource.h"
#include <unordered_map>
#include <memory>


namespace Core
{
	class ResourceManager final : public Util::Singleton<ResourceManager>
	{
	public:
		/// @brief リソースの生成
		/// @tparam T リソース型
		/// @return 生成したrリソース型ポインタ
		template<class T, bool isResourceBase = std::is_base_of_v<Resource, T>>
		T* CreateResource()
		{
			static_assert(isResourceBase, "Not ResourceBase");
			static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
			// 生成
			auto pResource = std::make_unique<T>();
			auto pResult = pResource.get();
			pResult->m_pResourceManager = this;
			pResult->m_instanceID = static_cast<InstanceID>(CreateResourceID(typeID));
			// 格納
			m_resourcePool[typeID].emplace(pResult->GetResourceID(), std::move(pResource));

			return pResult;
		}

		/// @brief リソースを削除リストに登録
		/// @tparam T リソース型
		/// @param typeID リソースタイプID
		/// @param resourceID リソースID
		template<class T, bool isResourceBase = std::is_base_of_v<Resource, T>>
		T* DestroyResource(const typename T::ID resourceID)
		{
			static_assert(isResourceBase, "Not ResourceBase");
			static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
			return static_cast<T*>(DestroyResource(typeID, static_cast<Resource::ID>(resourceID)));
		}

		/// @brief リソースの検索
		/// @tparam T リソース型
		/// @param resourceID リソースID
		/// @return リソース型ポインタ or nullptr
		template<class T, class U, bool isResourceBase = std::is_base_of_v<Resource, T>, 
			bool isID = std::is_same_v<typename T::ID, U>>
		T* GetResource(const U resourceID)
		{
			static_assert(isResourceBase, "Not ResourceBase");
			static_assert(isID, "Not ID");
			static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
			return static_cast<T*>(GetResource(typeID, static_cast<Resource::ID>(resourceID)));
		}

		/// @brief リソースを削除リストに登録
		/// @param typeID リソースタイプID
		/// @param resourceID リソースID
		void DestroyResource(const TypeID& typeID, const Resource::ID& resourceID);

		/// @brief リソースの検索
		/// @param typeID リソースタイプID
		/// @param resourceID リソースID
		/// @return リソースポインタ or nullptr
		Resource* GetResource(const TypeID& typeID, const Resource::ID& resourceID);

		/// @brief 削除リストの実行
		void CleanupResource();

	private:

		/// @brief リソースプール
		std::unordered_map<TypeID, std::unordered_map<Resource::ID, std::unique_ptr<Resource>>>	m_resourcePool;

		/// @brief 削除リスト
		std::unordered_map<TypeID, std::vector<Resource::ID>>					m_destroyList;
	};
}

#endif // !_RESOURCE_MANAGER_

