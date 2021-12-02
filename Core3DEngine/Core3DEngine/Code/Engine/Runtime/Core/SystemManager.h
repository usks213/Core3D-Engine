/*****************************************************************//**
 * \file   SystemManager.h
 * \brief  システム
 *
 * \author USAMI KOSHI
 * \date   2021/11/28
 *********************************************************************/
#ifndef _SYSTEM_MANAGER_
#define _SYSTEM_MANAGER_

#include "System.h"
#include <unordered_map>
#include <memory>

namespace Core
{
	class Scene;

	class SystemManager final
	{
	public:
		/// @brief コンストラクタ
		/// @param pScene シーンポインタ
		explicit SystemManager(Scene* pScene);

		/// @brief デストラクタ
		~SystemManager() noexcept = default;

		/// @brief システム更新
		void Update();

		/// @brief ギズモ表示
		void DispGizmo();

		/// @brief システムの追加
		/// @tparam T システム継承型
		/// @return 生成したシステム
		template<class T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T* AddSystem()
		{
			static constexpr SystemID systemID = static_cast<SystemID>(T::GetTypeHash());
			// 検索
			auto itr = m_systemPool.find(systemID);
			if (m_systemPool.end() != itr)
				return static_cast<T*>(itr->second.get());
			// 新規生成
			auto pSystem = std::make_unique<T>(this);
			T* pResult = pSystem.get();
			// 格納
			m_systemPool.emplace(systemID, std::move(pSystem));

			return pResult;
		}

		/// @brief システムの取得
		/// @tparam T システム継承型
		/// @return 一致 T* or 不一致 nullptr
		template<class T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		T* GetSystem()
		{
			static constexpr SystemID systemID = static_cast<SystemID>(T::GetTypeHash());
			// 検索
			auto itr = m_systemPool.find(systemID);
			// 一致
			if (m_systemPool.end() != itr)
				return  static_cast<T*>(itr->second.get());
			// 不一致
			return nullptr;
		}

		/// @brief システムの削除
		/// @tparam T システム継承型
		/// @return 成功 TRUE / 失敗 FALSE
		template<class T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		bool RemoveSystem()
		{
			static constexpr SystemID systemID = static_cast<SystemID>(T::GetTypeHash());
			// 検索
			auto itr = m_systemPool.find(systemID);
			// 一致
			if (m_systemPool.end() != itr)
			{
				m_systemPool.erase(itr);
				return true;
			}
			return false;
		}

		/// @brief 所属シーンの取得
		/// @return シーンポインタ
		Scene* GetScene() { return m_pScene; }

	private:
		/// @brief 所属シーン
		Scene* m_pScene;
		/// @brief システムプール
		std::unordered_map<SystemID, std::unique_ptr<System>> m_systemPool;
	};
}

#endif // !_SYSTEM_MANAGER_
