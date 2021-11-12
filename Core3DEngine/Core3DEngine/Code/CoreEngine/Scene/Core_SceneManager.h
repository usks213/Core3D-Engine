/*****************************************************************//**
 * \file   Core_SceneManager.h
 * \brief  �V�[���}�l�[�W���[
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
	// �O��`
	class CoreEngine;

	class CoreSceneManager final
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit CoreSceneManager(CoreEngine* pEngiine) :
			m_pEngine(pEngiine), m_pScene(nullptr)
		{
		}

		/// @brief �f�X�g���N�^
		~CoreSceneManager() noexcept = default;

		/// @brief �R�s�[�R���X�g���N�^�폜
		CoreSceneManager(const CoreSceneManager&) = delete;
		/// @brief ���[�u�R���X�g���N�^�폜
		CoreSceneManager(CoreSceneManager&&) = delete;

		/// @brief �X�^�[�g
		void Start()
		{
			m_pScene->Start();
		}

		/// @brief �X�V
		void Update()
		{
			m_pScene->Update();
		}

		/// @brief �`��
		void Render()
		{
			m_pScene->Render();
		}

		/// @brief �G���h
		void End()
		{
			m_pScene->End();
		}

		/// @brief �V�[���̐���
		/// @tparam T �V�[���̌^
		template<class T, bool isBase = std::is_base_of_v<CoreScene, T>>
		void CreateScene()
		{
			static_assert(isBase, "Not CoreScene");
			m_pScene = std::make_unique<T>(this);
			Start();
		}

		/// @brief �G���W���̎擾
		/// @return �G���W���̃|�C���^
		CoreEngine* getEngine() { return m_pEngine; }

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		CoreEngine*					m_pEngine;	///< �G���W���̃|�C���^
		std::unique_ptr<CoreScene>	m_pScene;	///< �V�[���̃|�C���^

	};
}

#endif // !_CORE_SCENE_MANAGER_

