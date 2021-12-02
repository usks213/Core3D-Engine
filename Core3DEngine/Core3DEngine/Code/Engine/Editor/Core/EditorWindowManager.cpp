/*****************************************************************//**
 * \file   EditorWindowManager.h
 * \brief  �G�f�B�^�[�E�B���h�E�}�l�[�W���[
 *
 * \author USAMI KOSHI
 * \date   2021/11/27
 *********************************************************************/
#include "EditorWindowManager.h"

#include <Engine\Core\Engine.h>
#include "ImGui\imgui.h"

#include <Editor/Window/ConsoleWindow.h>
#include <Editor/Window/GameWindow.h>
#include <Editor/Window/HierarchyWindow.h>
#include <Editor/Window/InspectorWindow.h>
#include <Editor/Window/ProjectWindow.h>
#include <Editor/Window/SceneWindow.h>

using namespace Core;
						

 /// @brief �R���X�g���N�^
 /// @param pEditor �R�A�G�f�B�^�[�|�C���^
EditorWindowManager::EditorWindowManager(Core::Editor* pEditor) noexcept :
	m_pEditor(pEditor)
{
	AddEditorWindow<GameWindow>();
	AddEditorWindow<HierarchyWindow>();
	AddEditorWindow<InspectorWindow>();
	AddEditorWindow<ProjectWindow>();
}

 /// @brief �E�B���h�E�̕\��
void EditorWindowManager::DispWindow()
{
	float width = static_cast<float>(GetEditor()->GetEngine()->GetWindowWidth());
	float height = static_cast<float>(GetEditor()->GetEngine()->GetWindowHeight());

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
		// �{�^��
		DispButton();

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

/// @brief �{�^���̕\��
void EditorWindowManager::DispButton()
{
	//--- �}�j�s�����[�^�[�̐؂�ւ�

	// Hand

	// Translation

	// Rotation

	// Scale


	//--- ���W�n

	// Bounds or Centor

	// Local or Global


	//--- �V�[���f�o�b�O

	// Start or End

	// Stop

	// Frame


	//--- ���̑�


}
