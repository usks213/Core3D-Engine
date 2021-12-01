/*****************************************************************//**
 * \file   D3D11_Editor.h
 * \brief  DirectX11�G�f�B�^�[
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#include "D3D11_Editor.h"

#include <CoreRenderer\D3D11\D3D11_Renderer.h>
#include <CoreRenderer\D3D11\D3D11_CommandList.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx11.h>

using namespace d3d11;

/// @brief ����������
/// @param hWnd �E�B���h�E�n���h��
/// @param pDevice �f�o�C�X
/// @param pContext �C�~�f�B�G�C�g�R���e�L�X�g
/// @return ���� TRUE / ���s FALSE
bool D3D11Editor::initialize(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	bool bResult = true;

	//--- imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	// �E�B���h�E�ɂȂ�
	// doking
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	// style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.0f;
	}

	// setup platform/renderer
	bResult = ImGui_ImplWin32_Init(hWnd);
	if (bResult == false) return bResult;

	bResult = ImGui_ImplDX11_Init(pDevice, pContext);
	if (bResult == false) return bResult;

	// ���{��t�H���g
	ImFontConfig config = {};
	config.OversampleH = 1;
	config.OversampleV = 1;
	config.PixelSnapH = 1;
	io.Fonts->AddFontDefault();
	ImFont* pFont = io.Fonts->AddFontFromFileTTF("Essentials/Fonts/msgothic.ttc", 
		18.0f, &config, io.Fonts->GetGlyphRangesJapanese());
	IM_ASSERT(pFont != nullptr);
	ImFont* currentFont = ImGui::GetFont();
	currentFont = pFont;
	io.FontDefault = pFont;
	// �R���t�B�O�p�X
	io.IniFilename = "Essentials/Config/ImGuiLayout.ini";

	return bResult;
}

/// @brief �I������
void D3D11Editor::finalize()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

/// @brief �V�����`��t���[���쐬
void D3D11Editor::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGuizmo::BeginFrame();
}

/// @brief �`��
/// @param cmdList �R�}���h���X�g
void D3D11Editor::Render(core::CoreCommandList* cmdList)
{
	// �o�b�N�o�b�t�@�ɕύX
	static_cast<D3D11CommandList*>(cmdList)->GetD3D11Renderer()->SetD3D11BackBuffer();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}
