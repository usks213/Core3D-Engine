/*****************************************************************//**
 * \file   EngineWindow.h
 * \brief  �G���W���E�B���h�E
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "EngineWindow.h"

#include <CoreEditor\Core_Editor.h>
#include <CoreEngine\Core_Engine.h>

 /// @brief �R���X�g���N�^
EngineWindow::EngineWindow() noexcept
{
	SetWindowDisp(true);
	SetWindowName("Overlay");
	SetWindowOpen(true);
	SetWindowFlags(
		ImGuiWindowFlags_NoTitleBar | 
		ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoMove | 
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_MenuBar | 
		ImGuiWindowFlags_NoDocking
	);

	ImGuiDockNodeFlags_PassthruCentralNode;
}

/// @brief GUI�\���R�[���o�b�N
void EngineWindow::OnGUI()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}
