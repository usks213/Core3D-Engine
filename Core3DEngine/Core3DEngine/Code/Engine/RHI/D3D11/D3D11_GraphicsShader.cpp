/*****************************************************************//**
 * \file   D3D11_GraphicsShader.h
 * \brief  DirectX11�O���t�B�b�N�X�V�F�[�_�[
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
	/// @brief �V�F�[�_�t�@�C���p�X
	const char* SHADER_FILE_PATH = "Assets/Shader/";

	/// @brief �G���g���[�|�C���g�A�t�@�C�����ʎq
	const char* SHADER_TYPES[] = {
		"VS","GS","DS","HS","PS","CS",
	};
}

/// @brief  �R���X�g���N�^
/// @param device �f�o�C�X
/// @param desc �V�F�[�_���
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
	// ������
	for (auto* shader : shaders) {
		shader = nullptr;
	}

	// �R���p�C�������V�F�[�_�f�[�^
	std::vector<ComPtr<ID3DBlob>>				blobs(static_cast<size_t>(GraphicsShaderStage::MAX));
	// �V�F�[�_���t���N�V����
	std::vector<ComPtr<ID3D11ShaderReflection>>	reflections(static_cast<size_t>(GraphicsShaderStage::MAX));
	// �V�F�[�_���ꎞ�i�[�p
	D3D11_SHADER_DESC							shaderDesc = {};


	// �V�F�[�_�X�e�[�W�������R���p�C��������
	for (auto stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		// �X�e�[�W���Ȃ��ꍇ�̓X�L�b�v
		if (!hasStaderStage(desc.m_stages, stage)) continue;

		ComPtr<ID3DBlob>& blob = blobs[static_cast<size_t>(stage)];
		ComPtr<ID3D11ShaderReflection>& reflection = reflections[static_cast<size_t>(stage)];

		// �p�X
		std::string filepath = SHADER_FILE_PATH + desc.m_name + "_" +
			SHADER_TYPES[static_cast<size_t>(stage)] + ".hlsl";
		// �V�F�[�_�[�R���p�C��
		if (D3DShaderCompiler::CompileFromFile(filepath, (ShaderStage)stage, blob.Get()))
		{

		}
		else
		{
			// ���s
		}
	}

	// ���_�V�F�[�_������ꍇ�̓C���v�b�g���C�A�E�g���쐬
	auto& vsReflection = reflections[static_cast<size_t>(GraphicsShaderStage::VS)];
	if (vsReflection)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
		auto& vsBlob = blobs[static_cast<size_t>(GraphicsShaderStage::VS)];

		// �C���v�b�g���C�A�E�g�̍쐬
		if (D3DShaderCompiler::CreateInputLayout(vsReflection.Get(), inputLayouts, m_inputLayout))
		{
			// ���̓��C�A�E�g���쐬
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

	// ���̓o�C���h�f�[�^�̍쐬
	D3D11_SHADER_BUFFER_DESC shaderGPUBufferDesc = {};
	for (auto stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		const auto& stageIndex = static_cast<size_t>(stage);
		const auto& reflection = reflections[stageIndex];
		if (!reflection) continue;
		
		// ���\�[�X���C�A�E�g�̍쐬
		if (D3DShaderCompiler::CreateResourceLayout(reflection.Get(), m_resourceLayout[stageIndex]))
		{
			// ����
		}
		else
		{
			// ���s
			continue;
		}

		// ���t���N�V��������R���X�^���g�o�b�t�@�ǂݍ���
		if (D3DShaderCompiler::CreateCBufferLayouts(reflection.Get(), 
			m_resourceLayout[stageIndex], m_cbufferLayout[stageIndex]))
		{
			// ����
		}
		else
		{
			// ���s
			continue;
		}
	}
}

/// @brief �V�F�[�_�I�u�W�F�N�g����
/// @param device �f�o�C�X
/// @param stage �V�F�[�_�X�e�[�W
/// @param blob �R���p�C���f�[�^
void D3D11GraphicsShader::CreateShaderObjct(ID3D11Device1* device, const GraphicsShaderStage& stage, ComPtr<ID3DBlob>& blob)
{
	// com�Q��
	auto& shader = m_comShaders[static_cast<size_t>(stage)];

	// �V�F�[�_��ʐ���
	switch (stage)
	{
	case GraphicsShaderStage::VS:
	{
		ID3D11VertexShader* d3d11Shader;
		CHECK_FAILED(device->CreateVertexShader(blob->GetBufferPointer(), 
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// �C���^�[�t�F�[�X����(�Q�ƃJ�E���g����)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild), 
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// �Q�ƃJ�E���g�����炷
		d3d11Shader->Release();
		vs = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::GS:
	{
		ID3D11GeometryShader* d3d11Shader;
		CHECK_FAILED(device->CreateGeometryShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// �C���^�[�t�F�[�X����(�Q�ƃJ�E���g����)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// �Q�ƃJ�E���g�����炷
		d3d11Shader->Release();
		gs = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::DS:
	{
		ID3D11DomainShader* d3d11Shader;
		CHECK_FAILED(device->CreateDomainShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// �C���^�[�t�F�[�X����(�Q�ƃJ�E���g����)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// �Q�ƃJ�E���g�����炷
		d3d11Shader->Release();
		ds = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::HS:
	{
		ID3D11HullShader* d3d11Shader;
		CHECK_FAILED(device->CreateHullShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// �C���^�[�t�F�[�X����(�Q�ƃJ�E���g����)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// �Q�ƃJ�E���g�����炷
		d3d11Shader->Release();
		hs = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::PS:
	{
		ID3D11PixelShader* d3d11Shader;
		CHECK_FAILED(device->CreatePixelShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// �C���^�[�t�F�[�X����(�Q�ƃJ�E���g����)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// �Q�ƃJ�E���g�����炷
		d3d11Shader->Release();
		ps = d3d11Shader;
	}
		break;
	case GraphicsShaderStage::CS:
	{
		ID3D11ComputeShader* d3d11Shader;
		CHECK_FAILED(device->CreateComputeShader(blob->GetBufferPointer(),
			blob->GetBufferSize(), nullptr, &d3d11Shader));
		// �C���^�[�t�F�[�X����(�Q�ƃJ�E���g����)
		d3d11Shader->QueryInterface(__uuidof(ID3D11DeviceChild),
			reinterpret_cast<void**>(static_cast<ID3D11DeviceChild**>(&shader)));
		// �Q�ƃJ�E���g�����炷
		d3d11Shader->Release();
		cs = d3d11Shader;
	}
		break;
	}
}
