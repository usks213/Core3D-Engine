/*****************************************************************//**
 * \file   Win_Main.cpp
 * \brief  WindowsMain
 * 
 * \author USAMI KOSHI
 * \date   2021/11/04
 *********************************************************************/

// WindowsOS�̂�
#ifdef _WIN32

// �C���N���[�h
#include <Windows.h>
#include <tchar.h>
#include "../Core_Main.h"

//-------- ���C�u�����̃����N
#pragma comment(lib, "imm32")

/// @brief �G���g���|�C���g
/// @param hInstance		�C���X�^���X�n���h��
/// @param hPrevInstance	�O��̃C���X�^���X�n���h��
/// @param lpCmdLine		�R�}���h���C��
/// @param nCmdShow			�E�B���h�E���
/// @return �I���R�[�h
int WINAPI _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// ���g�p�錾
	UNREFERENCED_PARAMETER(lpCmdLine);		// ���g�p�錾

	// ����������
	MainStartup();

	// ���b�Z�[�W���[�v
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �X�V����
			MainLoop();

			Sleep(0);
		}
	}

	// �I������
	MainCleanup();

	return (int)msg.wParam;
}

#endif // _WIN32
