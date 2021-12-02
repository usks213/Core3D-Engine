/*****************************************************************//**
 * \file   EditorWindowManager.h
 * \brief  エディターウィンドウマネージャー
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
						

 /// @brief コンストラクタ
 /// @param pEditor コアエディターポインタ
EditorWindowManager::EditorWindowManager(Core::Editor* pEditor) noexcept :
	m_pEditor(pEditor)
{
	AddEditorWindow<GameWindow>();
	AddEditorWindow<HierarchyWindow>();
	AddEditorWindow<InspectorWindow>();
	AddEditorWindow<ProjectWindow>();
}

 /// @brief ウィンドウの表示
void EditorWindowManager::DispWindow()
{
	float width = static_cast<float>(GetEditor()->GetEngine()->GetWindowWidth());
	float height = static_cast<float>(GetEditor()->GetEngine()->GetWindowHeight());

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
		// ボタン
		DispButton();

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

/// @brief ボタンの表示
void EditorWindowManager::DispButton()
{
	//--- マニピュレーターの切り替え

	// Hand

	// Translation

	// Rotation

	// Scale


	//--- 座標系

	// Bounds or Centor

	// Local or Global


	//--- シーンデバッグ

	// Start or End

	// Stop

	// Frame


	//--- その他


}
