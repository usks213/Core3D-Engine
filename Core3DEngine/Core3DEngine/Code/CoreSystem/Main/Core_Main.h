/*****************************************************************//**
 * \file   Core_Main.h
 * \brief  メイン関数
 * 
 * \author USAMI KOSHI
 * \date   2021/11/04
 *********************************************************************/
#ifndef _CORE_MAIN_
#define _CORE_MAIN_

// Windows
#ifdef _WIN32
#include <Windows.h>
 /// @brief メインの初期化処理関数
void MainStartup(HINSTANCE hInstance, int nCmdShow);
#elif __linux

#elif __APPLE__

#else
/// @brief メインの初期化処理関数
void MainStartup();
#endif // _WIN32

/// @brief メインループ関数
void MainLoop();

/// @brief メインの終了処理関数
void MainCleanup();

#endif // !_CORE_MAIN_
