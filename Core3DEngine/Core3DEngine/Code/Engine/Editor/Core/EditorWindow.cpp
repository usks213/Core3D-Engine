/*****************************************************************//**
 * \file   EditorWindow.h
 * \brief  エディターウィンドウ
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#include "EditorWindow.h"

using namespace Core;

 /// @brief コンストラクタ
EditorWindow::EditorWindow() noexcept :
	m_pManager(nullptr),
	m_isDisp(true),
	m_name("DefaultWindow"),
	m_isOpne(true),
	m_flags(ImGuiWindowFlags_None),
	m_pos(100, 100),
	m_size(100, 100)
{
}

/// @brief ウィンドウの表示
void EditorWindow::DispWindow()
{
	// 非表示
	if (!m_isDisp || !m_isOpne) return;

	// ウィンドウの開始
	//ImGui::SetNextWindowPos(m_pos);
	//ImGui::SetNextWindowSize(m_size);
	ImGui::SetNextWindowBgAlpha(0.6f);
	//ImGui::SetNextWindowFocus();
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
