/*****************************************************************//**
 * \file   D3D12_Shader.h
 * \brief  DirectX12シェーダークラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/11
 *********************************************************************/

#include "D3D12_Shader.h"
#include <d3dcompiler.h>
#include <fstream>
#include <iostream>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Core;
using namespace Core::D3D12;

namespace {
	/// @brief シェーダファイルパス
	const char* SHADER_FILE_PATH = "Assets/Shader/";

	/// @brief エントリーポイント、ファイル識別子
	const char* SHADER_TYPES[] = {
		"VS","GS","DS","HS","PS","CS",
	};
	/// @brief HLSLバージョン
	const char* HLSL_VERS[] = {
		"vs_5_1",
		"gs_5_1",
		"ds_5_1",
		"hs_5_1",
		"ps_5_1",
		"cs_5_1",
	};

	constexpr D3D12_SHADER_VISIBILITY SHADER_VISIBILITYS[static_cast<size_t>(Core::ShaderStage::CS)] = {
		D3D12_SHADER_VISIBILITY_VERTEX,
		D3D12_SHADER_VISIBILITY_HULL,
		D3D12_SHADER_VISIBILITY_DOMAIN,
		D3D12_SHADER_VISIBILITY_GEOMETRY,
		D3D12_SHADER_VISIBILITY_PIXEL,
	};
}

/// @brief  コンストラクタ
/// @param device デバイス
/// @param desc シェーダ情報
D3D12Shader::D3D12Shader(D3D12Device* device, Core::ShaderDesc desc, const Core::ShaderID& id) :
	Core::CoreShader(desc, id),
	m_pShaderBlob({nullptr,}),
	m_inputElementDesc()
{
	// 初期化
	for (auto& shader : m_pShaderBlob) {
		shader = nullptr;
	}

	// コンパイルしたシェーダデータ
	auto& blobs = m_pShaderBlob;
	// シェーダリフレクション
	std::vector<ComPtr<ID3D12ShaderReflection>>	reflections(static_cast<size_t>(Core::ShaderStage::MAX));
	// シェーダ情報一時格納用
	D3D12_SHADER_DESC							shaderDesc = {};


	// シェーダステージ数だけコンパイルを試す
	for (auto stage = Core::ShaderStage::VS; stage < Core::ShaderStage::MAX; ++stage)
	{
		// ステージがない場合はスキップ
		if (!hasStaderStage(desc.m_stages, stage)) continue;

		ComPtr<ID3DBlob>& blob = blobs[static_cast<size_t>(stage)];
		ComPtr<ID3D12ShaderReflection>& reflection = reflections[static_cast<size_t>(stage)];

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
				D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, //D3DCOMPILE_ENABLE_STRICTNESS,
				0,
				blob.GetAddressOf(),
				&d3dError));
			// エラーメッセージ!!


			// 読み込み成功
			if (blob)
			{
				// シェーダリフレクション取得
				void** ppBuffer = reinterpret_cast<void**>(reflection.GetAddressOf());
				CHECK_FAILED(D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(),
					IID_ID3D12ShaderReflection, ppBuffer));
			}

		}
		else
		{
			// シェーダファイルなし!!

		}
	}

	// 頂点シェーダがある場合はインプットレイアウトを作成
	auto& vsReflection = reflections[static_cast<size_t>(Core::ShaderStage::VS)];
	if (vsReflection)
	{
		auto& vsBlob = blobs[static_cast<size_t>(Core::ShaderStage::VS)];
		vsReflection->GetDesc(&shaderDesc);
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayouts(shaderDesc.InputParameters);

		// 入力レイアウト数分
		m_inputLayoutVariableList.resize(shaderDesc.InputParameters);
		for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
		{
			D3D12_SIGNATURE_PARAMETER_DESC signature;
			vsReflection->GetInputParameterDesc(i, &signature);

			// インプットレイアウト要素
			D3D12_INPUT_ELEMENT_DESC inputDesc = {};
			inputDesc.SemanticName = signature.SemanticName;
			inputDesc.SemanticIndex = signature.SemanticIndex;
			//inputDesc.Format = 後..
			inputDesc.InputSlot = 0;
			inputDesc.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
			inputDesc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			inputDesc.InstanceDataStepRate = 0;

			// 入力レイアウト情報
			m_inputLayoutVariableList[i].semanticName = inputDesc.SemanticName;
			inputDesc.SemanticName = m_inputLayoutVariableList[i].semanticName.c_str();
			m_inputLayoutVariableList[i].semanticIndex = inputDesc.SemanticIndex;
			if (i > 0)
			{
				m_inputLayoutVariableList[i].offset = m_inputLayoutVariableList[i - 1].arrayNum * 
					m_inputLayoutVariableList[i - 1].formatWidth +	m_inputLayoutVariableList[i - 1].offset;
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
				case D3D_MIN_PRECISION_SINT_16 :
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

		// 入力レイアウト情報格納
		if (!inputLayouts.empty()){

			m_inputElementDesc = inputLayouts;
		}
	}

	// 入力バインドデータの作成
	D3D12_SHADER_BUFFER_DESC shaderGPUBufferDesc = {};
	for (auto stage = Core::ShaderStage::VS; stage < Core::ShaderStage::MAX; ++stage)
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
			D3D12_SHADER_INPUT_BIND_DESC bindDesc;
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
				data.space = bindDesc.Space;
				data.type = bindType;
				m_dynamicBindData[stageIndex][type][bindDesc.Name] = data;
			}
			else
			{
				CoreShader::ShaderBindData data;
				data.stage = stage;
				data.name = bindDesc.Name;
				data.slot = bindDesc.BindPoint;
				data.space = bindDesc.Space;
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
			D3D12_SHADER_VARIABLE_DESC varDesc;
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

	// ルートシグネチャーの作成
	CreateRootSignature(device);

}


/// @brief ルートシグネチャーの生成
void D3D12Shader::CreateRootSignature(D3D12Device* device)
{
	// 全ディスクリプタレンジ・パラメータ
	std::vector<D3D12_DESCRIPTOR_RANGE>		aRanges;
	aRanges.reserve(100);
	std::vector<D3D12_ROOT_PARAMETER>			aParameters;
	std::vector<D3D12_STATIC_SAMPLER_DESC>		aSamplers;

	// 動的バインド
	for (Core::ShaderStage stage = Core::ShaderStage::VS; stage < Core::ShaderStage::CS; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);

		for (size_t type = 0; type < static_cast<size_t>(BindType::MAX); ++type)
		{
			// 動的
			int cnt = 0;
			for (auto& bindData : m_dynamicBindData[stageIndex][type])
			{
				// ルートパラメータインデックス
				bindData.second.rootIndex = aParameters.size();

				// バインドタイプでパラメータ作成
				switch (type)
				{
					// b
					case static_cast<size_t>(BindType::CBV) :
					{
						if (cnt++ > 0) continue;
						D3D12_DESCRIPTOR_RANGE range = {};
						range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
						range.NumDescriptors = m_dynamicBindData[stageIndex][type].size();
						range.BaseShaderRegister = 0;
						range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
						aRanges.push_back(range);

						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
						param.DescriptorTable.pDescriptorRanges = &aRanges.back();
						param.DescriptorTable.NumDescriptorRanges = 1;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);
						break;
					}
					// t
					case static_cast<size_t>(BindType::TEXTURE) :
					{
						D3D12_DESCRIPTOR_RANGE range = {};
						range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
						range.NumDescriptors = 1;
						range.BaseShaderRegister = bindData.second.slot;
						range.RegisterSpace = bindData.second.space;
						range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
						aRanges.push_back(range);

						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
						param.DescriptorTable.pDescriptorRanges = &aRanges.back();
						param.DescriptorTable.NumDescriptorRanges = 1;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);
						break;
					}
					// s
					case static_cast<size_t>(BindType::SAMPLER) :
					{
						D3D12_DESCRIPTOR_RANGE range = {};
						range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
						range.NumDescriptors = 1;
						range.BaseShaderRegister = bindData.second.slot;
						range.RegisterSpace = bindData.second.space;
						range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
						aRanges.push_back(range);

						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
						param.DescriptorTable.pDescriptorRanges = &aRanges.back();
						param.DescriptorTable.NumDescriptorRanges = 1;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);

						break;
					}
					// t
					case static_cast<size_t>(BindType::SRV) :
					{
						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
						param.Descriptor.ShaderRegister = bindData.second.slot;
						param.Descriptor.RegisterSpace = bindData.second.space;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);
						break;
					}
					// u
					case static_cast<size_t>(BindType::UAV) :
					{
						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV;
						param.Descriptor.ShaderRegister = bindData.second.slot;
						param.Descriptor.RegisterSpace = bindData.second.space;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);
						break;
					}
				}
			}
		}
	}
	// 静的バインド
	for (Core::ShaderStage stage = Core::ShaderStage::VS; stage < Core::ShaderStage::CS; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);

		for (size_t type = 0; type < static_cast<size_t>(BindType::MAX); ++type)
		{
			// 静的
			for (auto& bindData : m_staticBindData[stageIndex][type])
			{
				// ルートパラメータインデックス
				bindData.second.rootIndex = aParameters.size();

				switch (type)
				{
					// b
					case static_cast<size_t>(BindType::CBV) :
					{
						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
						param.Descriptor.ShaderRegister = bindData.second.slot;
						param.Descriptor.RegisterSpace = bindData.second.space;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);
						break;
					}
					// t
					case static_cast<size_t>(BindType::TEXTURE) :
					{
						D3D12_DESCRIPTOR_RANGE range = {};
						range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
						range.NumDescriptors = 1;
						range.BaseShaderRegister = bindData.second.slot;
						range.RegisterSpace = bindData.second.space;
						range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
						aRanges.push_back(range);

						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
						param.DescriptorTable.pDescriptorRanges = &aRanges.back();
						param.DescriptorTable.NumDescriptorRanges = 1;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);
						break;
					}
					// s
					case static_cast<size_t>(BindType::SAMPLER) :
					{
						aSamplers.push_back(device->m_staticSamplers[
							static_cast<size_t>(Core::SamplerState::LINEAR_WRAP)]);
						break;
					}
					// t
					case static_cast<size_t>(BindType::SRV) :
					{
						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
						param.Descriptor.ShaderRegister = bindData.second.slot;
						param.Descriptor.RegisterSpace = bindData.second.space;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);
						break;
					}
					// u
					case static_cast<size_t>(BindType::UAV) :
					{
						D3D12_ROOT_PARAMETER param = {};
						param.ParameterType = D3D12_ROOT_PARAMETER_TYPE_UAV;
						param.Descriptor.ShaderRegister = bindData.second.slot;
						param.Descriptor.RegisterSpace = bindData.second.space;
						param.ShaderVisibility = SHADER_VISIBILITYS[stageIndex];
						aParameters.push_back(param);
						break;
					}
				}
			}
		}
	}

	// ルートシグネチャーの生成
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.NumParameters = aParameters.size();
	rootSignatureDesc.pParameters = aParameters.data();
	rootSignatureDesc.NumStaticSamplers = aSamplers.size();
	rootSignatureDesc.pStaticSamplers = aSamplers.data();
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ID3DBlob* rootSigBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob));
	std::string errstr;
	if (rootSigBlob)
	{
		CHECK_FAILED(device->m_pD3DDevice->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
			IID_PPV_ARGS(m_pRootSignature.ReleaseAndGetAddressOf())));
		rootSigBlob->Release();
	}
	else
	{
		errstr.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), errstr.begin());
		errstr += "\n";
		OutputDebugStringA(errstr.c_str());
		errorBlob->Release();
		throw std::exception(errstr.c_str());
	}
}
