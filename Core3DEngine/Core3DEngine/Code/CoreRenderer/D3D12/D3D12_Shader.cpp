/*****************************************************************//**
 * \file   D3D12_Shader.h
 * \brief  DirectX12�V�F�[�_�[�N���X
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

using namespace core;
using namespace d3d12;

namespace {
	/// @brief �V�F�[�_�t�@�C���p�X
	const char* SHADER_FILE_PATH = "Source/Shader/";

	/// @brief �G���g���[�|�C���g�A�t�@�C�����ʎq
	const char* SHADER_TYPES[] = {
		"VS","GS","DS","HS","PS","CS",
	};
	/// @brief HLSL�o�[�W����
	const char* HLSL_VERS[] = {
		"vs_5_1",
		"gs_5_1",
		"ds_5_1",
		"hs_5_1",
		"ps_5_1",
		"cs_5_1",
	};

	constexpr D3D12_SHADER_VISIBILITY SHADER_VISIBILITYS[static_cast<size_t>(core::ShaderStage::CS)] = {
		D3D12_SHADER_VISIBILITY_VERTEX,
		D3D12_SHADER_VISIBILITY_HULL,
		D3D12_SHADER_VISIBILITY_DOMAIN,
		D3D12_SHADER_VISIBILITY_GEOMETRY,
		D3D12_SHADER_VISIBILITY_PIXEL,
	};
}

/// @brief  �R���X�g���N�^
/// @param device �f�o�C�X
/// @param desc �V�F�[�_���
D3D12Shader::D3D12Shader(D3D12Device* device, core::ShaderDesc desc, const core::ShaderID& id) :
	core::CoreShader(desc, id),
	m_pShaderBlob({nullptr,}),
	m_inputElementDesc()
{
	// ������
	for (auto& shader : m_pShaderBlob) {
		shader = nullptr;
	}

	// �R���p�C�������V�F�[�_�f�[�^
	auto& blobs = m_pShaderBlob;
	// �V�F�[�_���t���N�V����
	std::vector<ComPtr<ID3D12ShaderReflection>>	reflections(static_cast<size_t>(core::ShaderStage::MAX));
	// �V�F�[�_���ꎞ�i�[�p
	D3D12_SHADER_DESC							shaderDesc = {};


	// �V�F�[�_�X�e�[�W�������R���p�C��������
	for (auto stage = core::ShaderStage::VS; stage < core::ShaderStage::MAX; ++stage)
	{
		// �X�e�[�W���Ȃ��ꍇ�̓X�L�b�v
		if (!hasStaderStage(desc.m_stages, stage)) continue;

		ComPtr<ID3DBlob>& blob = blobs[static_cast<size_t>(stage)];
		ComPtr<ID3D12ShaderReflection>& reflection = reflections[static_cast<size_t>(stage)];

		// �p�X
		std::string filepath = SHADER_FILE_PATH + desc.m_name + "_" + 
			SHADER_TYPES[static_cast<size_t>(stage)] + ".hlsl";
		std::wstring wfilepath = std::wstring(filepath.begin(), filepath.end());
		// �G���[
		ID3DBlob* d3dError = nullptr;
		// �X�g���[��
		std::ifstream ifsShader(filepath, std::ios::in | std::ios::binary | std::ios::ate);
		if (ifsShader.good())
		{
			// �\�[�X�t�@�C������R���p�C��
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
			// �G���[���b�Z�[�W!!


			// �ǂݍ��ݐ���
			if (blob)
			{
				// �V�F�[�_���t���N�V�����擾
				void** ppBuffer = reinterpret_cast<void**>(reflection.GetAddressOf());
				CHECK_FAILED(D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(),
					IID_ID3D12ShaderReflection, ppBuffer));
			}

		}
		else
		{
			// �V�F�[�_�t�@�C���Ȃ�!!

		}
	}

	// ���_�V�F�[�_������ꍇ�̓C���v�b�g���C�A�E�g���쐬
	auto& vsReflection = reflections[static_cast<size_t>(core::ShaderStage::VS)];
	if (vsReflection)
	{
		auto& vsBlob = blobs[static_cast<size_t>(core::ShaderStage::VS)];
		vsReflection->GetDesc(&shaderDesc);
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayouts(shaderDesc.InputParameters);

		// ���̓��C�A�E�g����
		m_inputLayoutVariableList.resize(shaderDesc.InputParameters);
		for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
		{
			D3D12_SIGNATURE_PARAMETER_DESC signature;
			vsReflection->GetInputParameterDesc(i, &signature);

			// �C���v�b�g���C�A�E�g�v�f
			D3D12_INPUT_ELEMENT_DESC inputDesc = {};
			inputDesc.SemanticName = signature.SemanticName;
			inputDesc.SemanticIndex = signature.SemanticIndex;
			//inputDesc.Format = ��..
			inputDesc.InputSlot = 0;
			inputDesc.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
			inputDesc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
			inputDesc.InstanceDataStepRate = 0;

			// ���̓��C�A�E�g���
			m_inputLayoutVariableList[i].semanticName = inputDesc.SemanticName;
			inputDesc.SemanticName = m_inputLayoutVariableList[i].semanticName.c_str();
			m_inputLayoutVariableList[i].semanticIndex = inputDesc.SemanticIndex;
			if (i > 0)
			{
				m_inputLayoutVariableList[i].offset = m_inputLayoutVariableList[i - 1].arrayNum * 
					m_inputLayoutVariableList[i - 1].formatWidth +	m_inputLayoutVariableList[i - 1].offset;
			}

			// �r�b�g�}�X�N�Ńt�H�[�}�b�g�𕪂���
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

			// ���̓��C�A�E�g�쐬�p���i�[
			inputLayouts[i] = inputDesc;
		}

		// ���̓��C�A�E�g���i�[
		if (!inputLayouts.empty()){

			m_inputElementDesc = inputLayouts;
		}
	}

	// ���̓o�C���h�f�[�^�̍쐬
	D3D12_SHADER_BUFFER_DESC shaderBufferDesc = {};
	for (auto stage = core::ShaderStage::VS; stage < core::ShaderStage::MAX; ++stage)
	{
		const auto& stageIndex = static_cast<size_t>(stage);
		const auto& reflection = reflections[stageIndex];
		if (!reflection) continue;
		// �V�F�[�_���擾
		reflection->GetDesc(&shaderDesc);

		// �V�F�[�_�[���\�[�X�o�C���h���
		for (std::uint32_t i = 0; i < shaderDesc.BoundResources; ++i)
		{
			// �o�C���h���擾
			D3D12_SHADER_INPUT_BIND_DESC bindDesc;
			reflection->GetResourceBindingDesc(i, &bindDesc);

			BindType bindType = BindType::MAX;

			// �o�C���h�^�C�v�ŕ�����
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

			// �w��X���b�g�ȍ~�͐ÓI
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

		// ���t���N�V��������R���X�^���g�o�b�t�@�ǂݍ���
		std::uint32_t slotOffset = 0;
		m_cbufferLayouts[stageIndex].reserve(shaderDesc.ConstantBuffers);
		for (std::uint32_t cbIdx = 0; cbIdx < shaderDesc.ConstantBuffers; ++cbIdx)
		{
			auto* constantBuffer = reflection->GetConstantBufferByIndex(cbIdx);
			constantBuffer->GetDesc(&shaderBufferDesc);

			// ���ʂ̒萔�o�b�t�@�̓X�L�b�v
			std::string cbName(shaderBufferDesc.Name);
			auto type = static_cast<std::size_t>(BindType::CBV);
			auto itr = m_staticBindData[stageIndex][type].find(cbName);
			// �ÓI�f�[�^�Ȃ�X�L�b�v
			if (m_staticBindData[stageIndex][type].end() != itr)
			{
				++slotOffset;
				continue;
			}

			// ���C�A�E�g����
			CBufferLayout cbLayout(cbIdx - slotOffset, shaderBufferDesc.Name, shaderBufferDesc.Size);
			cbLayout.variables.resize(shaderBufferDesc.Variables);

			// CB�ϐ��̃��C�A�E�g�쐬
			D3D12_SHADER_VARIABLE_DESC varDesc;
			for (std::uint32_t v = 0; v < shaderBufferDesc.Variables; ++v)
			{
				// �ϐ����擾
				auto* variable = constantBuffer->GetVariableByIndex(v);
				variable->GetDesc(&varDesc);
				// �ϐ������
				cbLayout.variables[v].name = varDesc.Name;
				cbLayout.variables[v].size = varDesc.Size;
				cbLayout.variables[v].offset = varDesc.StartOffset;
				cbLayout.variables[v].stage = stageIndex;
				cbLayout.variables[v].slot = cbIdx - slotOffset;
				// �f�t�H���g�l������ꍇ
				if (varDesc.DefaultValue != nullptr)
				{
					std::unique_ptr<std::byte[]> defaultValue =
						std::make_unique<std::byte[]>(varDesc.Size);
					std::memcpy(defaultValue.get(), varDesc.DefaultValue, varDesc.Size);
					m_cbufferDefaults[varDesc.Name] = std::move(defaultValue);
				}
			}
			// �R���X�^���g�o�b�t�@���C�A�E�g�i�[
			m_cbufferLayouts[stageIndex].emplace(cbIdx - slotOffset, cbLayout);
		}
	}

	// ���[�g�V�O�l�`���[�̍쐬
	CreateRootSignature(device);

}


/// @brief ���[�g�V�O�l�`���[�̐���
void D3D12Shader::CreateRootSignature(D3D12Device* device)
{
	// �S�f�B�X�N���v�^�����W�E�p�����[�^
	std::vector<D3D12_DESCRIPTOR_RANGE>		aRanges;
	aRanges.reserve(100);
	std::vector<D3D12_ROOT_PARAMETER>			aParameters;
	std::vector<D3D12_STATIC_SAMPLER_DESC>		aSamplers;

	// ���I�o�C���h
	for (core::ShaderStage stage = core::ShaderStage::VS; stage < core::ShaderStage::CS; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);

		for (size_t type = 0; type < static_cast<size_t>(BindType::MAX); ++type)
		{
			// ���I
			int cnt = 0;
			for (auto& bindData : m_dynamicBindData[stageIndex][type])
			{
				// ���[�g�p�����[�^�C���f�b�N�X
				bindData.second.rootIndex = aParameters.size();

				// �o�C���h�^�C�v�Ńp�����[�^�쐬
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
	// �ÓI�o�C���h
	for (core::ShaderStage stage = core::ShaderStage::VS; stage < core::ShaderStage::CS; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);

		for (size_t type = 0; type < static_cast<size_t>(BindType::MAX); ++type)
		{
			// �ÓI
			for (auto& bindData : m_staticBindData[stageIndex][type])
			{
				// ���[�g�p�����[�^�C���f�b�N�X
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
							static_cast<size_t>(core::SamplerState::LINEAR_WRAP)]);
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

	// ���[�g�V�O�l�`���[�̐���
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
