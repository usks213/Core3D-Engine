/*****************************************************************//**
 * \file   Core_Window.h
 * \brief  �E�B���h�E�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_WINDOW_
#define _CORE_WINDOW_

#include <CoreSystem\Utils\Core_String.h>

namespace core
{
	// �O��`
	class CoreEngine;

	/// @class CoreWindow
	/// @brief �R�A�E�B���h�E�N���X
	class CoreWindow
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param windowName[in] �E�B���h�E��
		/// @param windowWidth[in] �E�B���h�E�̕�
		/// @param windowHeight[in] �E�B���h�E�̍���
		explicit CoreWindow(CoreString windowName, std::uint32_t windowWidth, std::uint32_t windowHeight);

		/// @brief �f�X�g���N�^
		virtual ~CoreWindow() noexcept = default;

		/// @brief �I������
		virtual void finalize() = 0;

		/// @brief �E�B���h�E���擾
		/// @return �E�B���h�E��
		[[nodiscard]] CoreString getWindowName() const noexcept { return m_windowName; }

		/// @brief �E�B���h�E�̕��擾
		/// @return �E�B���h�E�̕�(����)
		[[nodiscard]] int getWindowWidth() const noexcept { return m_windowWidth; }

		/// @brief �E�B���h�E�̍����擾
		/// @return �E�B���h�E�̍���(����)
		[[nodiscard]] int getWindowHeight() const noexcept { return m_windowHeight; }

		/// @brief �G���W���̎擾
		/// @return �G���W���̃|�C���^
		CoreEngine* getCoreEngine() const noexcept { return m_pCoreEngine; }

		/// @brief �G���W���̐ݒ�
		/// @param pCoreEngine �G���W���̃|�C���^
		void setCoreEngine(CoreEngine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief �R�s�[�R���X�g���N�^�폜
		CoreWindow(const CoreWindow&) = delete;
		/// @brief ���[�u�R���X�g���N�^�폜
		CoreWindow(CoreWindow&&) = delete;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		CoreEngine*		m_pCoreEngine;			///< �G���W���̃|�C���^
		CoreString		m_windowName;		///< �E�B���h�E��
		int				m_windowWidth;		///< �E�B���h�E�̕�
		int				m_windowHeight;		///< �E�B���h�E�̍���
	};
}

#endif // !_CORE_WINDOW_
