/*****************************************************************//**
 * \file   Scene.h
 * \brief  シーン
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#include "Scene.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "TransformManager.h"
#include "SystemManager.h"
#include "PipelineManager.h"

 /// @brief コンストラクタ
 /// @param pSceneManager シーンマネージャー
Scene::Scene(SceneManager* pSceneManager) noexcept :
	m_pSceneManager(pSceneManager)
{
	m_pEntityManager = std::make_unique<EntityManager>(this);
	m_pComponentManager = std::make_unique<ComponentManager>(this);
	m_pTransformManager = std::make_unique<TransformManager>(this);
	//m_pSystemManager = std::make_unique<SystemManager>(this);
	//m_pPipelineManager = std::make_unique<PipelineManager>(this);
}

/// @brief エンティティマネージャーの取得
/// @return エンティティマネージャーのポインタ
EntityManager* Scene::GetEntityManager() noexcept 
{ 
	return m_pEntityManager.get();
}

/// @brief コンポーネントマネージャーの取得
/// @return コンポーネントマネージャーのポインタ
ComponentManager* Scene::GetComponentManager() noexcept
{ 
	return m_pComponentManager.get(); 
}

/// @brief トランスフォームマネージャーの取得
/// @return トランスフォームマネージャーのポインタ
TransformManager* Scene::GetTransformManager() noexcept 
{ 
	return m_pTransformManager.get();
}
