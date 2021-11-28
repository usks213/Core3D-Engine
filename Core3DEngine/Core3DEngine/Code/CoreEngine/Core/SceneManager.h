/*****************************************************************//**
 * \file   SceneManager.h
 * \brief  �V�[���}�l�[�W���[
 * 
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include "Scene.h"
#include <memory>

// �O��`
namespace core
{
	class CoreEngine;
}

/// @brief �V�[���}�l�[�W��
class SceneManager final
{
public:
	//------------------------------------------------------------------------------
	// public methods
	//------------------------------------------------------------------------------

	/// @brief �R���X�g���N�^
	explicit SceneManager(core::CoreEngine* pEngiine) :
		m_pEngine(pEngiine), m_pScene(nullptr)
	{
	}

	/// @brief �f�X�g���N�^
	~SceneManager() noexcept = default;

	/// @brief �R�s�[�R���X�g���N�^�폜
	SceneManager(const SceneManager&) = delete;
	/// @brief ���[�u�R���X�g���N�^�폜
	SceneManager(SceneManager&&) = delete;

	/// @brief �X�^�[�g
	void Start()
	{
		m_pScene->Start();
	}

	/// @brief �X�V
	void Update()
	{
		m_pScene->Update();
		m_pScene->GetSystemManager()->Update();
	}

	/// @brief �`��
	void Render()
	{
		m_pScene->Render();
		m_pScene->GetSystemManager()->DispGizmo();
	}

	/// @brief �G���h
	void End()
	{
		m_pScene->End();
	}

	/// @brief �V�[���̐���
	/// @tparam T �V�[���̌^
	template<class T, bool isBase = std::is_base_of_v<Scene, T>>
	void CreateScene()
	{
		static_assert(isBase, "Not Scene");
		m_pScene = std::make_unique<T>(this);
		Start();
	}

	/// @brief ���݂̃V�[���擾
	/// @return �V�[���̃|�C���^
	Scene* GetCurrentScene() { return m_pScene.get(); }

	/// @brief �G���W���̎擾
	/// @return �G���W���̃|�C���^
	core::CoreEngine* getEngine() { return m_pEngine; }

private:
	//------------------------------------------------------------------------------
	// private variables
	//------------------------------------------------------------------------------

	core::CoreEngine*		m_pEngine;	///< �G���W���̃|�C���^
	std::unique_ptr<Scene>	m_pScene;	///< �V�[���̃|�C���^

};

#endif // !_SCENE_MANAGER_

