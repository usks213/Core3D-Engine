/*****************************************************************//**
 * \file   Core_Main.h
 * \brief  ���C���֐�
 * 
 * \author USAMI KOSHI
 * \date   2021/11/04
 *********************************************************************/
#ifndef _CORE_MAIN_
#define _CORE_MAIN_

// Windows
#ifdef _WIN32
#include <Windows.h>
 /// @brief ���C���̏����������֐�
void MainStartup(HINSTANCE hInstance, int nCmdShow);
#elif __linux

#elif __APPLE__

#else
/// @brief ���C���̏����������֐�
void MainStartup();
#endif // _WIN32

/// @brief ���C�����[�v�֐�
void MainLoop();

/// @brief ���C���̏I�������֐�
void MainCleanup();

#endif // !_CORE_MAIN_
