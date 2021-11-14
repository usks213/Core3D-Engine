/*****************************************************************//**
 * \file   D3D12_Device.h
 * \brief  DirectX12デバイス
 *
 * \author USAMI KOSHI
 * \date   2021/10/13
 *********************************************************************/

#include "D3D12_Device.h"
#include <Utils/Util_Hash.h>

#include <CoreRenderer/D3D12/D3D12_Buffer.h>
#include <CoreRenderer/D3D12/D3D12_DepthStencil.h>
#include <CoreRenderer/D3D12/D3D12_Material.h>
#include <CoreRenderer/D3D12/D3D12_RenderBuffer.h>
#include <CoreRenderer/D3D12/D3D12_RenderTarget.h>
#include <CoreRenderer/D3D12/D3D12_Shader.h>
#include <CoreRenderer/D3D12/D3D12_Texture.h>

using namespace core;
using namespace d3d12;

 //------------------------------------------------------------------------------
 // public methods
 //------------------------------------------------------------------------------

/// @brief コンストラクタ
D3D12Device::D3D12Device() :
	m_pD3DDevice(nullptr),
	//m_backBufferRT(nullptr),
	//m_backBufferRTV(nullptr),
	m_backBufferFormat(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM),
	//m_depthStencilTexture(nullptr),
	//m_depthStencilView(nullptr),
	m_depthStencilFormat(DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT),

	m_hWnd(nullptr),
	m_viewport(),
	m_backBufferCount(2u),
	m_nOutputWidth(1u),
	m_nOutputHeight(1u),

	m_blendStates{},
	m_rasterizeStates{},
	m_depthStencilStates{},
	m_dynamicSamplers{},
	m_staticSamplers{}
{

}

/// @brief 初期化処理
/// @param hWnd ウィンドウハンドル
/// @param width ウィンドウの幅
/// @param height ウィンドウの高さ
/// @return 初期化: 成功 true | 失敗 false
HRESULT D3D12Device::initialize(ID3D12Device* pDevice, IDXGIFactory2* pFactory2,
	HWND hWnd, UINT width, UINT height)
{
	// 初期化
	m_pD3DDevice = pDevice;
	m_hWnd = hWnd;
	m_nOutputWidth = width;
	m_nOutputHeight = height;

	// 共通ステートの初期化
	CHECK_FAILED(createCommonState());

	return S_OK;
}

//----- リソース生成 -----

core::BufferID D3D12Device::createBuffer(core::BufferDesc& desc, const core::BufferData* pData)
{
	// IDの取得
	BufferID id = static_cast<BufferID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_bufferPool.find(id);
	if (m_bufferPool.end() != itr) return id;

	// 新規生成
	m_bufferPool[id] = std::make_unique<D3D12Buffer>(m_pD3DDevice, id, desc, pData);

	return id;
}
core::DepthStencilID D3D12Device::createDepthStencil(core::TextureDesc& desc, float depth, std::uint8_t stencil)
{
	// IDの取得
	DepthStencilID id = static_cast<DepthStencilID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_depthStencilPool.find(id);
	if (m_depthStencilPool.end() != itr) return id;

	// クリアデータ
	D3D12_CLEAR_VALUE depthClearValue = {};
	depthClearValue.DepthStencil.Depth = depth;
	depthClearValue.DepthStencil.Stencil = stencil;
	depthClearValue.Format = d3d12::getTypeLessToDSVFormat(desc.format);

	// テクスチャ生成
	auto pTex = createD3D12Texture(desc, &depthClearValue);

	// デプスステンシル生成
	m_depthStencilPool[id] = std::make_unique<D3D12DepthStencil>(m_pD3DDevice, id, *pTex);

	return id;
}
core::MaterialID D3D12Device::createMaterial(std::string name, core::ShaderID& shaderID)
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
	m_materialPool[id] = std::make_unique<D3D12Material>(
		m_pD3DDevice, id, name, *shader);

	return id;
}
core::MeshID D3D12Device::createMesh(std::string name)
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
core::RenderBufferID D3D12Device::createRenderBuffer(core::ShaderID& shaderID, core::MeshID& meshID)
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
	m_renderBufferPool[id] = std::make_unique<D3D12RenderBuffer>(
		m_pD3DDevice, id, *shader, *mesh);

	return id;
}
core::RenderTargetID D3D12Device::createRenderTarget(core::TextureDesc& desc, const Color& color)
{
	// IDの取得
	RenderTargetID id = static_cast<RenderTargetID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_renderTargetPool.find(id);
	if (m_renderTargetPool.end() != itr) return id;

	// クリアデータ
	D3D12_CLEAR_VALUE rtvClearValue = {};
	std::memcpy(rtvClearValue.Color, &color, sizeof(Color));
	rtvClearValue.Format = d3d12::getDXGIFormat(desc.format);

	// テクスチャ生成
	auto pTex = createD3D12Texture(desc, &rtvClearValue);

	// デプスステンシル生成
	m_renderTargetPool[id] = std::make_unique<D3D12RenderTarget>(m_pD3DDevice, id, *pTex);

	return id;
}
core::ShaderID D3D12Device::createShader(core::ShaderDesc& desc)
{
	// IDの取得
	ShaderID id = static_cast<ShaderID>(util::stringHash(desc.m_name));

	// 既に生成済み
	const auto& itr = m_shaderPool.find(id);
	if (m_shaderPool.end() != itr) return id;

	// 新規生成
	m_shaderPool[id] = std::make_unique<D3D12Shader>(this, desc, id);

	return id;
}
core::TextureID D3D12Device::createTexture(std::string filePath)
{
	// IDの取得
	TextureID id = static_cast<TextureID>(util::stringHash(filePath));

	// 既に生成済み
	const auto& itr = m_texturePool.find(id);
	if (m_texturePool.end() != itr) return id;

	// 新規生成
	m_texturePool[id] = std::make_unique<D3D12Texture>(m_pD3DDevice, id, filePath);

	return id;
}
core::TextureID D3D12Device::createTexture(core::TextureDesc& desc, const core::TextureData* pData)
{
	// IDの取得
	TextureID id = static_cast<TextureID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_texturePool.find(id);
	if (m_texturePool.end() != itr) return id;

	// 新規生成
	m_texturePool[id] = std::make_unique<D3D12Texture>(m_pD3DDevice, id, desc, pData);

	return id;
}


 //------------------------------------------------------------------------------
 // private methods
 //------------------------------------------------------------------------------


/// @brief 共通ステートの生成
/// @return HRESULT
HRESULT D3D12Device::createCommonState()
{
	// ラスタライザステート作成
	{
		D3D12_RASTERIZER_DESC rasterizerDesc = {};

		// カリングなし 塗りつぶし
		rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		rasterizerDesc.CullMode =D3D12_CULL_MODE_NONE;
		m_rasterizeStates[(size_t)RasterizeState::CULL_NONE] = rasterizerDesc;

		// 表面カリング 塗りつぶし
		rasterizerDesc.CullMode =D3D12_CULL_MODE_FRONT;
		m_rasterizeStates[(size_t)RasterizeState::CULL_FRONT] = rasterizerDesc;

		// 裏面カリング 塗りつぶし
		rasterizerDesc.CullMode =D3D12_CULL_MODE_BACK;
		m_rasterizeStates[(size_t)RasterizeState::CULL_BACK] = rasterizerDesc;

		// カリングなし ワイヤーフレーム
		rasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
		rasterizerDesc.CullMode =D3D12_CULL_MODE_NONE;
		m_rasterizeStates[(size_t)RasterizeState::CULL_NONE_WIREFRAME] = rasterizerDesc;

		// 表面カリング ワイヤーフレーム
		rasterizerDesc.CullMode =D3D12_CULL_MODE_FRONT;
		m_rasterizeStates[(size_t)RasterizeState::CULL_FRONT_WIREFRAME] = rasterizerDesc;

		// 裏面カリング ワイヤーフレーム
		rasterizerDesc.CullMode =D3D12_CULL_MODE_BACK;
		m_rasterizeStates[(size_t)RasterizeState::CULL_BACK_WIREFRAME] = rasterizerDesc;

		// シャドウ用
		rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		rasterizerDesc.CullMode =D3D12_CULL_MODE_BACK;
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.DepthClipEnable = true;
		rasterizerDesc.DepthBias = 100000;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.SlopeScaledDepthBias = 2.0f;
		m_rasterizeStates[(size_t)RasterizeState::SHADOW] = rasterizerDesc;
	}

	// 静的サンプラステート作成
	{
		D3D12_STATIC_SAMPLER_DESC samplerDesc = {};

		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.MaxAnisotropy = D3D12_MAX_MAXANISOTROPY;

		// なし
		m_staticSamplers[static_cast<size_t>(SamplerState::NONE)] = samplerDesc;

		// リニアクランプ
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		m_staticSamplers[static_cast<size_t>(SamplerState::LINEAR_CLAMP)] = samplerDesc;

		// ポイントクランプ
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		m_staticSamplers[static_cast<size_t>(SamplerState::POINT_CLAMP)] = samplerDesc;

		// 異方性クランプ
		samplerDesc.Filter = D3D12_FILTER_ANISOTROPIC;
		m_staticSamplers[static_cast<size_t>(SamplerState::ANISOTROPIC_CLAMP)] = samplerDesc;

		// リニアラップ
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		m_staticSamplers[static_cast<size_t>(SamplerState::LINEAR_WRAP)] = samplerDesc;

		// ポイントラップ
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		m_staticSamplers[static_cast<size_t>(SamplerState::POINT_WRAP)] = samplerDesc;

		// 異方性ラップ
		samplerDesc.Filter = D3D12_FILTER_ANISOTROPIC;
		m_staticSamplers[static_cast<size_t>(SamplerState::ANISOTROPIC_WRAP)] = samplerDesc;

		// シャドウ
		samplerDesc.Filter = D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		m_staticSamplers[static_cast<size_t>(SamplerState::SHADOW)] = samplerDesc;
	}

	// 動的サンプラーステート
	{
		UINT num = static_cast<UINT>(SamplerState::MAX);
		// ヒープ作成
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
		heapDesc.NumDescriptors = num;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		heapDesc.NodeMask = 0;
		CHECK_FAILED(m_pD3DDevice->CreateDescriptorHeap(&heapDesc, 
			IID_PPV_ARGS(m_pSamplerHeap.ReleaseAndGetAddressOf())));

		// ハンドル
		auto cpuHandle = m_pSamplerHeap->GetCPUDescriptorHandleForHeapStart();
		auto gpuHandle = m_pSamplerHeap->GetGPUDescriptorHandleForHeapStart();
		auto descSize = m_pD3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);

		// サンプラーステート作成
		D3D12_SAMPLER_DESC samplerDesc = {};
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.MaxAnisotropy = D3D12_MAX_MAXANISOTROPY;
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;

		// なし
		m_pD3DDevice->CreateSampler(&samplerDesc, cpuHandle);
		m_dynamicSamplers[static_cast<size_t>(SamplerState::NONE)] = gpuHandle;
		cpuHandle.ptr += descSize;
		gpuHandle.ptr += descSize;

		// リニアクランプ
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		m_pD3DDevice->CreateSampler(&samplerDesc, cpuHandle);
		m_dynamicSamplers[static_cast<size_t>(SamplerState::LINEAR_CLAMP)] = gpuHandle;
		cpuHandle.ptr += descSize;
		gpuHandle.ptr += descSize;

		// ポイントクランプ
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		m_pD3DDevice->CreateSampler(&samplerDesc, cpuHandle);
		m_dynamicSamplers[static_cast<size_t>(SamplerState::POINT_CLAMP)] = gpuHandle;
		cpuHandle.ptr += descSize;
		gpuHandle.ptr += descSize;

		// 異方性クランプ
		samplerDesc.Filter = D3D12_FILTER_ANISOTROPIC;
		m_pD3DDevice->CreateSampler(&samplerDesc, cpuHandle);
		m_dynamicSamplers[static_cast<size_t>(SamplerState::ANISOTROPIC_CLAMP)] = gpuHandle;
		cpuHandle.ptr += descSize;
		gpuHandle.ptr += descSize;

		// リニアラップ
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		m_pD3DDevice->CreateSampler(&samplerDesc, cpuHandle);
		m_dynamicSamplers[static_cast<size_t>(SamplerState::LINEAR_WRAP)] = gpuHandle;
		cpuHandle.ptr += descSize;
		gpuHandle.ptr += descSize;

		// ポイントラップ
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		m_pD3DDevice->CreateSampler(&samplerDesc, cpuHandle);
		m_dynamicSamplers[static_cast<size_t>(SamplerState::POINT_WRAP)] = gpuHandle;
		cpuHandle.ptr += descSize;
		gpuHandle.ptr += descSize;

		// 異方性ラップ
		samplerDesc.Filter = D3D12_FILTER_ANISOTROPIC;
		m_pD3DDevice->CreateSampler(&samplerDesc, cpuHandle);
		m_dynamicSamplers[static_cast<size_t>(SamplerState::ANISOTROPIC_WRAP)] = gpuHandle;
		cpuHandle.ptr += descSize;
		gpuHandle.ptr += descSize;

		// シャドウ
		samplerDesc.Filter = D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		samplerDesc.BorderColor[0] = 1.0f;
		samplerDesc.BorderColor[1] = 1.0f;
		samplerDesc.BorderColor[2] = 1.0f;
		samplerDesc.BorderColor[3] = 1.0f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		m_pD3DDevice->CreateSampler(&samplerDesc, cpuHandle);
		m_dynamicSamplers[static_cast<size_t>(SamplerState::SHADOW)] = gpuHandle;

	}

	// ブレンドステート作成
	{
		D3D12_BLEND_DESC blendDesc = {};

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		// なし
		blendDesc.RenderTarget[0].BlendEnable = false;
		blendDesc.RenderTarget[0].LogicOpEnable = false;
		m_blendStates[static_cast<size_t>(BlendState::NONE)] = blendDesc;

		// 半透明合成
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
		m_blendStates[static_cast<size_t>(BlendState::ALPHA)] = blendDesc;

		// 加算合成
		blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;
		m_blendStates[static_cast<size_t>(BlendState::ADD)] = blendDesc;

		// 減算合成
		blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;
		m_blendStates[static_cast<size_t>(BlendState::SUB)] = blendDesc;

		// 乗算合成
		blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ZERO;
		blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_SRC_COLOR;
		m_blendStates[static_cast<size_t>(BlendState::MUL)] = blendDesc;

		// 反転合成
		blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_INV_DEST_COLOR;
		blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
		m_blendStates[static_cast<size_t>(BlendState::INV)] = blendDesc;
	}

	// 深度ステンシルステート作成
	{
		D3D12_DEPTH_STENCIL_DESC depthStencilDesc = {};

		m_depthStencilStates[static_cast<size_t>(DepthStencilState::UNKNOWN)] = depthStencilDesc;

		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		m_depthStencilStates[static_cast<size_t>(DepthStencilState::ENABLE_TEST_AND_ENABLE_WRITE)] = depthStencilDesc;

		depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
		m_depthStencilStates[static_cast<size_t>(DepthStencilState::ENABLE_TEST_AND_DISABLE_WRITE)] = depthStencilDesc;

		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_NEVER;
		depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		m_depthStencilStates[static_cast<size_t>(DepthStencilState::DISABLE_TEST_AND_ENABLE_WRITE)] = depthStencilDesc;

		depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
		m_depthStencilStates[static_cast<size_t>(DepthStencilState::DISABLE_TEST_AND_DISABLE_WRITE)] = depthStencilDesc;
	}

	return S_OK;
}

D3D12Texture* D3D12Device::createD3D12Texture(core::TextureDesc& desc, D3D12_CLEAR_VALUE* pClear)
{
	// IDの取得
	TextureID id = static_cast<TextureID>(util::stringHash(desc.name));

	// 既に生成済み
	const auto& itr = m_texturePool.find(id);
	if (m_texturePool.end() != itr) return nullptr;

	// 新規生成
	auto pD3D12Tex = std::make_unique<D3D12Texture>(m_pD3DDevice, id, desc, nullptr, pClear);
	auto pTex = pD3D12Tex.get();

	m_texturePool[id] = std::move(pD3D12Tex);

	return pTex;
}

ID3D12PipelineState* D3D12Device::createGraphicsPipelineState(D3D12Shader& d3d12Shader, const core::BlendState& bs,
	const core::RasterizeState& rs, const core::DepthStencilState& ds)
{
	// グラフィクスパイプラインを検索
	auto pipelineID = std::make_tuple(d3d12Shader.m_id, bs, rs, ds);
	auto itr = m_pGraphicsPipelineState.find(pipelineID);

	// パイプラインステートを新規作成
	if (m_pGraphicsPipelineState.end() == itr)
	{
		// グラフィクスパイプラインの作成
		D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline = {};
		// シグネチャー
		gpipeline.pRootSignature = d3d12Shader.m_pRootSignature.Get();
		// 各シェーダー
		D3D12_SHADER_BYTECODE* shaderByteCode[5] = 
		{ &gpipeline.VS, &gpipeline.HS, &gpipeline.DS, &gpipeline.GS, &gpipeline.PS };
		for (int i = 0; i < static_cast<int>(ShaderStage::CS); ++i)
		{
			if (d3d12Shader.m_pShaderBlob[i] != nullptr)
			{
				shaderByteCode[i]->pShaderBytecode = d3d12Shader.m_pShaderBlob[i]->GetBufferPointer();
				shaderByteCode[i]->BytecodeLength = d3d12Shader.m_pShaderBlob[i]->GetBufferSize();
			}
		}
		// ストリームアウトプット
		gpipeline.StreamOutput;
		// ブレンドステイト
		gpipeline.BlendState = m_blendStates[static_cast<std::size_t>(bs)];
		// サンプルマスク
		gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
		// ラスタライザーステート
		gpipeline.RasterizerState = m_rasterizeStates[static_cast<std::size_t>(rs)];
		// デプスステンシルステート
		gpipeline.DepthStencilState = m_depthStencilStates[static_cast<std::size_t>(ds)];
		// インプットレイアウト
		gpipeline.InputLayout.pInputElementDescs = d3d12Shader.m_inputElementDesc.data();
		gpipeline.InputLayout.NumElements = d3d12Shader.m_inputElementDesc.size();
		// ストリップカット
		gpipeline.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
		// プリミティブトポロジータイプ
		gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		// レンダーターゲット数
		gpipeline.NumRenderTargets = 1;
		// 各レンダーターゲットフォーマット
		gpipeline.RTVFormats[0] = m_backBufferFormat;
		// デプスステンシルフォーマット
		gpipeline.DSVFormat = m_depthStencilFormat;
		// サンプルDesc
		gpipeline.SampleDesc.Count = m_sampleDesc.count;
		gpipeline.SampleDesc.Quality = m_sampleDesc.quality;
		// ノードマスク
		gpipeline.NodeMask;
		// キャッシュPSO
		gpipeline.CachedPSO;
		// パイプラインフラグ
		gpipeline.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
		//gpipeline.Flags = D3D12_PIPELINE_STATE_FLAG_TOOL_DEBUG;

		// パイプラインステート作成
		ID3D12PipelineState* pPipelinestate = nullptr;
		CHECK_FAILED(m_pD3DDevice->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pPipelinestate)));
		if (pPipelinestate)
			m_pGraphicsPipelineState.emplace(pipelineID, pPipelinestate);
	}

	return m_pGraphicsPipelineState[pipelineID].Get();
}

//--- 更新リソース ---

/// @brief 更新リソースをリストに追加
/// @param pResource D3D12リソースポインタ
/// @param pData データポインタ
/// @param size データサイズ
void D3D12Device::AddUpdateResource(ID3D12Resource* pResource, void* pData, std::size_t size)
{
	UpdateResourceData updateData;
	updateData.pResource = pResource;
	updateData.data.resize(size);
	std::memcpy(updateData.data.data(), pData, size);

	m_updateResourceList.push_back(std::move(updateData));
}

/// @brief 更新リソースリストの実行
void D3D12Device::ExecuteUpdateResurce()
{
	// リソース更新
	for (auto& updateData : m_updateResourceList)
	{
		void* pData = nullptr;
		CHECK_FAILED(updateData.pResource->Map(0, 0, &pData));
		std::memcpy(pData, updateData.data.data(), updateData.data.size());
		updateData.pResource->Unmap(0, nullptr);
	}
	// リストクリア
	m_updateResourceList.clear();
	m_updateResourceList.shrink_to_fit();
}
