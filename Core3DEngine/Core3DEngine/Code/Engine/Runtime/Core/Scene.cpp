/*****************************************************************//**
 * \file   Scene.h
 * \brief  �V�[��
 *
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#include "Scene.h"

#include "SceneManager.h"

#include <CoreEngine\Core_Engine.h>
#include <CoreRenderer\Core\Core_Device.h>

 /// @brief �R���X�g���N�^
 /// @param pSceneManager �V�[���}�l�[�W���[
Scene::Scene(SceneManager* pSceneManager) noexcept :
	m_pSceneManager(pSceneManager)
{
	m_pEntityManager = std::make_unique<EntityManager>(this);
	m_pComponentManager = std::make_unique<ComponentManager>(this);
	m_pTransformManager = std::make_unique<TransformManager>(this);
	m_pSystemManager = std::make_unique<SystemManager>(this);
	//m_pPipelineManager = std::make_unique<PipelineManager>(this);

	float width = static_cast<float>(pSceneManager->getEngine()->getWindowWidth());
	float height = static_cast<float>(pSceneManager->getEngine()->getWindowHeight());

	// �V�[�����U���g�̍쐬
	core::TextureDesc rtDesc = {};
	rtDesc.name = "SceneResult";
	rtDesc.width = width;
	rtDesc.height = height;
	rtDesc.bindFlags = 0 | core::BindFlags::RENDER_TARGET | core::BindFlags::SHADER_RESOURCE;
	rtDesc.format = core::TextureFormat::R8G8B8A8_UNORM;
	m_sceneResultID = pSceneManager->getEngine()->getRenderer()->getDevice()->createRenderTarget(rtDesc);
}

/// @brief �G���e�B�e�B�}�l�[�W���[�̎擾
/// @return �G���e�B�e�B�}�l�[�W���[�̃|�C���^
EntityManager* Scene::GetEntityManager() noexcept 
{ 
	return m_pEntityManager.get();
}

/// @brief �R���|�[�l���g�}�l�[�W���[�̎擾
/// @return �R���|�[�l���g�}�l�[�W���[�̃|�C���^
ComponentManager* Scene::GetComponentManager() noexcept
{ 
	return m_pComponentManager.get(); 
}

/// @brief �g�����X�t�H�[���}�l�[�W���[�̎擾
/// @return �g�����X�t�H�[���}�l�[�W���[�̃|�C���^
TransformManager* Scene::GetTransformManager() noexcept 
{ 
	return m_pTransformManager.get();
}

/// @brief �V�X�e���}�l�[�W���[�̎擾
/// @return �V�X�e���}�l�[�W���[�̃|�C���^
SystemManager* Scene::GetSystemManager() noexcept
{
	return m_pSystemManager.get();
}
