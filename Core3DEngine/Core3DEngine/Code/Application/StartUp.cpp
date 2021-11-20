/*****************************************************************//**
 * \file   StartUp.cpp
 * \brief  �X�^�[�g�A�b�v
 * 
 * \author USAMI KOSHI
 * \date   2021/11/12
 *********************************************************************/

#include <wchar.h>
#include <CoreSystem\Main\Core_Main.h>
#include <CoreEngine\Core_Engine.h>
#include <CoreSystem\Window\Win\Win_Window.h>
#include <CoreRenderer\D3D11\D3D11_Renderer.h>
#include <CoreRenderer\D3D12\D3D12_Renderer.h>

#include "Scene\TestScene.h"

 //===== �v���g�^�C�v�錾 =====
 // �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// �E�B���h�E������
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);


//===== �O���[�o���ϐ� =====
/// @brief �G���W��
core::CoreEngine* g_pEngine = nullptr;

 /// @brief ���C���̏����������֐�
void MainStartup(HINSTANCE hInstance, int nCmdShow)
{
	// �G���W���̎擾
	g_pEngine = &core::CoreEngine::get();

	// �E�B���h�E�̏�����
	auto* pWindow = g_pEngine->createWindow<win::WinWindow>(_T("Core3D-Engine"), 1280, 720);
	pWindow->initialize(hInstance, _T("Core3D-Engine"), nCmdShow, WndProc);

	// �����_���[�̏�����
	auto* pRenderer = g_pEngine->createRenderer<d3d12::D3D12Renderer>();
	pRenderer->initialize(pWindow->getWindowHandle(), pWindow->getWindowWidth(), pWindow->getWindowHeight());

	// �G���W���̏�����
	g_pEngine->initialize();

	// �V�[���}�l�[�W���[�̓ǂݍ���
	g_pEngine->getSceneManager()->CreateScene<TestScene>();

}

/// @brief ���C�����[�v�֐�
void MainLoop()
{
	// �G���W���̍X�V
	g_pEngine->tick();
}

/// @brief ���C���̏I�������֐�
void MainCleanup()
{
	// �I������
	g_pEngine->finalize();
}


/// @brief �v���V�[�W��
/// @param hWnd 
/// @param uMsg 
/// @param wParam 
/// @param lParam 
/// @return 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
	{//----- �E�B���h�E���������ꂽ
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
	}
	case WM_DESTROY:				//----- �E�B���h�E�j���w��������
		PostQuitMessage(0);				// �V�X�e���ɃX���b�h�̏I����v��
		break;
	case WM_KEYDOWN:				//----- �L�[�{�[�h�������ꂽ
		switch (wParam) 
		{
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			PostMessage(hWnd, WM_CLOSE, 0, 0);	// [x]�������ꂽ�悤�ɐU����
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;			// [Alt]+[Enter]����BEEP��}�~
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/// @brief WM_CREATE���b�Z�[�W�n���h��
/// @param hWnd 
/// @param lpcs 
/// @return 
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// �N���C�A���g�̈�T�C�Y��SCREEN_WIDTH�~SCREEN_HEIGHT�ɍĐݒ�.
	RECT rcClnt;
	int SCREEN_WIDTH = core::CoreEngine::get().getWindowWidth();
	int SCREEN_HEIGHT = core::CoreEngine::get().getWindowHeight();

	GetClientRect(hWnd, &rcClnt);
	rcClnt.right -= rcClnt.left;
	rcClnt.bottom -= rcClnt.top;
	if (rcClnt.right != SCREEN_WIDTH || rcClnt.bottom != SCREEN_HEIGHT) {
		RECT rcWnd;
		GetWindowRect(hWnd, &rcWnd);
		SIZE sizeWnd;
		sizeWnd.cx = (rcWnd.right - rcWnd.left) - rcClnt.right + SCREEN_WIDTH;
		sizeWnd.cy = (rcWnd.bottom - rcWnd.top) - rcClnt.bottom + SCREEN_HEIGHT;

		SetWindowPos(hWnd, nullptr, 0, 0, sizeWnd.cx, sizeWnd.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	// IME������
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1��Ԃ���CreateWindow[Ex]�����s����.
}