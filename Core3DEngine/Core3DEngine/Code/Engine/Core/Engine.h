/*****************************************************************//**
 * \file   Engine.h
 * \brief  �G���W���N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_ENGINE_
#define _CORE_ENGINE_

#include <memory>
#include <chrono>

#include <Utils\Util_Singleton.h>
#include <Window\Core\Window.h>
#include <RHI\Core\RHI_Renderer.h>
#include <Editor\Core\Editor.h>
#include <Runtime\Core\SceneManager.h>

#ifdef CreateWindow
#undef CreateWindow
#endif // CreateWindow

namespace Core
{
	/// @class Engine
	/// @brief �G���W��
	class Engine final : public Util::Singleton<Engine>
	{
	private:
		friend Util::Singleton<Engine>;

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief ����������
		/// @return ������: ���� true | ���s false
		[[nodiscard]] bool initialize();

		/// @brief �X�V�֐�
		void tick();

		/// @brief �I������
		void finalize();

		/// @brief �E�B���h�E�̐���
		/// @tparam T �E�B���h�E�^�C�v
		/// @tparam Window�p���^�̂�
		/// @return �E�B���h�E�̃|�C���^
		template<class T, typename = std::enable_if_t<std::is_base_of_v<Window, T>>>
		T* CreateWindow(Util::String windowName, std::uint32_t windowWidth, std::uint32_t windowHeight)
		{
			m_pWindow = std::make_unique<T>(windowName, windowWidth, windowHeight);
			m_pWindow->SetEngine(this);
			return static_cast<T*>(m_pWindow.get());
		}

		/// @brief �����_���[�̐���
		/// @tparam T �����_���[�^�C�v
		/// @tparam RHI::Renderer�p���^�̂�
		/// @return �����_���[�̃|�C���^
		template<class T, typename = std::enable_if_t<std::is_base_of_v<RHI::Renderer, T>>>
		T* CreateRenderer() {
			m_pRenderer = std::make_unique<T>();
			m_pRenderer->SetEngine(this);
			return static_cast<T*>(m_pRenderer.get());
		}

		/// @brief �G�f�B�^�[�̐���
		/// @tparam T �G�f�B�^�[�^�C�v
		/// @tparam Editor�p���^�̂�
		/// @return �G�f�B�^�[�̃|�C���^
		template<class T, typename = std::enable_if_t<std::is_base_of_v<Editor, T>>>
		T* CreateEditor() {
			m_pEditor = std::make_unique<T>();
			m_pEditor->SetEngine(this);
			return static_cast<T*>(m_pEditor.get());
		}

		/// @brief �E�B���h�E�̎擾
		/// @return �E�B���h�E�̃|�C���^
		[[nodiscard]] Window* GetWindow() const noexcept { return m_pWindow.get(); }

		/// @brief �����_���[�擾
		/// @return �����_���[�̃|�C���^
		[[nodiscard]] RHI::Renderer* GetRenderer() const noexcept { return m_pRenderer.get(); }

		/// @brief �G�f�B�^�[�擾
		/// @return �G�f�B�^�[�̃|�C���^
		[[nodiscard]] Editor* GetEditor() const noexcept { return m_pEditor.get(); }

		/// @brief �V�[���}�l�[�W���[�̎擾
		/// @return �V�[���}�l�[�W���[�̃|�C���^
		[[nodiscard]] SceneManager* GetSceneManager() const noexcept { return m_pSceneManager.get(); }

		/// @brief �E�B���h�E���擾
		/// @return �E�B���h�E��
		[[nodiscard]] Util::String GetWindowName() const noexcept { return m_pWindow->GetWindowName(); }

		/// @brief �E�B���h�E�̕��擾
		/// @return �E�B���h�E�̕�(����)
		[[nodiscard]] int GetWindowWidth() const noexcept { return m_pWindow->GetWindowWidth(); }

		/// @brief �E�B���h�E�̍����擾
		/// @return �E�B���h�E�̍���(����)
		[[nodiscard]] int GetWindowHeight() const noexcept { return m_pWindow->GetWindowHeight(); }

		/// @brief ���݂̃t���[�����[�g�擾
		/// @return �t���[�����[�g(����)
		[[nodiscard]] std::uint32_t GetCurrentFPS() const noexcept { return m_nCurrentFPS; }

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		Engine();

		/// @brief �f�X�g���N�^
		~Engine() = default;

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		std::unique_ptr<Window>					m_pWindow;				///< �E�B���h�E
		std::unique_ptr<RHI::Renderer>			m_pRenderer;			///< �����_���[
		std::unique_ptr<Editor>					m_pEditor;				///< �G�f�B�^�[

		std::unique_ptr<SceneManager>			m_pSceneManager;		///< �V�[���}�l�[�W���[
		///< ���\�[�X�}�l�[�W���[
		///< �G�f�B�^�}�l�[�W���[

		//--- �^�C�}�[ 
		// �����ꂪ�����Ƃ��������x
		// std::chrono::high_resolution_clock;

		std::uint32_t							m_nCurrentFPS;			///< ���݂�FPS
		std::uint64_t							m_nFrameCount;			///< �t���[�����[�g�J�E���^
		std::chrono::system_clock::time_point	m_FixedExecLastTime;	///< ���X�V�̑O���� 
		std::chrono::system_clock::time_point	m_ExecLastTime;			///< �ʏ�X�V�̑O����
		std::chrono::system_clock::time_point	m_FPSLastTime;			///< FPS�v���p�̑O����
		std::chrono::system_clock::time_point	m_CurrentTime;			///< ���݂̎���

		float									m_deltaTime;			///< �ʏ�X�V�̒P�ʎ���
		float									m_fixedDeltaTime;		///< ���X�V�̒P�ʎ���
		std::int32_t							m_nMaxFPS;				///< �ő�FPS
		std::int64_t							m_nFixedTime;			///< ���X�V�̎���
	};

}

#endif // !_CORE_ENGINE_
