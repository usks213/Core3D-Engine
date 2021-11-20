/*****************************************************************//**
 * \file   StartUp.cpp
 * \brief  スタートアップ
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

 //===== プロトタイプ宣言 =====
 // ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// ウィンドウ初期化
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs);


//===== グローバル変数 =====
/// @brief エンジン
core::CoreEngine* g_pEngine = nullptr;

 /// @brief メインの初期化処理関数
void MainStartup(HINSTANCE hInstance, int nCmdShow)
{
	// エンジンの取得
	g_pEngine = &core::CoreEngine::get();

	// ウィンドウの初期化
	auto* pWindow = g_pEngine->createWindow<win::WinWindow>(_T("Core3D-Engine"), 1280, 720);
	pWindow->initialize(hInstance, _T("Core3D-Engine"), nCmdShow, WndProc);

	// レンダラーの初期化
	auto* pRenderer = g_pEngine->createRenderer<d3d12::D3D12Renderer>();
	pRenderer->initialize(pWindow->getWindowHandle(), pWindow->getWindowWidth(), pWindow->getWindowHeight());

	// エンジンの初期化
	g_pEngine->initialize();

	// シーンマネージャーの読み込み
	g_pEngine->getSceneManager()->CreateScene<TestScene>();

}

/// @brief メインループ関数
void MainLoop()
{
	// エンジンの更新
	g_pEngine->tick();
}

/// @brief メインの終了処理関数
void MainCleanup()
{
	// 終了処理
	g_pEngine->finalize();
}


/// @brief プロシージャ
/// @param hWnd 
/// @param uMsg 
/// @param wParam 
/// @param lParam 
/// @return 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
	{//----- ウィンドウが生成された
		return OnCreate(hWnd, (LPCREATESTRUCT)lParam);
	}
	case WM_DESTROY:				//----- ウィンドウ破棄指示がきた
		PostQuitMessage(0);				// システムにスレッドの終了を要求
		break;
	case WM_KEYDOWN:				//----- キーボードが押された
		switch (wParam) 
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			PostMessage(hWnd, WM_CLOSE, 0, 0);	// [x]が押されたように振舞う
			return 0;
		}
		break;
	case WM_MENUCHAR:
		return MNC_CLOSE << 16;			// [Alt]+[Enter]時のBEEPを抑止
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/// @brief WM_CREATEメッセージハンドラ
/// @param hWnd 
/// @param lpcs 
/// @return 
int OnCreate(HWND hWnd, LPCREATESTRUCT lpcs)
{
	// クライアント領域サイズをSCREEN_WIDTH×SCREEN_HEIGHTに再設定.
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

	// IME無効化
	ImmAssociateContext(hWnd, nullptr);

	return 0;	// -1を返すとCreateWindow[Ex]が失敗する.
}