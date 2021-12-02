/*****************************************************************//**
 * \file   EditorWindow.h
 * \brief  �G�f�B�^�[�E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#include "EditorWindow.h"

using namespace Core;

 /// @brief �R���X�g���N�^
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

/// @brief �E�B���h�E�̕\��
void EditorWindow::DispWindow()
{
	// ��\��
	if (!m_isDisp || !m_isOpne) return;

	// �E�B���h�E�̊J�n
	//ImGui::SetNextWindowPos(m_pos);
	//ImGui::SetNextWindowSize(m_size);
	ImGui::SetNextWindowBgAlpha(0.6f);
	//ImGui::SetNextWindowFocus();
	if (ImGui::Begin(m_name.c_str(), &m_isOpne, m_flags))
	{
		m_size = ImGui::GetWindowSize();
		m_pos = ImGui::GetWindowPos();

		// GUI�̍X�V�E�\��
		OnGUI();
	}

	// �E�B���h�E�̏I��
	ImGui::End();
}
