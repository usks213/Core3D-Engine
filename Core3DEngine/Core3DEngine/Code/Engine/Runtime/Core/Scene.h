/*****************************************************************//**
 * \file   Scene.h
 * \brief  シーン
 * 
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _SCENE_
#define _SCENE_

#include <memory>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "TransformManager.h"
#include "SystemManager.h"

namespace Core
{
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
		explicit Scene(SceneManager* pSceneManager) noexcept;

		/// @brief デストラクタ
		virtual ~Scene() noexcept = default;

		/// @brief スタート
		virtual void Start() {}

		/// @brief システムの更新
		virtual void Update() {}

		/// @brief パイプラインの描画
		virtual void Render() {}

		/// @brief エンド
		virtual void End() {}


		/// @brief シーンマネージャーの取得
		/// @return シーンマネージャーのポインタ
		SceneManager* GetSceneManager() noexcept { return m_pSceneManager; }

		/// @brief エンティティマネージャーの取得
		/// @return エンティティマネージャーのポインタ
		EntityManager* GetEntityManager() noexcept;

		/// @brief コンポーネントマネージャーの取得
		/// @return コンポーネントマネージャーのポインタ
		ComponentManager* GetComponentManager() noexcept;

		/// @brief トランスフォームマネージャーの取得
		/// @return トランスフォームマネージャーのポインタ
		TransformManager* GetTransformManager() noexcept;

		/// @brief システムマネージャーの取得
		/// @return システムマネージャーのポインタ
		SystemManager* GetSystemManager() noexcept;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		/// @brief シーンマネージャー
		SceneManager* m_pSceneManager;

		std::unique_ptr<EntityManager>		m_pEntityManager;
		std::unique_ptr<ComponentManager>	m_pComponentManager;
		std::unique_ptr<TransformManager>	m_pTransformManager;
		std::unique_ptr<SystemManager>		m_pSystemManager;
		//std::unique_ptr<PipelineManager>	m_pPipelineManager;

	};
}

#endif // !_SCENE_
