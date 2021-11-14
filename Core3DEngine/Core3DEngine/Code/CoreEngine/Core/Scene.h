/*****************************************************************//**
 * \file   Scene.h
 * \brief  �V�[��
 * 
 * \author USAMI KOSHI
 * \date   2021/11/14
 *********************************************************************/
#ifndef _SCENE_
#define _SCENE_

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
	explicit Scene(SceneManager* pSceneManager) :
		m_pSceneManager(pSceneManager)
	{
	}
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
	SceneManager* getSceneManager() noexcept { return m_pSceneManager; }

protected:
	//------------------------------------------------------------------------------
	// protected variables
	//------------------------------------------------------------------------------

	/// @brief ���[���h�}�l�[�W���[
	SceneManager* m_pSceneManager;
};

#endif // !_SCENE_
