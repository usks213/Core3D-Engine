/*****************************************************************//**
 * \file   StartUp.cpp
 * \brief  スタートアップ
 * 
 * \author USAMI KOSHI
 * \date   2021/11/12
 *********************************************************************/

#include <CoreSystem\Main\Core_Main.h>
#include <CoreEngine\Core_Engine.h>
#include <CoreSystem\Window\Win\Win_Window.h>
#include <CoreRenderer\D3D11\D3D11_Renderer.h>
#include <CoreRenderer\D3D12\D3D12_Renderer.h>

#include <wchar.h>

/// @brief エンジン
core::CoreEngine* g_pEngine = nullptr;

 /// @brief メインの初期化処理関数
void MainStartup()
{
	// エンジンの初期化
	g_pEngine = &core::CoreEngine::get();
	auto* pWindow = g_pEngine->createWindow<win::WinWindow>(_T("Core3D-Engine"), 1280, 720);

}

/// @brief メインループ関数
void MainLoop()
{

}

/// @brief メインの終了処理関数
void MainCleanup()
{

}
