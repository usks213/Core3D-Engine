/*****************************************************************//**
 * \file   Scene.h
 * \brief  �V�[��
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

#include <Resource\Core\RenderTarget.h>

namespace Core
{
	// �O��`
	class SceneManager;

	/// @brief �V�[��
	class Scene
	{
		friend class SceneManager;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param pSceneManager �V�[���}�l�[�W���[
		explicit Scene(SceneManager* pSceneManager) noexcept;

		/// @brief �f�X�g���N�^
		virtual ~Scene() noexcept = default;

		/// @brief �X�^�[�g
		virtual void Start() = 0;

		/// @brief �V�X�e���̍X�V
		virtual void Update() = 0;

		/// @brief �p�C�v���C���̕`��
		virtual void Render() = 0;

		/// @brief �G���h
		virtual void End() = 0;


		/// @brief �V�[���}�l�[�W���[�̎擾
		/// @return �V�[���}�l�[�W���[�̃|�C���^
		SceneManager* GetSceneManager() noexcept { return m_pSceneManager; }

		/// @brief �G���e�B�e�B�}�l�[�W���[�̎擾
		/// @return �G���e�B�e�B�}�l�[�W���[�̃|�C���^
		EntityManager* GetEntityManager() noexcept;

		/// @brief �R���|�[�l���g�}�l�[�W���[�̎擾
		/// @return �R���|�[�l���g�}�l�[�W���[�̃|�C���^
		ComponentManager* GetComponentManager() noexcept;

		/// @brief �g�����X�t�H�[���}�l�[�W���[�̎擾
		/// @return �g�����X�t�H�[���}�l�[�W���[�̃|�C���^
		TransformManager* GetTransformManager() noexcept;

		/// @brief �V�X�e���}�l�[�W���[�̎擾
		/// @return �V�X�e���}�l�[�W���[�̃|�C���^
		SystemManager* GetSystemManager() noexcept;

		/// @brief �V�[���̕`�挋�ʂ��擾
		/// @return �����_�[�^�[�Q�b�gID
		Core::RenderTargetID GetSceneResult() { return m_sceneResultID; }

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		Core::RenderTargetID				m_sceneResultID;

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		/// @brief �V�[���}�l�[�W���[
		SceneManager* m_pSceneManager;

		std::unique_ptr<EntityManager>		m_pEntityManager;
		std::unique_ptr<ComponentManager>	m_pComponentManager;
		std::unique_ptr<TransformManager>	m_pTransformManager;
		std::unique_ptr<SystemManager>		m_pSystemManager;
		//std::unique_ptr<PipelineManager>	m_pPipelineManager;

	};
}

#endif // !_SCENE_
