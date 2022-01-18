/*****************************************************************//**
 * \file   ResourceManager.h
 * \brief  リソースマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _RESOURCE_MANAGER_
#define _RESOURCE_MANAGER_

#include "Resource.h"
#include <unordered_map>
#include <memory>


namespace Core
{
	class Engine;

	class ResourceManager final
	{
	public:
		/// @brief コンストラクタ
		/// @param pSceneManager シーンマネージャーポインタ
		explicit ResourceManager(Engine* pEngine) noexcept :
			m_pEngine(pEngine)
		{
		}

		/// @brief デストラクタ
		~ResourceManager() noexcept = default;

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

		/// @brief コンポーネントを削除リストに登録
		/// @param typeID コンポーネントタイプID
		/// @param componentID コンポーネントID
		void DestroyResource(const TypeID& typeID, const ResourceID& componentID);

		/// @brief コンポーネントの検索
		/// @param typeID コンポーネントタイプID
		/// @param componentID コンポーネントID
		/// @return コンポーネントポインタ or nullptr
		Resource* GetResource(const TypeID& typeID, const ResourceID& componentID);

		/// @brief コンポーネントの検索
		/// @tparam T コンポーネント型
		/// @param componentID コンポーネントID
		/// @return コンポーネント型ポインタ or nullptr
		template<class T, bool isComBase = std::is_base_of_v<Resource, T>>
		T* GetResource(const typename T::ID resourceID)
		{
			static_assert(isComBase, "Not ResourceBase");
			static constexpr TypeID typeID = static_cast<TypeID>(T::GetTypeHash());
			return static_cast<T*>(GetResource(typeID, componentID));
		}

		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		Engine* GetEngine() const noexcept { return m_pEngine; }

	private:

		/// @brief エンジンポインタ
		Engine* m_pEngine;

		std::unordered_map<TypeID, std::unordered_map<ResourceID, std::unique_ptr<Resource>>>	m_resourcePool;

	};
}

#endif // !_RESOURCE_MANAGER_

