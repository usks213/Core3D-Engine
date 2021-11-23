/*****************************************************************//**
 * \file   EditorWindow.h
 * \brief  エディターウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#include "EditorWindow.h"

 /// @brief コンストラクタ
EditorWindow::EditorWindow() noexcept :
	m_pManager(nullptr),
	m_isDisp(true),
	m_name("DefaultWindow"),
	m_isOpne(true),
	m_flags(ImGuiWindowFlags_None)
{
}

/// @brief ウィンドウの表示
void EditorWindow::DispWindow()
{
	// 非表示
	if (!m_isDisp) return;

	// ウィンドウの開始
	if (ImGui::Begin(m_name.c_str(), &m_isOpne, m_flags))
	{
		m_size = ImGui::GetWindowSize();
		m_pos = ImGui::GetWindowPos();

		// GUIの更新・表示
		OnGUI();
	}

	// ウィンドウの終了
	ImGui::End();
}
