/*****************************************************************//**
 * \file   StartUp.cpp
 * \brief  �X�^�[�g�A�b�v
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

/// @brief �G���W��
core::CoreEngine* g_pEngine = nullptr;

 /// @brief ���C���̏����������֐�
void MainStartup()
{
	// �G���W���̏�����
	g_pEngine = &core::CoreEngine::get();
	auto* pWindow = g_pEngine->createWindow<win::WinWindow>(_T("Core3D-Engine"), 1280, 720);

}

/// @brief ���C�����[�v�֐�
void MainLoop()
{

}

/// @brief ���C���̏I�������֐�
void MainCleanup()
{

}
