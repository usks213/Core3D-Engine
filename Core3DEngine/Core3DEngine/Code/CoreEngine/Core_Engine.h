/*****************************************************************//**
 * \file   Core_Engine.h
 * \brief  �G���W���N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_ENGINE_
#define _CORE_ENGINE_


#include <memory>
#include <chrono>

#include <CoreSystem\Utils\Util_Singleton.h>
#include <CoreSystem\Window\Core\Core_Window.h>
#include <CoreRenderer\Core\Core_Renderer.h>
#include <CoreEngine\Scene\Core_SceneManager.h>


namespace core
{

	/// @class CoreEngine
	/// @brief �G���W��
	class CoreEngine final : public util::UtilSingleton<CoreEngine>
	{
	private:
		friend util::UtilSingleton<CoreEngine>;

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
		/// @tparam CoreWindow�p���^�̂�
		/// @return �E�B���h�E�̃|�C���^
		template<class T, typename = std::enable_if_t<std::is_base_of_v<CoreWindow, T>>>
		T* createWindow(util::String windowName, int windowWidth, int windowHeight) {
			m_pWindow = std::make_unique<T>(windowName, windowWidth, windowHeight);
			m_pWindow->setCoreEngine(this);
			return static_cast<T*>(m_pWindow.get());
		}

		/// @brief �����_���[�̐���
		/// @tparam T �����_���[�^�C�v
		/// @tparam CoreRenderer�p���^�̂�
		/// @return �����_���[�̃|�C���^
		template<class T, typename = std::enable_if_t<std::is_base_of_v<CoreRenderer, T>>>
		T* createRenderer() {
			m_pRenderer = std::make_unique<T>();
			m_pRenderer->setCoreEngine(this);
			return static_cast<T*>(m_pRenderer.get());
		}

		/// @brief �E�B���h�E�̎擾
		/// @return �E�B���h�E�̃|�C���^
		[[nodiscard]] CoreWindow* getWindow() const noexcept { return m_pWindow.get(); }

		/// @brief �����_���[�擾
		/// @return �����_���[�̃|�C���^
		[[nodiscard]] CoreRenderer* getRenderer() const noexcept { return m_pRenderer.get(); }

		/// @brief �V�[���}�l�[�W���[�̎擾
		/// @return �V�[���}�l�[�W���[�̃|�C���^
		[[nodiscard]] CoreSceneManager* getSceneManager() const noexcept { return m_pSceneManager.get(); }

		/// @brief �E�B���h�E���擾
		/// @return �E�B���h�E��
		[[nodiscard]] util::String getWindowName() const noexcept { return m_pWindow->getWindowName(); }

		/// @brief �E�B���h�E�̕��擾
		/// @return �E�B���h�E�̕�(����)
		[[nodiscard]] int getWindowWidth() const noexcept { return m_pWindow->getWindowWidth(); }

		/// @brief �E�B���h�E�̍����擾
		/// @return �E�B���h�E�̍���(����)
		[[nodiscard]] int getWindowHeight() const noexcept { return m_pWindow->getWindowHeight(); }

		/// @brief ���݂̃t���[�����[�g�擾
		/// @return �t���[�����[�g(����)
		[[nodiscard]] std::uint32_t getCurrentFPS() const noexcept { return m_nCurrentFPS; }

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		CoreEngine();

		/// @brief �f�X�g���N�^
		~CoreEngine() = default;

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		std::unique_ptr<CoreWindow>				m_pWindow;			///< �E�B���h�E
		std::unique_ptr<CoreRenderer>			m_pRenderer;			///< �����_���[
		std::unique_ptr<CoreSceneManager>		m_pSceneManager;		///< �V�[���}�l�[�W���[

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
