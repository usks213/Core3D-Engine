/*****************************************************************//**
 * \file   SceneManager.h
 * \brief  シーンマネージャー
 * 
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include "Scene.h"
#include <memory>


// 前定義
class core::CoreEngine;

/// @brief シーンマネージャ
class SceneManager final
{
public:
	//------------------------------------------------------------------------------
	// public methods
	//------------------------------------------------------------------------------

	/// @brief コンストラクタ
	explicit SceneManager(core::CoreEngine* pEngiine) :
		m_pEngine(pEngiine), m_pScene(nullptr)
	{
	}

	/// @brief デストラクタ
	~SceneManager() noexcept = default;

	/// @brief コピーコンストラクタ削除
	SceneManager(const SceneManager&) = delete;
	/// @brief ムーブコンストラクタ削除
	SceneManager(SceneManager&&) = delete;

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
	template<class T, bool isBase = std::is_base_of_v<Scene, T>>
	void CreateScene()
	{
		static_assert(isBase, "Not Scene");
		m_pScene = std::make_unique<T>(this);
		Start();
	}

	/// @brief 現在のシーン取得
	/// @return シーンのポインタ
	Scene* GetCurrentScene() { return m_pScene.get(); }

	/// @brief エンジンの取得
	/// @return エンジンのポインタ
	core::CoreEngine* getEngine() { return m_pEngine; }

private:
	//------------------------------------------------------------------------------
	// private variables
	//------------------------------------------------------------------------------

	core::CoreEngine*		m_pEngine;	///< エンジンのポインタ
	std::unique_ptr<Scene>	m_pScene;	///< シーンのポインタ

};

#endif // !_SCENE_MANAGER_

