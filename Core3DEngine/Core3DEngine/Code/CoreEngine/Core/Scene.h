/*****************************************************************//**
 * \file   Scene.h
 * \brief  シーン
 * 
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _SCENE_
#define _SCENE_

// 前定義
class SceneManager;

/// @brief シーン
class Scene
{
	friend class SceneManager;
public:
	//------------------------------------------------------------------------------
	// public methods
	//------------------------------------------------------------------------------

	/// @brief コンストラクタ
	/// @param pSceneManager シーンマネージャー
	explicit Scene(SceneManager* pSceneManager) :
		m_pSceneManager(pSceneManager)
	{
	}
	/// @brief デストラクタ
	virtual ~Scene() noexcept = default;

	/// @brief スタート
	virtual void Start() = 0;

	/// @brief システムの更新
	virtual void Update() = 0;

	/// @brief パイプラインの描画
	virtual void Render() = 0;

	/// @brief エンド
	virtual void End() = 0;


	/// @brief シーンマネージャーの取得
	/// @return シーンマネージャーのポインタ
	SceneManager* getSceneManager() noexcept { return m_pSceneManager; }

protected:
	//------------------------------------------------------------------------------
	// protected variables
	//------------------------------------------------------------------------------

	/// @brief ワールドマネージャー
	SceneManager* m_pSceneManager;
};

#endif // !_SCENE_
