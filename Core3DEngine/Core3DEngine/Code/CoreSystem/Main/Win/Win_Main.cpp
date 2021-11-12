/*****************************************************************//**
 * \file   Win_Main.cpp
 * \brief  WindowsMain
 * 
 * \author USAMI KOSHI
 * \date   2021/11/04
 *********************************************************************/

// WindowsOSのみ
#ifdef _WIN32

// インクルード
#include <Windows.h>
#include <tchar.h>
#include "../Core_Main.h"

//-------- ライブラリのリンク
#pragma comment(lib, "imm32")

/// @brief エントリポイント
/// @param hInstance		インスタンスハンドル
/// @param hPrevInstance	前回のインスタンスハンドル
/// @param lpCmdLine		コマンドライン
/// @param nCmdShow			ウィンドウ状態
/// @return 終了コード
int WINAPI _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 未使用宣言
	UNREFERENCED_PARAMETER(lpCmdLine);		// 未使用宣言

	// 初期化処理
	MainStartup();

	// メッセージループ
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
			// 更新処理
			MainLoop();

			Sleep(0);
		}
	}

	// 終了処理
	MainCleanup();

	return (int)msg.wParam;
}

#endif // _WIN32
