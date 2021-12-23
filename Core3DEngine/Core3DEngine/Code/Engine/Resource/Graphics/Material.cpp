/*****************************************************************//**
 * \file   Material.h
 * \brief  �}�e���A��
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "Material.h"
#include <Resource\Core\ResourceManager.h>
#include <Core\Engine.h>
#include <RHI\Core\RHI_Renderer.h>
#include <RHI\Core\RHI_Device.h>

using namespace Core;

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

 /// @brief �R���X�g���N�^
Material::Material() :
	m_isTransparent(false),
	m_blendState(RHI::BlendState::NONE),
	m_depthStencilState(RHI::DepthStencilState::ENABLE_TEST_AND_ENABLE_WRITE),
	m_rasterizeState(RHI::RasterizeState::CULL_NONE),
	m_shaderID(GraphicsShader::NONE_ID)
{
}

/// @brief �V�F�[�_�[����}�e���A���f�[�^���쐬
/// @param shader �O���t�B�b�N�X�V�F�[�_�[
/// @return ���� TRUE / ���s FALSE
bool Material::CreateMaterialData(const GraphicsShader& shader)
{
	auto* pEngine = GetResourceManager()->GetEngine();
	auto* pDevice = pEngine->GetRenderer()->GetDevice();
	auto pRHIShader = shader.GetRHIGraphicsShader();

	// �o�b�t�@Desc
	RHI::ResourceDesc desc = {};
	desc.bindFlags = 0 | RHI::BindFlags::CONSTANT_BUFFER;
	desc.cpuAccessFlags = 0 | RHI::CPUAccessFlags::WRITE;
	desc.miscFlags = 0;
	desc.usage = RHI::Usage::DYNAMIC;
	desc.buffer.count = 1;

	// �V�F�[�_����}�e���A���f�[�^�𐶐�
	for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		auto resourceLayout = pRHIShader->GetResourceLayout(stage);

		//--- CBuffer������
		for (const auto& cbLayout : pRHIShader->GetCBufferLayoutMap(stage))
		{
			// GPUBuffer�m��
			desc.buffer.size = cbLayout.second.m_size;
			auto pBuffer = pDevice->CreateGPUBuffer(desc);

			// �ϐ��f�[�^�i�[
			for (const auto& var : cbLayout.second.m_variables)
			{
				auto& defaltVar = var.second.defaultVal;
				// �������q�f�[�^������ꍇ�͏���������
				if (defaltVar.empty())
				{
					std::memset(pBuffer->GetData() + var.second.offset, 0, var.second.size);
				}
				else
				{
					std::memcpy(pBuffer->GetData() + var.second.offset,
						defaltVar.data(), var.second.size);	// �������c
				}
			}

			// GPUBuffer�f�[�^
			m_cbufferData[stageIndex][cbLayout.first] = pBuffer;
		}

		//--- �e�N�X�`��������
		for (const auto& tex : resourceLayout.m_localResource[static_cast<size_t>(RHI::ShaderResourceType::TEXTURE)])
		{
			m_textureData[stageIndex][tex.second.slot] = Texture::NONE_ID;
		}

		//--- �T���v��
		for (const auto& smp : resourceLayout.m_localResource[static_cast<size_t>(RHI::ShaderResourceType::SAMPLER)])
		{
			m_samplerData[stageIndex][smp.second.slot] = RHI::SamplerState::NONE;
		}
	}
}

//------------------------------------------------------------------------------
// protected methods
//------------------------------------------------------------------------------

/// @brief �f�[�^�ݒ�
void Material::SetData(const char* name, const void* data, RHI::GraphicsShaderStage stage)
{
	// RHI�V�F�[�_�[�擾
	auto pRHIShader = GetResourceManager();

	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�œ������O�̃f�[�^���X�V
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto itr = m_cbufferVariableTable[stageIndex].find(name);

			// ��v������o�b�t�@���X�V
			if (m_cbufferVariableTable[stageIndex].end() != itr)
			{
				auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
				std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto itr = m_cbufferVariableTable[stageIndex].find(name);

		// ��v������o�b�t�@���X�V
		if (m_cbufferVariableTable[stageIndex].end() != itr)
		{
			auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
			std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
		}
	}
}

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief �f�[�^�擾
void* Material::GetData(const char* name, RHI::GraphicsShaderStage stage)
{
	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�ōŏ��Ɍ������f�[�^
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto itr = m_cbufferVariableTable[stageIndex].find(name);

			// ��v������o�b�t�@���X�V
			if (m_cbufferVariableTable[stageIndex].end() != itr)
			{
				auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
				return pBuffer->GetData() + itr->second.offset;
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto itr = m_cbufferVariableTable[stageIndex].find(name);

		// ��v������o�b�t�@���X�V
		if (m_cbufferVariableTable[stageIndex].end() != itr)
		{
			auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
			return pBuffer->GetData() + itr->second.offset;
		}
	}
}

/// @brief �e�N�X�`���ݒ�
void Material::SetTexture(const char* name, const Texture::ID textureID, RHI::GraphicsShaderStage stage)
{
	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�œ������O�̃f�[�^���X�V
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto itr = m_textureData[stageIndex].find(name);

			// ��v������e�N�X�`�����i�[
			if (m_cbufferVariableTable[stageIndex].end() != itr)
			{
				auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
				std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto itr = m_cbufferVariableTable[stageIndex].find(name);

		// ��v������o�b�t�@���X�V
		if (m_cbufferVariableTable[stageIndex].end() != itr)
		{
			auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
			std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
		}
	}
}

/// @brief �e�N�X�`���擾
TextureID Material::GetTexture(const char* name, RHI::GraphicsShaderStage stage)
{
	// ����
	for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		for (const auto& texData : m_textureData[stageIndex])
		{
			if (texData.second.name == name)
			{
				return texData.second.id;
			}
		}
	}
}

/// @brief �T���v���ݒ�
void Material::SetSampler(const char* name, const SamplerState sampler, RHI::GraphicsShaderStage stage)
{
	// ����
	for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		for (auto& samData : m_samplerData[stageIndex])
		{
			if (samData.second.name == name)
			{
				samData.second.state = sampler;
				return;
			}
		}
	}
}

/// @brief �T���v���擾
SamplerState Material::GetSampler(const char* name, RHI::GraphicsShaderStage stage)
{
	// ����
	for (GraphicsShaderStage stage = GraphicsShaderStage::VS; stage < GraphicsShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		for (auto& samData : m_samplerData[stageIndex])
		{
			if (samData.second.name == name)
			{
				return samData.second.state;
			}
		}
	}
}
