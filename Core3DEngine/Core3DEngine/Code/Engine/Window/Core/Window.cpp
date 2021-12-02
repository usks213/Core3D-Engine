/*****************************************************************//**
 * \file   Window.cpp
 * \brief  �E�B���h�E�N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#include "Window.h"

using namespace Core;

/// @brief �R���X�g���N�^
/// @param windowName[in] �E�B���h�E��
/// @param windowWidth[in] �E�B���h�E�̕�
/// @param windowHeight[in] �E�B���h�E�̍���
Window::Window(Util::String windowName, std::uint32_t windowWidth, std::uint32_t windowHeight) :
	m_pCoreEngine(nullptr),
	m_windowName(windowName), 
	m_windowWidth(windowWidth), 
	m_windowHeight(windowHeight)
{
}

