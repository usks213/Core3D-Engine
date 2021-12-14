/*****************************************************************//**
 * \file   D3D11_GraphicsShader.h
 * \brief  DirectX11グラフィックスシェーダー
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#include "D3D11_GraphicsShader.h"
#include "D3D11_CommonState.h"

#include <RHI\D3D\D3D_ShaderCompiler.h>

using namespace Core::RHI;
using namespace Core::RHI::D3D;
using namespace Core::RHI::D3D11;

namespace {
	/// @brief シェーダファイルパス
	const char* SHADER_FILE_PATH = "Assets/Shader/";

	/// @brief エントリーポイント、ファイル識別子
	const char* SHADER_TYPES[] = {
		"VS","GS","DS","HS","PS","CS",
	};
}

/// @brief  コンストラクタ
/// @param device デバイス
/// @param desc シェーダ情報
D3D11GraphicsShader::D3D11GraphicsShader(ID3D11Device1* device, const GraphicsShaderDesc& desc) :
	GraphicsShader(desc),
	m_comGraphicsShaders(static_cast<size_t>(GraphicsShaderStage::MAX)),
	m_pInputLayout(),
	vs(nullptr),
	gs(nullptr),
	ds(nullptr),
	hs(nullptr),
	ps(nullptr)
{
	// 初期化
	for (auto* shader : shaders) {
		shader = nullptr;
	}

	// コンパイルしたシェーダデータ
	std::vector<ComPtr<ID3DBlob>>				blobs(static_cast<size_t>(GraphicsShaderStage::MAX));
	// シェーダリフレクション
	std::vector<ComPtr<ID3D11ShaderReflection>>	reflections(static_cast<size_t>(GraphicsShaderStage::MAX));
	// シェーダ情報一時格納用
	D3D11_SHADER_DESC							shaderDesc = {};


	// シェーダステージ数だけコンパイルを試す
	for (auto stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		// ステージがない場合はスキップ
		if (!hasStaderStage(desc.m_stages, stage)) continue;

		ComPtr<ID3DBlob>& blob = blobs[static_cast<size_t>(stage)];
		ComPtr<ID3D11ShaderReflection>& reflection = reflections[static_cast<size_t>(stage)];

		// パス
		std::string filepath = SHADER_FILE_PATH + desc.m_name + "_" +
			SHADER_TYPES[static_cast<size_t>(stage)] + ".hlsl";
		// シェーダーコンパイル
		if (D3DShaderCompiler::CompileFromFile(filepath, (ShaderStage)stage, blob.Get()))
		{

		}
		else
		{
			// 失敗
		}
	}

	// 頂点シェーダがある場合はインプットレイアウトを作成
	auto& vsReflection = reflections[static_cast<size_t>(GraphicsShaderStage::VS)];
	if (vsReflection)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
		auto& vsBlob = blobs[static_cast<size_t>(GraphicsShaderStage::VS)];

		// インプットレイアウトの作成
		if (D3DShaderCompiler::CreateInputLayout(vsReflection.Get(), inputLayouts, m_inputLayout))
		{
			// 入力レイアウト情報作成
			if (!inputLayouts.empty()) {
				CHECK_FAILED(device->CreateInputLayout(
					inputLayouts.data(),
					shaderDesc.InputParameters,
					vsBlob->GetBufferPointer(),
					vsBlob->GetBufferSize(),
					m_pInputLayout.GetAddressOf()));
			}
		}
	}

	// 入力バインドデータの作成
	D3D11_SHADER_BUFFER_DESC shaderGPUBufferDesc = {};
	for (auto stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		const auto& stageIndex = static_cast<size_t>(stage);
		const auto& reflection = reflections[stageIndex];
		if (!reflection) continue;
		
		// リソースレイアウトの作成
		if (D3DShaderCompiler::CreateResourceLayout(reflection.Get(), m_resourceLayout[stageIndex]))
		{
			// 成功
		}
		else
		{
			// 失敗
			continue;
		}

		// リフレクションからコンスタントバッファ読み込み
		if (D3DShaderCompiler::CreateCBufferLayouts(reflection.Get(), 
			m_resourceLayout[stageIndex], m_cbufferLayout[stageIndex]))
		{
			// 成功
		}
		else
		{
			// 失敗
			continue;
		}
	}
}

/// @brief シェーダオブジェクト生成
/// @param device デバイス
/// @param stage シェーダステージ
/// @param blob コンパイルデータ
void D3D11GraphicsShader::CreateShaderObjct(ID3D11Device1* device, const GraphicsShaderStage& stage, ComPtr<ID3DBlob>& blob)
{
	// com参照
	auto& shader = m_comShaders[static_cast<size_t>(stage)];

	// シェーダ種別生成
	switch (stage)
	{
	case GraphicsShaderStage::VS:
	{
		ID3D11VertexShader* d3d11Shader;
		CHECK_FAILED(device->CreateVertexShader(blob->GetBufferPointer(), 
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// インターフェース生成(参照カウント増加)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild), 
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// 参照カウントを減らす
		d3d11Shader->Release();
		vs = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::GS:
	{
		ID3D11GeometryShader* d3d11Shader;
		CHECK_FAILED(device->CreateGeometryShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// インターフェース生成(参照カウント増加)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// 参照カウントを減らす
		d3d11Shader->Release();
		gs = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::DS:
	{
		ID3D11DomainShader* d3d11Shader;
		CHECK_FAILED(device->CreateDomainShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// インターフェース生成(参照カウント増加)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// 参照カウントを減らす
		d3d11Shader->Release();
		ds = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::HS:
	{
		ID3D11HullShader* d3d11Shader;
		CHECK_FAILED(device->CreateHullShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// インターフェース生成(参照カウント増加)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// 参照カウントを減らす
		d3d11Shader->Release();
		hs = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::PS:
	{
		ID3D11PixelShader* d3d11Shader;
		CHECK_FAILED(device->CreatePixelShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// インターフェース生成(参照カウント増加)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// 参照カウントを減らす
		d3d11Shader->Release();
		ps = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::CS:
	{
		ID3D11ComputeShader* d3d11Shader;
		CHECK_FAILED(device->CreateComputeShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// インターフェース生成(参照カウント増加)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// 参照カウントを減らす
		d3d11Shader->Release();
		cs = d3d11Shader;
	}
		break;
	}
}
