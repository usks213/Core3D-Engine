/*****************************************************************//**
 * \file   D3D11_Device.cpp
 * \brief  DirectX11デバイス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#include "D3D11_Device.h"
#include <Utils/Util_Hash.h>

#include <CoreRenderer/D3D11/D3D11_Buffer.h>
#include <CoreRenderer/D3D11/D3D11_DepthStencil.h>
#include <CoreRenderer/D3D11/D3D11_Material.h>
#include <CoreRenderer/D3D11/D3D11_RenderBuffer.h>
#include <CoreRenderer/D3D11/D3D11_RenderTarget.h>
#include <CoreRenderer/D3D11/D3D11_Shader.h>
#include <CoreRenderer/D3D11/D3D11_Texture.h>

using namespace core;
using namespace d3d11;

 //------------------------------------------------------------------------------
 // public methods
 //------------------------------------------------------------------------------

/// @brief コンストラクタ
D3D11Device::D3D11Device() :
	m_pD3DDevice(nullptr),
	m_backBufferRT(nullptr),
	m_backBufferRTV(nullptr),
	m_backBufferFormat(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM),
	m_depthStencilTexture(nullptr),
	m_depthStencilView(nullptr),
	m_depthStencilFormat(DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT),

	m_hWnd(nullptr),
	m_viewport(),
	m_backBufferCount(2u),
	m_nOutputWidth(1u),
	m_nOutputHeight(1u)
{

}

/// @brief 初期化処理
/// @param hWnd ウィンドウハンドル
/// @param width ウィンドウの幅
/// @param height ウィンドウの高さ
/// @return 初期化: 成功 true | 失敗 false
HRESULT D3D11Device::initialize(ID3D11Device1* pDevice, IDXGIFactory2* pFactory2,
	HWND hWnd, UINT width, UINT height, UINT backBufferCount)
{
	// 初期化
	m_pD3DDevice = pDevice;
	m_hWnd = hWnd;
	m_nOutputWidth = width;
	m_nOutputHeight = height;
	m_backBufferCount = backBufferCount;

	// スワップチェーンとバッファの初期化
	CHECK_FAILED(createSwapChainAndBuffer(pFactory2));

	// 共通ステートの初期化
	CHECK_FAILED(createCommonState());

	return S_OK;
}

//----- リソース生成 -----

core::BufferID D3D11Device::createBuffer(core::BufferDesc& desc, const core::BufferData* pData)
{
	// IDの取得
	BufferID id = static_cast<BufferID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_bufferPool.find(id);
	if (m_bufferPool.end() != itr) return id;

	// 新規生成
	m_bufferPool[id] = std::make_unique<D3D11Buffer>(m_pD3DDevice, id, desc, pData);

	return id;
}
core::DepthStencilID D3D11Device::createDepthStencil(core::TextureDesc& desc, float depth, std::uint8_t stencil)
{
	// IDの取得
	DepthStencilID id = static_cast<DepthStencilID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_depthStencilPool.find(id);
	if (m_depthStencilPool.end() != itr) return id;

	// テクスチャ生成
	auto texID = createTexture(desc, nullptr);
	auto pTex = static_cast<D3D11Texture*>(getTexture(texID));

	// デプスステンシル生成
	m_depthStencilPool[id] = std::make_unique<D3D11DepthStencil>(m_pD3DDevice, id, *pTex);

	return id;
}
core::MaterialID D3D11Device::createMaterial(std::string name, core::ShaderID& shaderID)
{
	// IDの取得
	MaterialID id = static_cast<MaterialID>(util::stringHash(name));

	// 既に生成済み
	const auto& itr = m_materialPool.find(id);
	if (m_materialPool.end() != itr) return id;

	// シェーダー取得
	auto* shader = getShader(shaderID);
	if (shader == nullptr) return NONE_MATERIAL_ID;

	// 新規生成
	m_materialPool[id] = std::make_unique<D3D11Material>(
		m_pD3DDevice, id, name, *shader);

	return id;
}
core::MeshID D3D11Device::createMesh(std::string name)
{
	// IDの取得
	MeshID id = static_cast<MeshID>(util::stringHash(name));

	// 既に生成済み
	const auto& itr = m_meshPool.find(id);
	if (m_meshPool.end() != itr) return id;

	// 新規生成
	m_meshPool[id] = std::make_unique<CoreMesh>(id, name);

	return id;
}
core::RenderBufferID D3D11Device::createRenderBuffer(core::ShaderID& shaderID, core::MeshID& meshID)
{
	// シェーダー取得
	auto* shader = getShader(shaderID);
	if (shader == nullptr) return NONE_RENDERBUFFER_ID;
	// メッシュ取得
	auto* mesh = getMesh(meshID);
	if (mesh == nullptr) return NONE_RENDERBUFFER_ID;
	
	// IDの生成
	RenderBufferID id = static_cast<RenderBufferID>(
		util::stringHash(shader->m_desc.m_name + ":" + mesh->m_name));

	// 既にある
	const auto& itr = m_renderBufferPool.find(id);
	if (m_renderBufferPool.end() != itr) return id;

	// 新規生成
	m_renderBufferPool[id] = std::make_unique<D3D11RenderBuffer>(
		m_pD3DDevice, id, *shader, *mesh);

	return id;
}
core::RenderTargetID D3D11Device::createRenderTarget(core::TextureDesc& desc, const Color& color)
{
	// IDの取得
	RenderTargetID id = static_cast<RenderTargetID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_renderTargetPool.find(id);
	if (m_renderTargetPool.end() != itr) return id;

	// テクスチャ生成
	auto texID = createTexture(desc, nullptr);
	auto pTex = static_cast<D3D11Texture*>(getTexture(texID));

	// レンダーターゲット生成
	m_renderTargetPool[id] = std::make_unique<D3D11RenderTarget>(m_pD3DDevice, id, *pTex);

	return id;
}
core::ShaderID D3D11Device::createShader(core::ShaderDesc& desc)
{
	// IDの取得
	ShaderID id = static_cast<ShaderID>(util::stringHash(desc.m_name));

	// 既に生成済み
	const auto& itr = m_shaderPool.find(id);
	if (m_shaderPool.end() != itr) return id;

	// 新規生成
	m_shaderPool[id] = std::make_unique<D3D11Shader>(m_pD3DDevice, desc, id);

	return id;
}
core::TextureID D3D11Device::createTexture(std::string filePath)
{
	// IDの取得
	TextureID id = static_cast<TextureID>(util::stringHash(filePath));

	// 既に生成済み
	const auto& itr = m_texturePool.find(id);
	if (m_texturePool.end() != itr) return id;

	// 新規生成
	m_texturePool[id] = std::make_unique<D3D11Texture>(m_pD3DDevice, id, filePath);

	return id;
}
core::TextureID D3D11Device::createTexture(core::TextureDesc& desc, const core::TextureData* pData)
{
	// IDの取得
	TextureID id = static_cast<TextureID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_texturePool.find(id);
	if (m_texturePool.end() != itr) return id;

	// 新規生成
	m_texturePool[id] = std::make_unique<D3D11Texture>(m_pD3DDevice, id, desc, pData);

	return id;
}


 //------------------------------------------------------------------------------
 // private methods
 //------------------------------------------------------------------------------

/// @brief スワップチェーンとバッファの生成
/// @return HRESULT
HRESULT D3D11Device::createSwapChainAndBuffer(IDXGIFactory2* pFactory2)
{
	HRESULT hr = S_OK;
	HWND &hWnd = m_hWnd;

	// レンダーターゲットのサイズ指定
	UINT backBufferWidth = std::max<UINT>(m_nOutputWidth, 1u);
	UINT backBufferHeight = std::max<UINT>(m_nOutputHeight, 1u);

	//使用可能なMSAAを取得
	if (m_sampleDesc.isUse)
	{
		for (int i = 0; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i++) {
			UINT Quality;
			if SUCCEEDED(m_pD3DDevice->CheckMultisampleQualityLevels(m_backBufferFormat, i, &Quality)) {
				if (0 < Quality) {
					m_sampleDesc.count = i;
					m_sampleDesc.quality = Quality - 1;
				}
			}
		}
	}
	DXGI_SAMPLE_DESC dxgiSampleDesc = { m_sampleDesc.count, m_sampleDesc.quality };

	//--- スワップチェイン ---
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = backBufferWidth;
	swapChainDesc.Height = backBufferHeight;
	swapChainDesc.Format = m_backBufferFormat;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = m_backBufferCount;
	swapChainDesc.SampleDesc = dxgiSampleDesc;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	swapChainDesc.Flags = 0;
	//swapChainDesc.Flags = (m_options & ALLOW_TEARING) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;
	// フルスクリーン指定
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
	fsSwapChainDesc.Windowed = TRUE;

	// スワップチェーンの作成
	hr = pFactory2->CreateSwapChainForHwnd(
		m_pD3DDevice,
		m_hWnd,
		&swapChainDesc,
		&fsSwapChainDesc,
		nullptr,
		m_swapChain.ReleaseAndGetAddressOf());
	if (FAILED(hr)) {
		MessageBoxW(hWnd, L"CreateSwapChainForHwnd", L"Err", MB_ICONSTOP);
		return hr;
	}

	// 排他的フルスクリーンモードを無効化
	hr = pFactory2->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_ALT_ENTER);
	if (FAILED(hr)) {
		MessageBoxW(hWnd, L"MakeWindowAssociation", L"Err", MB_ICONSTOP);
		return hr;
	}


	//--- バックバッファRT ---

	// フォーマットサポートチェック
	std::uint32_t formatSupport = 0;
	if (FAILED(m_pD3DDevice->CheckFormatSupport(m_backBufferFormat, &formatSupport)))
	{
		MessageBoxW(hWnd, L"CheckFormatSupport", L"Err", MB_ICONSTOP);
		return E_FAIL;
	}

	// バックバッファレンダーターゲットの作成
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)m_backBufferRT.ReleaseAndGetAddressOf());

	CD3D11_RENDER_TARGET_VIEW_DESC rtvDesc(D3D11_RTV_DIMENSION_TEXTURE2D, m_backBufferFormat);
	if (m_sampleDesc.isUse) rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	// レンダーターゲットビュー作成
	hr = m_pD3DDevice->CreateRenderTargetView(
		m_backBufferRT.Get(),
		&rtvDesc,
		m_backBufferRTV.ReleaseAndGetAddressOf());
	if (FAILED(hr)) {
		MessageBoxW(hWnd, L"CreateRenderTargetView", L"Err", MB_ICONSTOP);
		return hr;
	}

	//--- 深度ステンシル ---
	CD3D11_TEXTURE2D_DESC dsDesc(m_depthStencilFormat, backBufferWidth, backBufferHeight,
		1, 1, D3D11_BIND_DEPTH_STENCIL);
	if (m_sampleDesc.isUse) dsDesc.SampleDesc = dxgiSampleDesc;
	// 深度ステンシルテクスチャ作成
	hr = m_pD3DDevice->CreateTexture2D(&dsDesc, nullptr,
		m_depthStencilTexture.ReleaseAndGetAddressOf());
	CHECK_FAILED(hr);
	// 深度ステンシルテクスチャビュー
	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	if (m_sampleDesc.isUse) dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	hr = m_pD3DDevice->CreateDepthStencilView(m_depthStencilTexture.Get(),
		&dsvDesc, m_depthStencilView.ReleaseAndGetAddressOf());
	CHECK_FAILED(hr);

	// ビューポート
	m_viewport = CD3D11_VIEWPORT(0.0f, 0.0f,
		static_cast<float>(backBufferWidth),
		static_cast<float>(backBufferHeight));

	return S_OK;
}

/// @brief 共通ステートの生成
/// @return HRESULT
HRESULT D3D11Device::createCommonState()
{
	// ラスタライザステート作成
	{
		D3D11_RASTERIZER_DESC rasterizerDesc = {};

		// カリングなし 塗りつぶし
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		CHECK_FAILED(m_pD3DDevice->CreateRasterizerState(&rasterizerDesc,
			m_rasterizeStates[(size_t)RasterizeState::CULL_NONE].GetAddressOf()));

		// 表面カリング 塗りつぶし
		rasterizerDesc.CullMode = D3D11_CULL_FRONT;
		CHECK_FAILED(m_pD3DDevice->CreateRasterizerState(&rasterizerDesc,
			m_rasterizeStates[(size_t)RasterizeState::CULL_FRONT].GetAddressOf()));

		// 裏面カリング 塗りつぶし
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		CHECK_FAILED(m_pD3DDevice->CreateRasterizerState(&rasterizerDesc,
			m_rasterizeStates[(size_t)RasterizeState::CULL_BACK].GetAddressOf()));

		// カリングなし ワイヤーフレーム
		rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		CHECK_FAILED(m_pD3DDevice->CreateRasterizerState(&rasterizerDesc,
			m_rasterizeStates[(size_t)RasterizeState::CULL_NONE_WIREFRAME].GetAddressOf()));

		// 表面カリング ワイヤーフレーム
		rasterizerDesc.CullMode = D3D11_CULL_FRONT;
		CHECK_FAILED(m_pD3DDevice->CreateRasterizerState(&rasterizerDesc,
			m_rasterizeStates[(size_t)RasterizeState::CULL_FRONT_WIREFRAME].GetAddressOf()));

		// 裏面カリング ワイヤーフレーム
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		CHECK_FAILED(m_pD3DDevice->CreateRasterizerState(&rasterizerDesc,
			m_rasterizeStates[(size_t)RasterizeState::CULL_BACK_WIREFRAME].GetAddressOf()));

		// シャドウ用
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.DepthClipEnable = true;
		rasterizerDesc.DepthBias = 100000;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.SlopeScaledDepthBias = 2.0f;
		CHECK_FAILED(m_pD3DDevice->CreateRasterizerState(&rasterizerDesc,
			m_rasterizeStates[(size_t)RasterizeState::SHADOW].GetAddressOf()));
	}

	// サンプラステート作成
	{
		D3D11_SAMPLER_DESC samplerDesc = {};

		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0.f;
		samplerDesc.BorderColor[1] = 0.f;
		samplerDesc.BorderColor[2] = 0.f;
		samplerDesc.BorderColor[3] = 0.f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		samplerDesc.MaxAnisotropy = (m_pD3DDevice->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? D3D11_MAX_MAXANISOTROPY : 2;

		// リニアクランプ
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		CHECK_FAILED(m_pD3DDevice->CreateSamplerState(&samplerDesc, m_samplerStates[static_cast<size_t>(SamplerState::LINEAR_CLAMP)].GetAddressOf()));

		// ポイントクランプ
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		CHECK_FAILED(m_pD3DDevice->CreateSamplerState(&samplerDesc, m_samplerStates[static_cast<size_t>(SamplerState::POINT_CLAMP)].GetAddressOf()));

		// 異方性クランプ
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		CHECK_FAILED(m_pD3DDevice->CreateSamplerState(&samplerDesc, m_samplerStates[static_cast<size_t>(SamplerState::ANISOTROPIC_CLAMP)].GetAddressOf()));

		// リニアラップ
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		CHECK_FAILED(m_pD3DDevice->CreateSamplerState(&samplerDesc, m_samplerStates[static_cast<size_t>(SamplerState::LINEAR_WRAP)].GetAddressOf()));

		// ポイントラップ
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		CHECK_FAILED(m_pD3DDevice->CreateSamplerState(&samplerDesc, m_samplerStates[static_cast<size_t>(SamplerState::POINT_WRAP)].GetAddressOf()));

		// 異方性ラップ
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		CHECK_FAILED(m_pD3DDevice->CreateSamplerState(&samplerDesc, m_samplerStates[static_cast<size_t>(SamplerState::ANISOTROPIC_WRAP)].GetAddressOf()));

		// シャドウ
		samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
		samplerDesc.BorderColor[0] = 1.0f;
		samplerDesc.BorderColor[1] = 1.0f;
		samplerDesc.BorderColor[2] = 1.0f;
		samplerDesc.BorderColor[3] = 1.0f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		CHECK_FAILED(m_pD3DDevice->CreateSamplerState(&samplerDesc, m_samplerStates[static_cast<size_t>(SamplerState::SHADOW)].GetAddressOf()));
	}

	// ブレンドステート作成
	{
		D3D11_BLEND_DESC blendDesc = {};

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// 半透明合成
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		CHECK_FAILED(m_pD3DDevice->CreateBlendState(&blendDesc, m_blendStates[static_cast<size_t>(BlendState::ALPHA)].GetAddressOf()));

		// 加算合成
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		CHECK_FAILED(m_pD3DDevice->CreateBlendState(&blendDesc, m_blendStates[static_cast<size_t>(BlendState::ADD)].GetAddressOf()));

		// 減算合成
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		CHECK_FAILED(m_pD3DDevice->CreateBlendState(&blendDesc, m_blendStates[static_cast<size_t>(BlendState::SUB)].GetAddressOf()));

		// 乗算合成
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
		CHECK_FAILED(m_pD3DDevice->CreateBlendState(&blendDesc, m_blendStates[static_cast<size_t>(BlendState::MUL)].GetAddressOf()));

		// 反転合成
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_INV_DEST_COLOR;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		CHECK_FAILED(m_pD3DDevice->CreateBlendState(&blendDesc, m_blendStates[static_cast<size_t>(BlendState::INV)].GetAddressOf()));
	}

	// 深度ステンシルステート作成
	{
		m_depthStencilStates[static_cast<size_t>(DepthStencilState::UNKNOWN)] = nullptr;

		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

		CHECK_FAILED(m_pD3DDevice->CreateDepthStencilState(&depthStencilDesc, m_depthStencilStates[static_cast<size_t>(DepthStencilState::ENABLE_TEST_AND_ENABLE_WRITE)].GetAddressOf()));

		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

		CHECK_FAILED(m_pD3DDevice->CreateDepthStencilState(&depthStencilDesc, m_depthStencilStates[static_cast<size_t>(DepthStencilState::ENABLE_TEST_AND_DISABLE_WRITE)].GetAddressOf()));

		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_NEVER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

		CHECK_FAILED(m_pD3DDevice->CreateDepthStencilState(&depthStencilDesc, m_depthStencilStates[static_cast<size_t>(DepthStencilState::DISABLE_TEST_AND_ENABLE_WRITE)].GetAddressOf()));

		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

		CHECK_FAILED(m_pD3DDevice->CreateDepthStencilState(&depthStencilDesc, m_depthStencilStates[static_cast<size_t>(DepthStencilState::DISABLE_TEST_AND_DISABLE_WRITE)].GetAddressOf()));
	}

	return S_OK;
}

/// @brief 更新リソースをリストに追加
/// @param pResource D3D12リソースポインタ
/// @param pData データポインタ
/// @param size データサイズ
void D3D11Device::AddUpdateResource(ID3D11Resource* pResource, void* pData, std::size_t size)
{
	UpdateResourceData updateData;
	updateData.pResource = pResource;
	updateData.data.resize(size);
	std::memcpy(updateData.data.data(), pData, size);

	m_updateResourceList.push_back(std::move(updateData));
}

/// @brief 更新リソースリストの実行
void D3D11Device::ExecuteUpdateResurce(ID3D11DeviceContext1* pContext)
{
	// リソース更新
	for (auto& updateData : m_updateResourceList)
	{
		D3D11_MAPPED_SUBRESOURCE subData = {};
		CHECK_FAILED(pContext->Map(updateData.pResource, 0, 
			D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subData));
		std::memcpy(subData.pData, updateData.data.data(), updateData.data.size());
		pContext->Unmap(updateData.pResource, 0);
	}
	// リストクリア
	m_updateResourceList.clear();
	m_updateResourceList.shrink_to_fit();
}
