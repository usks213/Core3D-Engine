/*****************************************************************//**
 * \file   D3D12_Editor.h
 * \brief  DirectX12エディター
 *
 * \author USAMI KOSHI
 * \date   2021/12/23
 *********************************************************************/
#include "D3D12_Editor.h"

#include <RHI\D3D12\D3D12_CommandList.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx12.h>

using namespace Core::D3D12;

/// @brief 初期化処理
/// @param hWnd ウィンドウハンドル
/// @param pDevice デバイス
/// @param pContext イミディエイトコンテキスト
/// @return 成功 TRUE / 失敗 FALSE
bool D3D12Editor::initialize(HWND hWnd, D3D12Device* pDevice, int nBackBufferCount, DXGI_FORMAT backBufferFormat)
{
	bool bResult = true;

	////--- DirectX12
	//// ヒープの作成
	//D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	//desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	//desc.NodeMask = 0;				// 今ゼロ
	//desc.NumDescriptors = 1;	// 最大ディスクリプタ数
	//desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	//pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_pImGuiHeap.ReleaseAndGetAddressOf()));
	D3D12DescriptorPool* pPool = pDevice->GetTextureDescriptor();
	D3D12DescriptorHandle handle = pPool->Allocate();
	m_pTexHeap = pPool->GetDescriptorHeap();

	//--- imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;	// ウィンドウになる
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

	bResult = ImGui_ImplDX12_Init(pDevice->GetD3D12Device(), nBackBufferCount, backBufferFormat,
		m_pTexHeap, handle.CPUHandle, handle.GPUHandle);
	if (bResult == false) return bResult;

	// 日本語フォント
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
	// コンフィグパス
	io.IniFilename = "Essentials/Config/ImGuiLayout.ini";

	return bResult;
}

/// @brief 終了処理
void D3D12Editor::finalize()
{
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

/// @brief 新しい描画フレーム作成
void D3D12Editor::NewFrame()
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGuizmo::BeginFrame();
}

/// @brief 描画
/// @param cmdList コマンドリスト
void D3D12Editor::Render(Core::CommandList* cmdList)
{

	// バックバッファ指定
	auto* pD3D12Cmd = static_cast<D3D12CommandList*>(cmdList);
	pD3D12Cmd->setBackBuffer();
	pD3D12Cmd->clearBackBuffer(Color(0.2f, 0.2f, 0.2f, 1.0f));
	pD3D12Cmd->GetD3D12GraphicsCommandList()->SetDescriptorHeaps(1, &m_pTexHeap);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),
		pD3D12Cmd->GetD3D12GraphicsCommandList());
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}
