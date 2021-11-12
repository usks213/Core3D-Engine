/*****************************************************************//**
 * \file   Win_Window.h
 * \brief  �E�B���h�E�Y�̃E�B���h�E�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _WIN_WINDOW_
#define _WIN_WINDOW_

#include "../Core/Core_Window.h"
#include <Windows.h>

namespace win
{
	/// @class WinWindow
	/// @brief �E�B���h�E�Y�̃E�B���h�E�N���X
	class WinWindow final : public core::CoreWindow
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param windowName[in] �E�B���h�E��
		/// @param windowWidth[in] �E�B���h�E�̕�
		/// @param windowHeight[in] �E�B���h�E�̍���
		explicit WinWindow(util::String windowName, UINT windowWidth, UINT windowHeight);

		/// @brief �f�X�g���N�^
		~WinWindow() noexcept = default;

		/// @brief �E�B���h�E�������֐�
		/// @param hInstance �C���X�^���X�n���h��
		/// @param className �N���X��
		/// @param nCmdShow 
		/// @param lpfnWndProc �E�B���h�E�v���V�[�W���֐��̃|�C���^
		/// @return ������: ���� true | ���s false
		bool initialize(HINSTANCE& hInstance, util::String className, int nCmdShow, WNDPROC lpfnWndProc);

		/// @brief �I������
		void finalize() override;

		/// @brief �E�B���h�E�n���h���擾
		/// @return �E�B���h�E�n���h��
		HWND getWindowHandle() { return m_hWnd; }

		/// @brief �R�s�[�R���X�g���N�^�폜
		WinWindow(const WinWindow&) = delete;
		/// @brief ���[�u�R���X�g���N�^�폜
		WinWindow(WinWindow&&) = delete;

	private:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		HINSTANCE		m_hInstance;		///< �C���X�^���X�n���h��
		HWND				m_hWnd;			///< �E�B���h�E�n���h��
		util::String		m_className;		///< �N���X��
		int				m_nCmdShow;		///< �t���X�N���[���؂�ւ��Ŏg�������H
	};

}

#endif // !_WIN_WINDOW_
