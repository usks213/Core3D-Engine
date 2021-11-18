/*****************************************************************//**
 * \file   Scene.h
 * \brief  �V�[��
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

 /// @brief �R���X�g���N�^
 /// @param pSceneManager �V�[���}�l�[�W���[
Scene::Scene(SceneManager* pSceneManager) noexcept :
	m_pSceneManager(pSceneManager)
{
	m_pEntityManager = std::make_unique<EntityManager>(this);
	m_pComponentManager = std::make_unique<ComponentManager>(this);
	m_pTransformManager = std::make_unique<TransformManager>(this);
	m_pSystemManager = std::make_unique<SystemManager>(this);
	m_pPipelineManager = std::make_unique<PipelineManager>(this);
}