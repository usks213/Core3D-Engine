/*****************************************************************//**
 * \file   Scene.h
 * \brief  シーン
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#include "Scene.h"

#include "SceneManager.h"

#include <Core\Engine.h>
#include <RHI\Core\Device.h>

using namespace Core;

 /// @brief コンストラクタ
 /// @param pSceneManager シーンマネージャー
Scene::Scene(SceneManager* pSceneManager) noexcept :
	m_pSceneManager(pSceneManager)
{
	m_pEntityManager = std::make_unique<EntityManager>(this);
	m_pComponentManager = std::make_unique<ComponentManager>(this);
	m_pTransformManager = std::make_unique<TransformManager>(this);
	m_pSystemManager = std::make_unique<SystemManager>(this);
	//m_pPipelineManager = std::make_unique<PipelineManager>(this);

	float width = static_cast<float>(pSceneManager->GetEngine()->GetWindowWidth());
	float height = static_cast<float>(pSceneManager->GetEngine()->GetWindowHeight());

	// シーンリザルトの作成
	Core::TextureDesc rtDesc = {};
	rtDesc.name = "SceneResult";
	rtDesc.width = width;
	rtDesc.height = height;
	rtDesc.bindFlags = 0 | Core::BindFlags::RENDER_TARGET | Core::BindFlags::SHADER_RESOURCE;
	rtDesc.format = Core::TextureFormat::R8G8B8A8_UNORM;
	m_sceneResultID = pSceneManager->GetEngine()->GetRenderer()->GetDevice()->CreateRenderTarget(rtDesc);
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

/// @brief システムマネージャーの取得
/// @return システムマネージャーのポインタ
SystemManager* Scene::GetSystemManager() noexcept
{
	return m_pSystemManager.get();
}
