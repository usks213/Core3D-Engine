/*****************************************************************//**
 * \file   EditorWindowManager.h
 * \brief  エディターウィンドウマネージャー
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
						

 /// @brief コンストラクタ
 /// @param pCoreEditor コアエディターポインタ
EditorWindowManager::EditorWindowManager(core::CoreEditor* pCoreEditor) noexcept :
	m_pCoreEditor(pCoreEditor)
{
	AddEditorWindow<GameWindow>();
	AddEditorWindow<HierarchyWindow>();
	AddEditorWindow<InspectorWindow>();
	AddEditorWindow<ProjectWindow>();
}

 /// @brief ウィンドウの表示
void EditorWindowManager::DispWindow()
{
	float width = static_cast<float>(GetCoreEditor()->getCoreEngine()->getWindowWidth());
	float height = static_cast<float>(GetCoreEditor()->getCoreEngine()->getWindowHeight());

	// overlayウィンドウの表示表示
	static ImGuiID dockspaceID = 0;
	bool active = true;
	ImGui::SetNextWindowPos(ImVec2());
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowBgAlpha(0.0f);
	if (ImGui::Begin("Master Window", &active,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | 
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar))
	{
		// メニューバー
		DispMenueBar();
	}
	if (active)
	{
		// Declare Central dockspace
		dockspaceID = ImGui::GetID("HUB_DockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
	}
	ImGui::End();

	// 子ウィンドウの表示
	for (auto& window : m_windowPool)
	{
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		window.second->DispWindow();
	}
}

/// @brief メニューバーの表示
void EditorWindowManager::DispMenueBar()
{
	// メニューバー
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
