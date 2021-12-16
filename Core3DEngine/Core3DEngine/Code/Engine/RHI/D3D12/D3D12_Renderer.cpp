/*****************************************************************//**
 * \file   D3D12_Renderer.h
 * \brief  DirectX12レンダラー
 *
 * \author USAMI KOSHI
 * \date   2021/10/08
 *********************************************************************/

#include "D3D12_Renderer.h"
using namespace Core::D3D12;


//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief コンストラクタ
D3D12Renderer::D3D12Renderer() :
	m_eBackBufferSate{ D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_PRESENT }
{

}

/// @brief 初期化処理
/// @param hWnd ウィンドウハンドル
/// @param width ウィンドウの幅
/// @param height ウィンドウの高さ
/// @return 初期化: 成功 true | 失敗 false
HRESULT D3D12Renderer::initialize(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr = S_OK;

	//----- デバッグレイヤー・ファクトリー -----

#ifdef _DEBUG
	// デバッグレイヤー
	{
		hr = D3D12GetDebugInterface(IID_PPV_ARGS(m_pDebugLater.ReleaseAndGetAddressOf()));
		CHECK_FAILED(hr);
		m_pDebugLater->EnableDebugLayer();
	}
#endif // _DEBUG

	// ファクトリーの生成
	{
#ifdef _DEBUG
		hr = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(m_pDXGIFactory.ReleaseAndGetAddressOf()));
#else
		hr = CreateDXGIFactory1(IID_PPV_ARGS(m_pDXGIFactory.ReleaseAndGetAddressOf()));
#endif // _DEBUG
		CHECK_FAILED(hr);
	}

	//----- アダプタ・デバイス -----

	// デバイス生成
	hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(m_pD3DDevice.ReleaseAndGetAddressOf()));
	CHECK_FAILED(hr);


	//----- コマンドキュー -----
	D3D12_COMMAND_LIST_TYPE cmdType = D3D12_COMMAND_LIST_TYPE_DIRECT;
	UINT nodeMask = 0;

	// コマンドキューの生成
	{
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = cmdType;									// コマンドバッファの種類
		desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;	// コマンドキューの優先度
		desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;				// ??? GPUTimeOut
		desc.NodeMask = nodeMask;								// GPU識別マスク(1つは0)

		hr = m_pD3DDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(m_pCmdQueue.ReleaseAndGetAddressOf()));
		CHECK_FAILED(hr);
	}

	//----- スワップチェイン・フェンス・レンダーターゲット -----

	// スワップチェインの生成
	{
		DXGI_SWAP_CHAIN_DESC1 desc = {};
		desc.Width = width;
		desc.Height = height;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Stereo = false;								// フルスクリーン指定
		desc.SampleDesc = DXGI_SAMPLE_DESC{ 1,0 };	
		desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;			// バッファ識別
		desc.BufferCount = BACK_BUFFER_COUNT;				// バックバッファ数
		desc.Scaling = DXGI_SCALING_STRETCH;				// バックバッファのスケーリング指定
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// スワップ時のバッファの扱い
		desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;		// アルファモード??
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;// 動作オプション (フルスクリーン切り替え可)

		IDXGISwapChain1* pTempSwapChain1;
		hr = m_pDXGIFactory->CreateSwapChainForHwnd(
			m_pCmdQueue.Get(),
			hWnd,
			&desc,
			nullptr,
			nullptr,
			&pTempSwapChain1
		);
		CHECK_FAILED(hr);
		
		// スワップチェイン４に変換
		hr = pTempSwapChain1->QueryInterface(IID_PPV_ARGS(m_pSwapChain.ReleaseAndGetAddressOf()));
		CHECK_FAILED(hr);
		
		// フレームバッファ番号取得

	}

	// フェンスの生成
	{
		m_nFenceVal = 0;
		hr = m_pD3DDevice->CreateFence(m_nFenceVal, D3D12_FENCE_FLAG_NONE,
			IID_PPV_ARGS(m_pFence.ReleaseAndGetAddressOf()));
		CHECK_FAILED(hr);
	}

	// レンダーターゲットヒープの生成
	{
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// ピープタイプ
		desc.NumDescriptors = BACK_BUFFER_COUNT;		// バッファ数
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// シェーダーリソースか
		desc.NodeMask = nodeMask;

		hr = m_pD3DDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_pBackBufferHeap.ReleaseAndGetAddressOf()));
	}

	// レンダーターゲットビューの生成
	{
		// 先頭アドレスとオフセットサイズを取得
		auto handle = m_pBackBufferHeap->GetCPUDescriptorHandleForHeapStart();
		m_nBackBufferSize = m_pD3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_RENDER_TARGET_VIEW_DESC desc = {};
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;	// MSAA off

		// バックバッファからレンダーターゲットを生成
		for (UINT i = 0; i < BACK_BUFFER_COUNT; ++i)
		{
			// バックバッファ取得
			hr = m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(m_pBackBuffer[i].ReleaseAndGetAddressOf()));
			CHECK_FAILED(hr);

			// レンダーターゲットビューの生成
			m_pD3DDevice->CreateRenderTargetView(m_pBackBuffer[i].Get(), &desc, handle);
			// ハンドルのポインタを進める
			handle.ptr += m_nBackBufferSize;
		}
	}

	//深度バッファ作成
	{
		//深度バッファの仕様
		D3D12_RESOURCE_DESC depthResDesc = {};
		depthResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;//2次元のテクスチャデータとして
		depthResDesc.Width = width;//幅と高さはレンダーターゲットと同じ
		depthResDesc.Height = height;//上に同じ
		depthResDesc.DepthOrArraySize = 1;//テクスチャ配列でもないし3Dテクスチャでもない
		depthResDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度値書き込み用フォーマット
		depthResDesc.SampleDesc.Count = 1;//サンプルは1ピクセル当たり1つ
		depthResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;//このバッファは深度ステンシルとして使用します
		depthResDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		depthResDesc.MipLevels = 1;

		//デプス用ヒーププロパティ
		D3D12_HEAP_PROPERTIES depthHeapProp = {};
		depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;//DEFAULTだから後はUNKNOWNでよし
		depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		//このクリアバリューが重要な意味を持つ
		D3D12_CLEAR_VALUE _depthClearValue = {};
		_depthClearValue.DepthStencil.Depth = 1.0f;//深さ１(最大値)でクリア
		_depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;//32bit深度値としてクリア

		m_pD3DDevice->CreateCommittedResource(
			&depthHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthResDesc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE, //デプス書き込みに使用
			&_depthClearValue,
			IID_PPV_ARGS(m_pDepthStencil.ReleaseAndGetAddressOf()));

		//深度のためのデスクリプタヒープ作成
		D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};//深度に使うよという事がわかればいい
		dsvHeapDesc.NumDescriptors = 1;//深度ビュー1つのみ
		dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;//デプスステンシルビューとして使う
		dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		m_pD3DDevice->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(m_pDepthStencilHeap.ReleaseAndGetAddressOf()));

		//深度ビュー作成
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//デプス値に32bit使用
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;//2Dテクスチャ
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;//フラグは特になし
		m_pD3DDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &dsvDesc, 
			m_pDepthStencilHeap->GetCPUDescriptorHandleForHeapStart());
	}


	// デバイスの生成
	m_device.initialize(m_pD3DDevice.Get(), m_pDXGIFactory.Get(), hWnd, width, height);

	return hr;
}

/// @brief 終了処理
void D3D12Renderer::finalize()
{
	HRESULT hr = S_OK;

	// コマンド完了待ち
	hr = m_pCmdQueue->Signal(m_pFence.Get(), ++m_nFenceVal);
	CHECK_FAILED(hr);

	// フェンス処理
	if (m_pFence->GetCompletedValue() != m_nFenceVal)
	{
		// イベント発行
		auto hEvent = CreateEvent(nullptr, false, false, nullptr);
		hr = m_pFence->SetEventOnCompletion(m_nFenceVal, hEvent);
		CHECK_FAILED(hr);
		// イベント終了待ち
		WaitForSingleObject(hEvent, INFINITE);
		// イベントを閉じる
		CloseHandle(hEvent);
	}

	// 表示
	m_pSwapChain->Present(1, 0);
}

/// @brief フレーム開始
void D3D12Renderer::beginFrame()
{
	HRESULT hr = S_OK;

	//--- リソースの更新
	// GPU側のバッファ、テクスチャなど更新

	// リソース更新
	m_device.ExecuteUpdateResurce();


	//--- コマンド発行
	// 前フレームで貯めたコマンドの発行

	// コマンドリストを格納
	std::vector<ID3D12CommandList*> ppCmdList;
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		ppCmdList.push_back(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList.Get());
	}

	// コマンドの実行
	m_pCmdQueue->ExecuteCommandLists(ppCmdList.size(), ppCmdList.data());


	//--- 現フレームのコマンド準備
	// バックバッファ入れ替え

	// 現在のバックバッファインデックス
	m_curBackBufferIndex = (m_pSwapChain->GetCurrentBackBufferIndex() + 1) % BACK_BUFFER_COUNT;

	// コマンドアロケーターとコマンドリストをリセット
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		CHECK_FAILED(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdAllocator->Reset());
		CHECK_FAILED(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList->
			Reset(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdAllocator.Get(), nullptr));
	}
	m_useCmdListCnt[m_curBackBufferIndex] = 0;

}

/// @brief フレーム終了
void D3D12Renderer::endFrame()
{
	HRESULT hr = S_OK;

	if (m_eBackBufferSate[m_curBackBufferIndex] != D3D12_RESOURCE_STATE_PRESENT && 
		m_cmdLists[m_curBackBufferIndex].size() > 0)
	{
		// レンダーターゲットのバリア指定
		D3D12_RESOURCE_BARRIER barrierDesc = {};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;					// バリア種別(遷移)
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;						// バリア分割用
		barrierDesc.Transition.pResource = m_pBackBuffer[m_curBackBufferIndex].Get();	// リソースポインタ
		barrierDesc.Transition.Subresource = 										// サブリソースの数
			D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;								// リソース内のすべてのサブリソースを同時に移行
		barrierDesc.Transition.StateBefore = m_eBackBufferSate[m_curBackBufferIndex];	// 遷移前のリソース状態
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			// 遷移後のリソース状態

		// 最後のコマンドにリソースバリア
		m_cmdLists[m_curBackBufferIndex].back()->m_pCmdList->ResourceBarrier(1, &barrierDesc);
		m_eBackBufferSate[m_curBackBufferIndex] = D3D12_RESOURCE_STATE_PRESENT;
	}

	// コマンドの記録終了
	for (int i = 0; i < m_useCmdListCnt[m_curBackBufferIndex]; ++i)
	{
		CHECK_FAILED(m_cmdLists[m_curBackBufferIndex][i]->m_pCmdList->Close());
	}

	//--- 前フレームのコマンド完了を待つ

	// コマンド完了待ち
	hr = m_pCmdQueue->Signal(m_pFence.Get(), ++m_nFenceVal);
	CHECK_FAILED(hr);

	// フェンス処理
	if (m_pFence->GetCompletedValue() != m_nFenceVal)
	{
		// イベント発行
		auto hEvent = CreateEvent(nullptr, false, false, nullptr);
		hr = m_pFence->SetEventOnCompletion(m_nFenceVal, hEvent);
		CHECK_FAILED(hr);
		// イベント終了待ち
		WaitForSingleObject(hEvent, INFINITE);
		// イベントを閉じる
		CloseHandle(hEvent);
	}

	// 表示
	m_pSwapChain->Present(1, 0);
}

/// @brief コマンドリストの取得
/// @return コマンドリストのポインタ 
Core::CommandList* D3D12Renderer::GetCommandList()
{
	if (m_useCmdListCnt[m_curBackBufferIndex] >= m_cmdLists[m_curBackBufferIndex].size())
	{
		auto up = std::make_unique<D3D12CommandList>();
		auto* ptr = up.get();
		ptr->initialize(this, &m_device);
		m_cmdLists[m_curBackBufferIndex].push_back(std::move(up));
		++m_useCmdListCnt[m_curBackBufferIndex];
		return ptr;
	}

	return m_cmdLists[m_curBackBufferIndex][m_useCmdListCnt[m_curBackBufferIndex]++].get();
}