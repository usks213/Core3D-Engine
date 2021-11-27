/*****************************************************************//**
 * \file   EditorWindowManager.h
 * \brief  �G�f�B�^�[�E�B���h�E�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "EditorWindowManager.h"

#include <CoreEngine\Core_Engine.h>
#include "ImGui\imgui.h"

#include <CoreEditor/Window/ConsoleWindow.h>
#include <CoreEditor/Window/GameWindow.h>
#include <CoreEditor/Window/HierarchyWindow.h>
#include <CoreEditor/Window/InspectorWindow.h>
#include <CoreEditor/Window/ProjectWindow.h>
#include <CoreEditor/Window/SceneWindow.h>
						

 /// @brief �R���X�g���N�^
 /// @param pCoreEditor �R�A�G�f�B�^�[�|�C���^
EditorWindowManager::EditorWindowManager(core::CoreEditor* pCoreEditor) noexcept :
	m_pCoreEditor(pCoreEditor)
{
	AddEditorWindow<GameWindow>();
	AddEditorWindow<HierarchyWindow>();
	AddEditorWindow<InspectorWindow>();
	AddEditorWindow<ProjectWindow>();
}

 /// @brief �E�B���h�E�̕\��
void EditorWindowManager::DispWindow()
{
	float width = static_cast<float>(GetCoreEditor()->getCoreEngine()->getWindowWidth());
	float height = static_cast<float>(GetCoreEditor()->getCoreEngine()->getWindowHeight());

	// overlay�E�B���h�E�̕\���\��
	static ImGuiID dockspaceID = 0;
	bool active = true;
	ImGui::SetNextWindowPos(ImVec2());
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowBgAlpha(0.0f);
	if (ImGui::Begin("Master Window", &active,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | 
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar))
	{
		// ���j���[�o�[
		DispMenueBar();
	}
	if (active)
	{
		// Declare Central dockspace
		dockspaceID = ImGui::GetID("HUB_DockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
	}
	ImGui::End();

	// �q�E�B���h�E�̕\��
	for (auto& window : m_windowPool)
	{
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		window.second->DispWindow();
	}
}

/// @brief ���j���[�o�[�̕\��
void EditorWindowManager::DispMenueBar()
{
	// ���j���[�o�[
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
			for (auto& window : m_windowPool)
			{
				if (ImGui::MenuItem(window.second->GetWindowName().data()))
				{
					if (!window.second->GetWindowOpen())
					{
						window.second->SetWindowOpen(true);
					}
				}
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}
