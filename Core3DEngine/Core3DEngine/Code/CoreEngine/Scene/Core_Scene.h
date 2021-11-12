/*****************************************************************//**
 * \file   Core_Scene.h
 * \brief  シーン
 * 
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/
#ifndef _CORE_SCENE_
#define _CORE_SCENE_

namespace core
{
	// 前定義
	class CoreSceneManager;

	class CoreScene
	{
		friend class CoreSceneManager;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param pSceneManager シーンマネージャー
		explicit CoreScene(CoreSceneManager* pSceneManager) :
			m_pSceneManager(pSceneManager)
		{
		}
		/// @brief デストラクタ
		virtual ~CoreScene() noexcept = default;

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
		CoreSceneManager* getSceneManager() noexcept { return m_pSceneManager; }

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		/// @brief ワールドマネージャー
		CoreSceneManager* m_pSceneManager;
	};
}

#endif // !_CORE_SCENE_
