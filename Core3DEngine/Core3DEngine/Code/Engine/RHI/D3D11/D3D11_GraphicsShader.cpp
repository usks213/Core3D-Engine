/*****************************************************************//**
 * \file   D3D11_GraphicsShader.h
 * \brief  DirectX11グラフィックスシェーダー
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#include "D3D11_GraphicsShader.h"
#include "D3D11_CommonState.h"

#include <d3dcompiler.h>
#include <fstream>
#include <iostream>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Core::RHI::D3D11;

namespace {
	/// @brief シェーダファイルパス
	const char* SHADER_FILE_PATH = "Assets/Shader/";

	/// @brief エントリーポイント、ファイル識別子
	const char* SHADER_TYPES[] = {
		"VS","GS","DS","HS","PS","CS",
	};
	/// @brief HLSLバージョン
	const char* HLSL_VERS[] = {
		"vs_5_0",
		"gs_5_0",
		"ds_5_0",
		"hs_5_0",
		"ps_5_0",
		"cs_5_0",
	};
}

/// @brief  コンストラクタ
/// @param device デバイス
/// @param desc シェーダ情報
D3D11GraphicsShader::D3D11GraphicsShader(ID3D11Device1* device, const GraphicsShaderDesc& desc) :
	GraphicsShader(desc),
	m_comGraphicsShaders(static_cast<size_t>(GraphicsShaderStage::MAX)),
	m_inputLayout(),
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
		std::wstring wfilepath = std::wstring(filepath.begin(), filepath.end());
		// エラー
		ID3DBlob* d3dError = nullptr;
		// ストリーム
		std::ifstream ifsShader(filepath, std::ios::in | std::ios::binary | std::ios::ate);
		if (ifsShader.good())
		{
			// ソースファイルからコンパイル
			CHECK_FAILED(D3DCompileFromFile(
				wfilepath.c_str(),
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				SHADER_TYPES[static_cast<size_t>(stage)],
				HLSL_VERS[static_cast<size_t>(stage)],
				D3DCOMPILE_ENABLE_STRICTNESS,
				0,
				blob.GetAddressOf(),
				&d3dError));
			// エラーメッセージ!!


			// 読み込み成功
			if (blob)
			{
				// シェーダオブジェクト生成
				CreateShaderObjct(device, stage, blob);

				// シェーダリフレクション取得
				void** ppBuffer = reinterpret_cast<void**>(reflection.GetAddressOf());
				CHECK_FAILED(D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(),
					IID_ID3D11ShaderReflection, ppBuffer));
			}

		}
		else
		{
			// シェーダファイルなし!!

		}
	}

	// 頂点シェーダがある場合はインプットレイアウトを作成
	auto& vsReflection = reflections[static_cast<size_t>(GraphicsShaderStage::VS)];
	if (vsReflection)
	{
		auto& vsBlob = blobs[static_cast<size_t>(GraphicsShaderStage::VS)];
		vsReflection->GetDesc(&shaderDesc);
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts(shaderDesc.InputParameters);

		// 入力レイアウト数分
		m_inputLayoutVariableList.resize(shaderDesc.InputParameters);
		for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
		{
			D3D11_SIGNATURE_PARAMETER_DESC signature;
			vsReflection->GetInputParameterDesc(i, &signature);

			// インプットレイアウト要素
			D3D11_INPUT_ELEMENT_DESC inputDesc;
			inputDesc.SemanticName = signature.SemanticName;
			inputDesc.SemanticIndex = signature.SemanticIndex;
			//inputDesc.Format = 後..
			inputDesc.InputSlot = 0;
			inputDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			inputDesc.InstanceDataStepRate = 0;

			// 入力レイアウト情報
			m_inputLayoutVariableList[i].semanticName = inputDesc.SemanticName;
			inputDesc.SemanticName = m_inputLayoutVariableList[i].semanticName.c_str();
			m_inputLayoutVariableList[i].semanticIndex = inputDesc.SemanticIndex;
			if (i > 0)
			{
				m_inputLayoutVariableList[i].offset = m_inputLayoutVariableList[i - 1].arrayNum *
					m_inputLayoutVariableList[i - 1].formatWidth + m_inputLayoutVariableList[i - 1].offset;
			}

			// ビットマスクでフォーマットを分ける
			if (signature.Mask == 0x01)
			{
				switch (signature.MinPrecision)
				{
				case D3D_MIN_PRECISION_DEFAULT:
					switch (signature.ComponentType)
					{
					case D3D_REGISTER_COMPONENT_UINT32: inputDesc.Format = DXGI_FORMAT_R32_UINT;  break;
					case D3D_REGISTER_COMPONENT_SINT32: inputDesc.Format = DXGI_FORMAT_R32_SINT;  break;
					case D3D_REGISTER_COMPONENT_FLOAT32: inputDesc.Format = DXGI_FORMAT_R32_FLOAT; break;
					}
					m_inputLayoutVariableList[i].formatWidth = sizeof(long);
					break;
				case D3D_MIN_PRECISION_FLOAT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16_FLOAT; break;
				case D3D_MIN_PRECISION_SINT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16_SINT; break;
				case D3D_MIN_PRECISION_UINT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16_UINT; break;
				case D3D_MIN_PRECISION_ANY_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16_TYPELESS; break;
				}
				m_inputLayoutVariableList[i].arrayNum = 1U;
			}
			else if (signature.Mask <= 0x03)
			{
				switch (signature.MinPrecision)
				{
				case D3D_MIN_PRECISION_DEFAULT:
					switch (signature.ComponentType)
					{
					case D3D_REGISTER_COMPONENT_UINT32: inputDesc.Format = DXGI_FORMAT_R32G32_UINT;  break;
					case D3D_REGISTER_COMPONENT_SINT32: inputDesc.Format = DXGI_FORMAT_R32G32_SINT;  break;
					case D3D_REGISTER_COMPONENT_FLOAT32: inputDesc.Format = DXGI_FORMAT_R32G32_FLOAT; break;
					}
					m_inputLayoutVariableList[i].formatWidth = sizeof(long);
					break;
				case D3D_MIN_PRECISION_FLOAT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16G16_FLOAT; break;
				case D3D_MIN_PRECISION_SINT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16G16_SINT; break;
				case D3D_MIN_PRECISION_UINT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16G16_UINT; break;
				case D3D_MIN_PRECISION_ANY_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16G16_TYPELESS; break;
				}
				m_inputLayoutVariableList[i].arrayNum = 2U;
			}
			else if (signature.Mask <= 0x07)
			{
				switch (signature.MinPrecision)
				{
				case D3D_MIN_PRECISION_DEFAULT:
					switch (signature.ComponentType)
					{
					case D3D_REGISTER_COMPONENT_UINT32: inputDesc.Format = DXGI_FORMAT_R32G32B32_UINT;  break;
					case D3D_REGISTER_COMPONENT_SINT32: inputDesc.Format = DXGI_FORMAT_R32G32B32_SINT;  break;
					case D3D_REGISTER_COMPONENT_FLOAT32: inputDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; break;
					}
					m_inputLayoutVariableList[i].formatWidth = sizeof(long);
					break;
				case D3D_MIN_PRECISION_FLOAT_16:
				case D3D_MIN_PRECISION_SINT_16:
				case D3D_MIN_PRECISION_UINT_16:
				case D3D_MIN_PRECISION_ANY_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_UNKNOWN; break;
				}
				m_inputLayoutVariableList[i].arrayNum = 3U;
			}
			else if (signature.Mask <= 0x0F)
			{
				switch (signature.MinPrecision)
				{
				case D3D_MIN_PRECISION_DEFAULT:
					switch (signature.ComponentType)
					{
					case D3D_REGISTER_COMPONENT_UINT32: inputDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;  break;
					case D3D_REGISTER_COMPONENT_SINT32: inputDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;  break;
					case D3D_REGISTER_COMPONENT_FLOAT32: inputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
					}
					m_inputLayoutVariableList[i].formatWidth = sizeof(long);
					break;
				case D3D_MIN_PRECISION_FLOAT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; break;
				case D3D_MIN_PRECISION_SINT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16G16B16A16_SINT; break;
				case D3D_MIN_PRECISION_UINT_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16G16B16A16_UINT; break;
				case D3D_MIN_PRECISION_ANY_16:
					m_inputLayoutVariableList[i].formatWidth = sizeof(short);
					inputDesc.Format = DXGI_FORMAT_R16G16B16A16_TYPELESS; break;
				}
				m_inputLayoutVariableList[i].arrayNum = 4U;
			}

			// 入力レイアウト作成用情報格納
			inputLayouts[i] = inputDesc;
		}

		// 入力レイアウト情報作成
		if (!inputLayouts.empty()){
			CHECK_FAILED(device->CreateInputLayout(
				inputLayouts.data(),
				shaderDesc.InputParameters,
				vsBlob->GetBufferPointer(),
				vsBlob->GetBufferSize(),
				m_inputLayout.GetAddressOf()));
		}
	}

	// 入力バインドデータの作成
	D3D11_SHADER_BUFFER_DESC shaderGPUBufferDesc = {};
	for (auto stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		const auto& stageIndex = static_cast<size_t>(stage);
		const auto& reflection = reflections[stageIndex];
		if (!reflection) continue;
		// シェーダ情報取得
		reflection->GetDesc(&shaderDesc);

		// シェーダーリソースバインド情報
		for (std::uint32_t i = 0; i < shaderDesc.BoundResources; ++i)
		{
			// バインド情報取得
			D3D11_SHADER_INPUT_BIND_DESC bindDesc;
			reflection->GetResourceBindingDesc(i, &bindDesc);

			BindType bindType = BindType::MAX;

			// バインドタイプで分ける
			switch (bindDesc.Type)
			{
			// b
			case D3D_SIT_CBUFFER:
				bindType = BindType::CBV;
				break;
			// u
			case D3D_SIT_UAV_RWTYPED:
			case D3D_SIT_UAV_RWSTRUCTURED:
			case D3D_SIT_UAV_RWBYTEADDRESS:
			case D3D_SIT_UAV_APPEND_STRUCTURED:
			case D3D_SIT_UAV_CONSUME_STRUCTURED:
			case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
				bindType = BindType::UAV;
				break;
			// t
			case D3D_SIT_TBUFFER:
			case D3D_SIT_STRUCTURED:
			case D3D_SIT_BYTEADDRESS:
				bindType = BindType::SRV;
				break;
			// t
			case D3D_SIT_TEXTURE:
				bindType = BindType::TEXTURE;
				break;
			// s
			case D3D_SIT_SAMPLER:
				bindType = BindType::SAMPLER;
				break;
			default:
				break;
			}

			if (bindType == BindType::MAX) continue;
			auto type = static_cast<std::size_t>(bindType);

			// 指定スロット以降は静的
			if (bindDesc.BindPoint < STATIC_BIND_SLOT_BORDER)
			{
				CoreShader::ShaderBindData data;
				data.stage = stage;
				data.name = bindDesc.Name;
				data.slot = bindDesc.BindPoint;
				data.space = 0;
				data.type = bindType;
				m_dynamicBindData[stageIndex][type][bindDesc.Name] = data;
			}
			else
			{
				CoreShader::ShaderBindData data;
				data.stage = stage;
				data.name = bindDesc.Name;
				data.slot = bindDesc.BindPoint;
				data.space = 0;
				data.type = bindType;
				m_staticBindData[stageIndex][type][bindDesc.Name] = data;
			}
		}

		// リフレクションからコンスタントバッファ読み込み
		std::uint32_t slotOffset = 0;
		m_cbufferLayouts[stageIndex].reserve(shaderDesc.ConstantBuffers);
		for (std::uint32_t cbIdx = 0; cbIdx < shaderDesc.ConstantBuffers; ++cbIdx)
		{
			auto* constantBuffer = reflection->GetConstantBufferByIndex(cbIdx);
			constantBuffer->GetDesc(&shaderGPUBufferDesc);

			// 共通の定数バッファはスキップ
			std::string cbName(shaderGPUBufferDesc.Name);
			auto type = static_cast<std::size_t>(BindType::CBV);
			auto itr = m_staticBindData[stageIndex][type].find(cbName);
			// 静的データならスキップ
			if (m_staticBindData[stageIndex][type].end() != itr)
			{
				++slotOffset;
				continue;
			}

			// レイアウト生成
			CBufferLayout cbLayout(cbIdx - slotOffset, shaderGPUBufferDesc.Name, shaderGPUBufferDesc.Size);
			cbLayout.variables.resize(shaderGPUBufferDesc.Variables);

			// CB変数のレイアウト作成
			D3D11_SHADER_VARIABLE_DESC varDesc;
			for (std::uint32_t v = 0; v < shaderGPUBufferDesc.Variables; ++v)
			{
				// 変数情報取得
				auto* variable = constantBuffer->GetVariableByIndex(v);
				variable->GetDesc(&varDesc);
				// 変数情報代入
				cbLayout.variables[v].name = varDesc.Name;
				cbLayout.variables[v].size = varDesc.Size;
				cbLayout.variables[v].offset = varDesc.StartOffset;
				cbLayout.variables[v].stage = stageIndex;
				cbLayout.variables[v].slot = cbIdx - slotOffset;
				// デフォルト値がある場合
				if (varDesc.DefaultValue != nullptr)
				{
					std::unique_ptr<std::byte[]> defaultValue =
						std::make_unique<std::byte[]>(varDesc.Size);
					std::memcpy(defaultValue.get(), varDesc.DefaultValue, varDesc.Size);
					m_cbufferDefaults[varDesc.Name] = std::move(defaultValue);
				}
			}
			// コンスタントバッファレイアウト格納
			m_cbufferLayouts[stageIndex].emplace(cbIdx - slotOffset, cbLayout);
		}
	}
}

/// @brief シェーダオブジェクト生成
/// @param device デバイス
/// @param stage シェーダステージ
/// @param blob コンパイルデータ
void D3D11Shader::CreateShaderObjct(ID3D11Device1* device, const GraphicsShaderStage& stage, ComPtr<ID3DBlob>& blob)
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
