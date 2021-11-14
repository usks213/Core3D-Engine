/*****************************************************************//**
 * \file   TestScene.h
 * \brief  �e�X�g�V�[��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/
#ifndef _TEST_SCENE_
#define _TEST_SCENE_

#include <CoreEngine/Core/Scene.h>

class TestScene :public Scene
{
public:
	//------------------------------------------------------------------------------
	// public methods
	//------------------------------------------------------------------------------

	/// @brief �R���X�g���N�^
	/// @param pSceneManager �V�[���}�l�[�W���[
	explicit TestScene(SceneManager* pSceneManager) :
		Scene(pSceneManager)
	{
	}
	/// @brief �f�X�g���N�^
	virtual ~TestScene() noexcept = default;


	/// @brief �X�^�[�g
	void Start() override;

	/// @brief �V�X�e���̍X�V
	void Update() override;

	/// @brief �p�C�v���C���̕`��
	void Render() override;

	/// @brief �G���h
	void End() override;

private:

};


#endif // !_TEST_SCENE_
