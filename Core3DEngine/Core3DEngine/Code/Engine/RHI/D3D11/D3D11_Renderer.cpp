/*****************************************************************//**
 * \file   D3D11_Renderer.cpp
 * \brief  DirectX11レンダラークラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#include "D3D11_Renderer.h"
#include <vector>

using namespace Core::RHI::D3D11;


/// @brief コンストラクタ
D3D11Renderer::D3D11Renderer() :
	m_curBackBufferIndex(1),
	m_cmdLists(),
	m_useCmdListCnt{0,0},
	m_device(),
	m_d3dDevice(),
	m_d3dAnnotation(),
	m_d3dContext(),
	m_dxgiFactory()
{
}

 /// @brief 初期化処理
 /// @param hWnd ウィンドウハンドル
 /// @param width ウィンドウの幅
 /// @param height ウィンドウの高さ
 /// @return 初期化: 成功 true | 失敗 false
HRESULT D3D11Renderer::initialize(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr = S_OK;

	// デバイスとコマンドリストの作成
	CHECK_FAILED(hr = CreateDiveceAndContext(hWnd));

	// デバイスの初期化
	CHECK_FAILED(hr = m_device.initialize(m_d3dDevice.Get(), 
		m_dxgiFactory.Get(), hWnd, width, height, BACK_BUFFER_COUNT));

	return hr;
}

/// @brief 終了処理
void D3D11Renderer::finalize()
{

}

/// @brief フレーム開始
void D3D11Renderer::beginFrame()
{
	//--- リソースの更新
	// GPU側のバッファ、テクスチャなど更新
	// DirectX11はいらないかも

	//--- コマンド発行
	// 前フレームで貯めたコマンドの発行

	// コマンドの実行
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		m_d3dContext->ExecuteCommandList(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList.Get(), false);
	}

	//--- 現フレームのコマンド準備

	// バッファインデックス切り替え
	m_curBackBufferIndex = (m_curBackBufferIndex + 1) % BACK_BUFFER_COUNT;

	// コマンドリストのクリア
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		m_cmdLists[m_curBackBufferIndex][i]->ClearCommand();
	}
	m_useCmdListCnt[m_curBackBufferIndex] = 0;

}

/// @brief フレーム終了
void D3D11Renderer::endFrame()
{
	// コマンドの記録終了
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		m_cmdLists[m_curBackBufferIndex][i]->m_pDeferredContext->FinishCommandList(true,
			m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList.GetAddressOf());
	}

	//--- 前フレームのコマンド完了を待つ(フェンス)


	// スワップ
	//m_swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);	// ティアリング許容描画
	//m_swapChain->Present(0, 0);							// 非垂直同期描画
	m_device.m_swapChain->Present(1, 0);					// 垂直同期描画
}

/// @brief コマンドリストの取得
/// @return コマンドリストのポインタ 
CommandList* D3D11Renderer::GetCommandList()
{
	if (m_useCmdListCnt[m_curBackBufferIndex] >= m_cmdLists[m_curBackBufferIndex].size())
	{
		auto up = std::make_unique<D3D11CommandList>();
		auto* ptr = up.get();
		ptr->initialize(this, &m_device);
		m_cmdLists[m_curBackBufferIndex].push_back(std::move(up));
		++m_useCmdListCnt[m_curBackBufferIndex];
		return ptr;
	}

	return m_cmdLists[m_curBackBufferIndex][m_useCmdListCnt[m_curBackBufferIndex]++].get();
}

/// @brief イミディエイトコンテキストでバッファ指定
void D3D11Renderer::SetD3D11BackBuffer()
{
	m_d3dContext->OMSetRenderTargets(1, m_device.m_backBufferRTV.GetAddressOf(), 
		m_device.m_depthStencilView.Get());
}

//------------------------------------------------------------------------------
// private methods
//------------------------------------------------------------------------------

/// @brief デバイスとコマンドリストの生成
/// @return HRESULT
HRESULT D3D11Renderer::CreateDiveceAndContext(HWND hWnd)
{
	HRESULT hr = S_OK;

	D3D_FEATURE_LEVEL featureLevels[] = {
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
	D3D_FEATURE_LEVEL_9_3,
	D3D_FEATURE_LEVEL_9_2,
	D3D_FEATURE_LEVEL_9_1,
	};

	// ファクトリーの取得
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), (void**)(&m_dxgiFactory));
	if (FAILED(hr)) {
		MessageBoxW(hWnd, L"CreateDXGIFactory1", L"Err", MB_ICONSTOP);
		return hr;
	}
	// アダプターの取得
	IDXGIAdapter* iAdapter = NULL;
	std::vector<IDXGIAdapter*> aiAdapter;
	aiAdapter.push_back(iAdapter);
	for (unsigned int index = 0;; index++)
	{
		HRESULT	ret = m_dxgiFactory->EnumAdapters(index, &iAdapter);

		if (ret == DXGI_ERROR_NOT_FOUND)
		{
			break;
		}
		// ～ アダプタの選択
		aiAdapter.push_back(iAdapter);
	}
	aiAdapter.pop_back();
	if (aiAdapter.size() <= 0)
	{
		aiAdapter.push_back(NULL);
	}


	//--- デバイスの生成 ---
	ComPtr<ID3D11Device>				device;
	ComPtr<ID3D11DeviceContext>		context;

	// デバイス。コマンドリストの生成
	hr = D3D11CreateDevice(
		aiAdapter.back(),
		aiAdapter.back() ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		featureLevels,
		7,
		D3D11_SDK_VERSION,
		device.GetAddressOf(),
		NULL,
		context.GetAddressOf());
	if (FAILED(hr)) {
		MessageBoxW(hWnd, L"D3D11CreateDevice", L"Err", MB_ICONSTOP);
		return hr;
	}

	// 格納
	hr = device.As(&m_d3dDevice);
	hr = context.As(&m_d3dContext);

	return hr;
}
