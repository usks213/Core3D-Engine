/*****************************************************************//**
 * \file   D3D_ShaderCompiler.h
 * \brief  DirectX�V�F�[�_�[�R���p�C���[
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#include "D3D_ShaderCompiler.h"
#include "D3D_Defines.h"

#include <fstream>
#include <iostream>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Core::RHI;
using namespace Core::RHI::D3D;

// �R�s�[�p
#ifdef __d3d12_h__
#else __d3d11_h__
#endif // __d3d12.h_

/// @brief �G���g���[�|�C���g�A�t�@�C�����ʎq
const char* SHADER_TYPES[] = {
	"VS","GS","DS","HS","PS","CS",
};

#ifdef __d3d12_h__

/// @include D3D12�V�F�[�_�[
#include <d3d12shader.h>

/// @brief HLSL�o�[�W����
const char* HLSL_VERS[] = {
	"vs_5_1",
	"gs_5_1",
	"ds_5_1",
	"hs_5_1",
	"ps_5_1",
	"cs_5_1",
};
#else __d3d11_h__

/// @include D3D11�V�F�[�_�[
#include <d3d11shader.h>

/// @brief HLSL�o�[�W����
const char* HLSL_VERS[] = {
	"vs_5_0",
	"gs_5_0",
	"ds_5_0",
	"hs_5_0",
	"ps_5_0",
	"cs_5_0",
};
#endif // __d3d12.h_


/// @brief �V�F�[�_�[�t�@�C���̃R���p�C��
/// @param filepath �t�@�C���p�X
/// @param stage �V�F�[�_�[�X�e�[�W
/// @param pOut �V�F�[�_�[�o�C�i���̏o�͐�(out)
/// @return ���� TRUE / ���s FALSE
bool D3DShaderCompiler::CompileFromFile(std::string_view filepath, ShaderStage stage, ID3DBlob* pOut)
{
	// �p�X
	std::wstring wfilepath = std::wstring(filepath.begin(), filepath.end());
	// �G���[
	ID3DBlob* d3dError = nullptr;
	// �X�g���[��
	std::ifstream ifsShader(filepath.data(), std::ios::in | std::ios::binary | std::ios::ate);
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
			&pOut,
			&d3dError));

		// �G���[���b�Z�[�W!!
		if (!pOut)
		{
			return false;
		}
	}

	return true;
}

/// @brief �V�F�[�_�[���t���N�V�����擾
/// @param pBlob �V�F�[�_�[�o�C�i��(in)
/// @param pRefletor ���t���N�V�����i�[��(out)
/// @return ���� TRUE / ���s FALSE
bool D3DShaderCompiler::GetReflection(ID3DBlob* pBlob, void* pRefletor)
{
#ifdef __d3d12_h__
	const GUID gudi = IID_ID3D12ShaderReflection;
#else __d3d11_h__
	const GUID gudi = IID_ID3D11ShaderReflection;
#endif // __d3d12.h_
	// �V�F�[�_���t���N�V�����擾
	CHECK_FAILED(D3DReflect(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), gudi, &pRefletor));

	// ����
	if (pRefletor)
	{
		return true;
	}

	return false;
}


/// @brief �C���v�b�g���C�A�E�g�쐬
/// @param pReflection ���t���N�V�����f�[�^
/// @param elementList �G�������g���X�g
/// @param inputLayout �C���v�b�g���C�A�E�g(out)
/// @return ���� TRUE / ���s FALSE
bool D3DShaderCompiler::CreateInputLayout(void* pReflection,
#ifdef __d3d12_h__
	std::vector<D3D12_INPUT_ELEMENT_DESC>& elementList,
#else __d3d11_h__
	std::vector<D3D11_INPUT_ELEMENT_DESC>& elementList,
#endif // __d3d12.h_
	ShaderInputLayout& inputLayout)
{

	// DX11 or DX12�̃p�����[�^
#ifdef __d3d12_h__
	D3D12_SHADER_DESC shaderDesc = {};
	D3D12_SIGNATURE_PARAMETER_DESC signature = {};
	ID3D12ShaderReflection* pD3DRef = static_cast<ID3D12ShaderReflection*>(pReflection);
#else __d3d11_h__
	D3D11_SHADER_DESC shaderDesc = {};
	D3D11_SIGNATURE_PARAMETER_DESC signature = {};
	ID3D11ShaderReflection* pD3DRef = static_cast<ID3D11ShaderReflection*>(pReflection);
#endif // __d3d12.h_

	// �V�F�[�_�[���擾
	pD3DRef->GetDesc(&shaderDesc);

	// ���̓��C�A�E�g�̐�
	elementList.resize(shaderDesc.InputParameters);
	auto& inputLayoutVariableList = inputLayout.GetVariableList();
	inputLayoutVariableList.resize(shaderDesc.InputParameters);

	// ���̓��C�A�E�g����
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		// ���̓��C�A�E�g�̕ϐ��p�����[�^�擾
		pD3DRef->GetInputParameterDesc(i, &signature);

		// �C���v�b�g���C�A�E�g�v�f
#ifdef __d3d12_h__
		D3D12_INPUT_ELEMENT_DESC inputDesc = {};
		inputDesc.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
		inputDesc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
#else __d3d11_h__
		D3D11_INPUT_ELEMENT_DESC inputDesc = {};
		inputDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
#endif // __d3d12.h_

		inputDesc.SemanticName = signature.SemanticName;
		inputDesc.SemanticIndex = signature.SemanticIndex;
		//inputDesc.Format = ��..
		inputDesc.InputSlot = 0;
		inputDesc.InstanceDataStepRate = 0;

		// ���̓��C�A�E�g���
		inputLayoutVariableList[i].semanticName = inputDesc.SemanticName;
		inputDesc.SemanticName = inputLayoutVariableList[i].semanticName.c_str();
		inputLayoutVariableList[i].semanticIndex = inputDesc.SemanticIndex;
		if (i > 0)
		{
			inputLayoutVariableList[i].offset = inputLayoutVariableList[i - 1].arrayNum *
				inputLayoutVariableList[i - 1].formatWidth + inputLayoutVariableList[i - 1].offset;
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
				inputLayoutVariableList[i].formatWidth = sizeof(long);
				break;
			case D3D_MIN_PRECISION_FLOAT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16_FLOAT; break;
			case D3D_MIN_PRECISION_SINT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16_SINT; break;
			case D3D_MIN_PRECISION_UINT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16_UINT; break;
			case D3D_MIN_PRECISION_ANY_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16_TYPELESS; break;
			}
			inputLayoutVariableList[i].arrayNum = 1U;
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
				inputLayoutVariableList[i].formatWidth = sizeof(long);
				break;
			case D3D_MIN_PRECISION_FLOAT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16G16_FLOAT; break;
			case D3D_MIN_PRECISION_SINT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16G16_SINT; break;
			case D3D_MIN_PRECISION_UINT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16G16_UINT; break;
			case D3D_MIN_PRECISION_ANY_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16G16_TYPELESS; break;
			}
			inputLayoutVariableList[i].arrayNum = 2U;
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
				inputLayoutVariableList[i].formatWidth = sizeof(long);
				break;
			case D3D_MIN_PRECISION_FLOAT_16:
			case D3D_MIN_PRECISION_SINT_16:
			case D3D_MIN_PRECISION_UINT_16:
			case D3D_MIN_PRECISION_ANY_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_UNKNOWN; break;
			}
			inputLayoutVariableList[i].arrayNum = 3U;
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
				inputLayoutVariableList[i].formatWidth = sizeof(long);
				break;
			case D3D_MIN_PRECISION_FLOAT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; break;
			case D3D_MIN_PRECISION_SINT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16G16B16A16_SINT; break;
			case D3D_MIN_PRECISION_UINT_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16G16B16A16_UINT; break;
			case D3D_MIN_PRECISION_ANY_16:
				inputLayoutVariableList[i].formatWidth = sizeof(short);
				inputDesc.Format = DXGI_FORMAT_R16G16B16A16_TYPELESS; break;
			}
			inputLayoutVariableList[i].arrayNum = 4U;
		}

		// ���̓��C�A�E�g�쐬�p���i�[
		elementList[i] = inputDesc;
	}

	// ���̓��C�A�E�g���i�[
	if (!elementList.empty()) {

		return false;
	}

	return true;
}

/// @brief ���\�[�X���C�A�E�g�쐬
/// @param pReflection ���t���N�V�����f�[�^
/// @param resourceLayout ���\�[�X���C�A�E�g(out)
/// @return ���� TRUE / ���s FALSE
bool D3DShaderCompiler::CreateResourceLayout(void* pReflection, ShaderResourceLayout& resourceLayout)
{
	// DX11 or DX12�̃p�����[�^
#ifdef __d3d12_h__
	D3D12_SHADER_DESC shaderDesc = {};
	ID3D12ShaderReflection* pD3DRef = static_cast<ID3D12ShaderReflection*>(pReflection);
	// ���̓o�C���h�f�[�^�̍쐬
	D3D12_SHADER_BUFFER_DESC shaderGPUBufferDesc = {};
	// �o�C���h���擾
	D3D12_SHADER_INPUT_BIND_DESC bindDesc = {};
#else __d3d11_h__
	D3D11_SHADER_DESC shaderDesc = {};
	ID3D11ShaderReflection* pD3DRef = static_cast<ID3D11ShaderReflection*>(pReflection);
	// ���̓o�C���h�f�[�^�̍쐬
	D3D11_SHADER_BUFFER_DESC shaderGPUBufferDesc = {};
	// �o�C���h���擾
	D3D11_SHADER_INPUT_BIND_DESC bindDesc = {};
#endif // __d3d12.h_

	// �V�F�[�_���擾
	pD3DRef->GetDesc(&shaderDesc);

	// �V�F�[�_�[���\�[�X�o�C���h���
	for (std::uint32_t i = 0; i < shaderDesc.BoundResources; ++i)
	{
		// �o�C���h���擾
		pD3DRef->GetResourceBindingDesc(i, &bindDesc);
		// ���\�[�X�^�C�v
		ShaderResourceType resourceType = ShaderResourceType::MAX;

		// �o�C���h�^�C�v�ŕ�����
		switch (bindDesc.Type)
		{
			// b
		case D3D_SIT_CBUFFER:
			resourceType = ShaderResourceType::CBV;
			break;
			// u
		case D3D_SIT_UAV_RWTYPED:
		case D3D_SIT_UAV_RWSTRUCTURED:
		case D3D_SIT_UAV_RWBYTEADDRESS:
		case D3D_SIT_UAV_APPEND_STRUCTURED:
		case D3D_SIT_UAV_CONSUME_STRUCTURED:
		case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
			resourceType = ShaderResourceType::UAV;
			break;
			// t
		case D3D_SIT_TBUFFER:
		case D3D_SIT_STRUCTURED:
		case D3D_SIT_BYTEADDRESS:
			resourceType = ShaderResourceType::SRV;
			break;
			// t
		case D3D_SIT_TEXTURE:
			resourceType = ShaderResourceType::TEXTURE;
			break;
			// s
		case D3D_SIT_SAMPLER:
			resourceType = ShaderResourceType::SAMPLER;
			break;
		default:
			break;
		}

		if (resourceType == ShaderResourceType::MAX) continue;
		auto type = static_cast<std::size_t>(resourceType);

		// ���C�A�E�g�f�[�^
		ShaderResourceLayout::ShaderResoureData data = {};
		data.type = resourceType;
		data.slot = bindDesc.BindPoint;
#ifdef __d3d12_h__
		data.space = bindDesc.Space;
#endif // __d3d12.h__

		// �w��X���b�g�ȍ~�͐ÓI
		if (bindDesc.BindPoint < GLOBAL_BIND_SLOT_BORDER)
		{
			resourceLayout.m_localResource[type][bindDesc.Name] = data;
		}
		else
		{
			resourceLayout.m_globalResource[type][bindDesc.Name] = data;
		}
	}

	return true;
}

/// @brief CBuffer���C�A�E�g�쐬
/// @param pReflection ���t���N�V�����f�[�^
/// @param resourceLayout ���\�[�X���C�A�E�g(in)
/// @param cbufferLayouts CBuffer���C�A�E�g���X�g(out)
/// @return ���� TRUE / ���s FALSE
bool D3DShaderCompiler::CreateCBufferLayouts(void* pReflection, ShaderResourceLayout& resourceLayout,
	std::vector<ShaderCBufferLayout>& cbufferLayouts)
{
#ifdef __d3d12_h__
	D3D12_SHADER_DESC shaderDesc = {};
	ID3D12ShaderReflection* pD3DRef = static_cast<ID3D12ShaderReflection*>(pReflection);
	// ���̓o�C���h�f�[�^�̍쐬
	D3D12_SHADER_BUFFER_DESC shaderGPUBufferDesc = {};
	// �o�C���h���擾
	D3D12_SHADER_INPUT_BIND_DESC bindDesc = {};
	// �ϐ����
	D3D12_SHADER_VARIABLE_DESC varDesc = {};
#else __d3d11_h__
	D3D11_SHADER_DESC shaderDesc = {};
	ID3D11ShaderReflection* pD3DRef = static_cast<ID3D11ShaderReflection*>(pReflection);
	// ���̓o�C���h�f�[�^�̍쐬
	D3D11_SHADER_BUFFER_DESC shaderGPUBufferDesc = {};
	// �o�C���h���擾
	D3D11_SHADER_INPUT_BIND_DESC bindDesc = {};
	// �ϐ����
	D3D11_SHADER_VARIABLE_DESC varDesc = {};
#endif // __d3d12.h_

	// �V�F�[�_���擾
	pD3DRef->GetDesc(&shaderDesc);

	// ���t���N�V��������R���X�^���g�o�b�t�@�ǂݍ���
	std::uint32_t slotOffset = 0;
	cbufferLayouts.reserve(shaderDesc.ConstantBuffers);
	for (std::uint32_t cbIdx = 0; cbIdx < shaderDesc.ConstantBuffers; ++cbIdx)
	{
		// CBuffer�f�[�^�擾
		auto* constantBuffer = pD3DRef->GetConstantBufferByIndex(cbIdx);
		constantBuffer->GetDesc(&shaderGPUBufferDesc);

		// ���ʂ̒萔�o�b�t�@�̓X�L�b�v
		std::string cbName(shaderGPUBufferDesc.Name);
		auto type = static_cast<std::size_t>(ShaderResourceType::CBV);
		auto itr = resourceLayout.m_globalResource[type].find(cbName);
		// �ÓI�f�[�^�Ȃ�X�L�b�v
		if (resourceLayout.m_globalResource[type].end() != itr)
		{
			++slotOffset;
			continue;
		}

		// ���C�A�E�g����
		ShaderCBufferLayout cbLayout(cbIdx - slotOffset, 
			shaderGPUBufferDesc.Name, shaderGPUBufferDesc.Size);

		// CB�ϐ��̃��C�A�E�g�쐬
		for (std::uint32_t v = 0; v < shaderGPUBufferDesc.Variables; ++v)
		{
			// �ϐ����擾
			auto* variable = constantBuffer->GetVariableByIndex(v);
			variable->GetDesc(&varDesc);
			std::string name = varDesc.Name;
			// �ϐ������
			cbLayout.m_variables[name].size = varDesc.Size;
			cbLayout.m_variables[name].offset = varDesc.StartOffset;
			cbLayout.m_variables[name].slot = cbLayout.m_slot;
			// �f�t�H���g�l������ꍇ
			if (varDesc.DefaultValue != nullptr)
			{
				cbLayout.m_variables[name].defaultVal.resize(varDesc.Size);
				std::memcpy(cbLayout.m_variables[name].defaultVal.data(), 
					varDesc.DefaultValue, varDesc.Size);
			}
		}

		// �R���X�^���g�o�b�t�@���C�A�E�g�i�[
		cbufferLayouts.push_back(std::move(cbLayout));
	}

	return true;
}
