/*****************************************************************//**
 * \file   Core_SceneManager.h
 * \brief  シーンマネージャー
 * 
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/
#ifndef _CORE_SCENE_MANAGER_
#define _CORE_SCENE_MANAGER_

#include "Core_Scene.h"
#include <memory>

namespace core
{
	// 前定義
	class CoreEngine;

	class CoreSceneManager final
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit CoreSceneManager(CoreEngine* pEngiine) :
			m_pEngine(pEngiine), m_pScene(nullptr)
		{
		}

		/// @brief デストラクタ
		~CoreSceneManager() noexcept = default;

		/// @brief コピーコンストラクタ削除
		CoreSceneManager(const CoreSceneManager&) = delete;
		/// @brief ムーブコンストラクタ削除
		CoreSceneManager(CoreSceneManager&&) = delete;

		/// @brief スタート
		void Start()
		{
			m_pScene->Start();
		}

		/// @brief 更新
		void Update()
		{
			m_pScene->Update();
		}

		/// @brief 描画
		void Render()
		{
			m_pScene->Render();
		}

		/// @brief エンド
		void End()
		{
			m_pScene->End();
		}

		/// @brief シーンの生成
		/// @tparam T シーンの型
		template<class T, bool isBase = std::is_base_of_v<CoreScene, T>>
		void CreateScene()
		{
			static_assert(isBase, "Not CoreScene");
			m_pScene = std::make_unique<T>(this);
			Start();
		}

		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		CoreEngine* getEngine() { return m_pEngine; }

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		CoreEngine*					m_pEngine;	///< エンジンのポインタ
		std::unique_ptr<CoreScene>	m_pScene;	///< シーンのポインタ

	};
}

#endif // !_CORE_SCENE_MANAGER_

