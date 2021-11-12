/*****************************************************************//**
 * \file   Win_Window.h
 * \brief  �E�B���h�E�Y�̃E�B���h�E�N���X
 *
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#include "Win_Window.h"
#include "Win_Resource.h"
#include <tchar.h>

using namespace win;


/// @brief �R���X�g���N�^
/// @param windowName[in] �E�B���h�E��
/// @param windowWidth[in] �E�B���h�E�̕�
/// @param windowHeight[in] �E�B���h�E�̍���
WinWindow::WinWindow(util::String windowName, UINT windowWidth, UINT windowHeight) :
	CoreWindow(windowName, windowWidth, windowHeight),
	m_hInstance(NULL), m_hWnd(NULL), m_nCmdShow(NULL)
{
}

/// @brief �E�B���h�E�������֐�
/// @param hInstance �C���X�^���X�n���h��
/// @param className �N���X��
/// @param nCmdShow 
/// @param lpfnWndProc �E�B���h�E�v���V�[�W���֐��̃|�C���^
/// @return �E�B���h�E���� ���� ture, �s���� false
bool WinWindow::initialize(HINSTANCE& hInstance, util::String className, int nCmdShow, WNDPROC lpfnWndProc)
{
	// �E�B���h�EEx�\����
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		lpfnWndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		nullptr,
		className.c_str(),
		nullptr
	};

	// COM������
	if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		MessageBox(NULL, _T("COM�̏������Ɏ��s���܂����B"), _T("error"), MB_OK);
		return false;
	}

	// �C���X�^���X �n���h���ۑ�
	m_hInstance = hInstance;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// ��DPI�Ή�
	//SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// �N���C�A���g�̈�T�C�Y����E�B���h�E �T�C�Y�Z�o
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION
		| WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;
	DWORD dwExStyle = 0;
	RECT rc = { 0, 0, m_windowWidth, m_windowHeight };
	AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

	// �E�B���h�E�̍쐬
	m_hWnd = CreateWindowEx(dwExStyle,
		className.c_str(),
		m_windowName.c_str(),
		dwStyle,
		CW_USEDEFAULT,		// �E�B���h�E�̍����W
		CW_USEDEFAULT,		// �E�B���h�E�̏���W
		rc.right - rc.left,	// �E�B���h�E����
		rc.bottom - rc.top,	// �E�B���h�E�c��
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	// �i�[
	m_className = className;
	m_nCmdShow = nCmdShow;

	return true;
}


void WinWindow::finalize()
{
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(m_className.c_str(), m_hInstance);

	// COM�I������
	CoUninitialize();
}

//void UpdateButtonLayoutForDpi(HWND hWnd)
//{
//	int iDpi = GetDpiForWindow(hWnd);
//	int dpiScaledX = MulDiv(INITIALX_96DPI, iDpi, 96);
//	int dpiScaledY = MulDiv(INITIALY_96DPI, iDpi, 96);
//	int dpiScaledWidth = MulDiv(INITIALWIDTH_96DPI, iDpi, 96);
//	int dpiScaledHeight = MulDiv(INITIALHEIGHT_96DPI, iDpi, 96);
//	SetWindowPos(hWnd, hWnd, dpiScaledX, dpiScaledY, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);
//}