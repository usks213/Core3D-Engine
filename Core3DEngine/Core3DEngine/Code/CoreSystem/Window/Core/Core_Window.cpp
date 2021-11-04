/*****************************************************************//**
 * \file   Core_Window.cpp
 * \brief  ウィンドウクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#include "Core_Window.h"

using namespace core;

/// @brief コンストラクタ
/// @param windowName[in] ウィンドウ名
/// @param windowWidth[in] ウィンドウの幅
/// @param windowHeight[in] ウィンドウの高さ
CoreWindow::CoreWindow(CoreString windowName, std::uint32_t windowWidth, std::uint32_t windowHeight) :
	m_pCoreEngine(nullptr),
	m_windowName(windowName), 
	m_windowWidth(windowWidth), 
	m_windowHeight(windowHeight)
{
}

