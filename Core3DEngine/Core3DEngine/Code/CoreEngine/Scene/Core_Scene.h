/*****************************************************************//**
 * \file   Core_Scene.h
 * \brief  �V�[��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/
#ifndef _CORE_SCENE_
#define _CORE_SCENE_

namespace core
{
	// �O��`
	class CoreSceneManager;

	class CoreScene
	{
		friend class CoreSceneManager;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param pSceneManager �V�[���}�l�[�W���[
		explicit CoreScene(CoreSceneManager* pSceneManager) :
			m_pSceneManager(pSceneManager)
		{
		}
		/// @brief �f�X�g���N�^
		virtual ~CoreScene() noexcept = default;

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
		CoreSceneManager* getSceneManager() noexcept { return m_pSceneManager; }

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		/// @brief ���[���h�}�l�[�W���[
		CoreSceneManager* m_pSceneManager;
	};
}

#endif // !_CORE_SCENE_
