/*****************************************************************//**
 * \file   Window.h
 * \brief  �E�B���h�E�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_WINDOW_
#define _CORE_WINDOW_

#include <Utils/Util_String.h>

namespace Core
{
	// �O��`
	class Engine;

	/// @class Window
	/// @brief �R�A�E�B���h�E�N���X
	class Window
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param windowName[in] �E�B���h�E��
		/// @param windowWidth[in] �E�B���h�E�̕�
		/// @param windowHeight[in] �E�B���h�E�̍���
		explicit Window(Util::String windowName, std::uint32_t windowWidth, std::uint32_t windowHeight);

		/// @brief �f�X�g���N�^
		virtual ~Window() noexcept = default;

		/// @brief �I������
		virtual void finalize() = 0;

		/// @brief �E�B���h�E���擾
		/// @return �E�B���h�E��
		[[nodiscard]] Util::String GetWindowName() const noexcept { return m_windowName; }

		/// @brief �E�B���h�E�̕��擾
		/// @return �E�B���h�E�̕�(����)
		[[nodiscard]] int GetWindowWidth() const noexcept { return m_windowWidth; }

		/// @brief �E�B���h�E�̍����擾
		/// @return �E�B���h�E�̍���(����)
		[[nodiscard]] int GetWindowHeight() const noexcept { return m_windowHeight; }

		/// @brief �G���W���̎擾
		/// @return �G���W���̃|�C���^
		Engine* GetEngine() const noexcept { return m_pCoreEngine; }

		/// @brief �G���W���̐ݒ�
		/// @param pCoreEngine �G���W���̃|�C���^
		void SetEngine(Engine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief �R�s�[�R���X�g���N�^�폜
		Window(const Window&) = delete;
		/// @brief ���[�u�R���X�g���N�^�폜
		Window(Window&&) = delete;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		Engine*		m_pCoreEngine;			///< �G���W���̃|�C���^
		Util::String		m_windowName;		///< �E�B���h�E��
		int				m_windowWidth;		///< �E�B���h�E�̕�
		int				m_windowHeight;		///< �E�B���h�E�̍���
	};
}

#endif // !_CORE_WINDOW_
