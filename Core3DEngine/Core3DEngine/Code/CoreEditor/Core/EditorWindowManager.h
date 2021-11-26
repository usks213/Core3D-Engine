/*****************************************************************//**
 * \file   EditorWindowManager.h
 * \brief  エディターウィンドウマネージャー
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _EDITOR_WINDOW_MANAGER_
#define _EDITOR_WINDOW_MANAGER_

#include "EditorWindow.h"
#include <unordered_map>
#include <memory>

namespace core
{
	class CoreEditor;
}

/// @brief エディターウィンドウマネージャークラス
class EditorWindowManager final
{
public:
	/// @brief コンストラクタ
	/// @param pCoreEditor コアエディターポインタ
	explicit EditorWindowManager(core::CoreEditor* pCoreEditor) noexcept :
		m_pCoreEditor(pCoreEditor)
	{
	}

	/// @brief デストラクタ
	~EditorWindowManager() noexcept = default;

	/// @brief ウィンドウの表示
	void DispWindow()
	{
		for (auto& window : m_windowPool)
		{
			//window.second->DispWindow();
		}
	}

	/// @brief エディターウィンドウの追加
	/// @tparam T エディターウィンドウ型
	/// @return 生成したエディターウィンドウ
	template<class T, typename = std::enable_if_t<std::is_base_of_v<EditorWindow, T>>>
	T* AddEditorWindow()
	{
		static constexpr TypeHash typeHash = T::GetTypeHash();
		// 検索
		auto itr = m_windowPool.find(typeHash);
		if (m_windowPool.end() != itr)
		{
			return static_cast<T*>(itr->second.get());
		}
		// 新規生成
		auto pWindow = std::make_unique<T>();
		auto* pResult = pWindow.get();
		pResult->m_pManager = this;
		// 格納
		m_windowPool.emplace(typeHash, std::move(pWindow));

		return pResult;
	}

	/// @brief エディターウィンドウの検索
	/// @tparam T エディターウィンドウ型
	/// @return 一致したエディターウィンドウ
	template<class T, typename = std::enable_if_t<std::is_base_of_v<EditorWindow, T>>>
	T* GetEditorWindow()
	{
		static constexpr TypeHash typeHash = T::GetTypeHash();
		// 検索
		auto itr = m_windowPool.find(typeHash);
		if (m_windowPool.end() != itr)
		{
			return static_cast<T*>(itr->second.get());
		}

		return nullptr;
	}

	/// @brief コアエディターの取得
	/// @return コアエディターポインタ
	core::CoreEditor* GetCoreEditor() { return m_pCoreEditor; }

private:

	/// @brief コアエディター
	core::CoreEditor* m_pCoreEditor;

	/// @brief 型種別のエディターウィンドウ
	std::unordered_map<TypeHash, std::unique_ptr<EditorWindow>>	m_windowPool;

};


#endif // !_EDITOR_WINDOW_MANAGER_

