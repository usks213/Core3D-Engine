/*****************************************************************//**
 * \file   D3D12_Editor.h
 * \brief  DirectX12�G�f�B�^�[
 *
 * \author USAMI KOSHI
 * \date   2021/12/23
 *********************************************************************/
#include "D3D12_Editor.h"

#include <CoreRenderer\D3D12\D3D12_CommandList.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx12.h>

using namespace d3d12;

/// @brief ����������
/// @param hWnd �E�B���h�E�n���h��
/// @param pDevice �f�o�C�X
/// @param pContext �C�~�f�B�G�C�g�R���e�L�X�g
/// @return ���� TRUE / ���s FALSE
bool D3D12Editor::initialize(HWND hWnd, ID3D12Device* pDevice, int nBackBufferCount, DXGI_FORMAT backBufferFormat)
{
	bool bResult = true;

	//--- DirectX12
	// �q�[�v�̍쐬
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	desc.NodeMask = 0;				// ���[��
	desc.NumDescriptors = 10000;	// �ő�f�B�X�N���v�^��
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_pImGuiHeap.ReleaseAndGetAddressOf()));

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
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.0f;
	}

	// setup platform/renderer
	bResult = ImGui_ImplWin32_Init(hWnd);
	if (bResult == false) return bResult;

	bResult = ImGui_ImplDX12_Init(pDevice, nBackBufferCount, backBufferFormat,
		m_pImGuiHeap.Get(), m_pImGuiHeap->GetCPUDescriptorHandleForHeapStart(), 
		m_pImGuiHeap->GetGPUDescriptorHandleForHeapStart());
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
void D3D12Editor::finalize()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

/// @brief �V�����`��t���[���쐬
void D3D12Editor::NewFrame()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGuizmo::BeginFrame();
}

/// @brief �`��
/// @param cmdList �R�}���h���X�g
void D3D12Editor::Render(core::CoreCommandList* cmdList)
{
	ImGui::Render();

	// �o�b�N�o�b�t�@�w��
	auto* pD3D12Cmd = static_cast<D3D12CommandList*>(cmdList);
	pD3D12Cmd->setBackBuffer();
	pD3D12Cmd->GetD3D12GraphicsCommandList()->SetDescriptorHeaps(1, m_pImGuiHeap.GetAddressOf());

	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), 
		pD3D12Cmd->GetD3D12GraphicsCommandList());
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}
