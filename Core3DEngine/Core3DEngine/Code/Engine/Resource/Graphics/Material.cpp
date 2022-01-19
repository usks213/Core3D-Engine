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
	auto pShader = GetResourceManager()->GetResource<GraphicsShader>(m_shaderID);
	auto pRHIShader = pShader->GetRHIGraphicsShader();

	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�œ������O�̃f�[�^���X�V
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto cbufferLayouts = pRHIShader->GetCBufferLayoutMap(stage);

			for (auto& layout : cbufferLayouts)
			{
				auto itr = layout.second.m_variables.find(name);
				// ��v������o�b�t�@���X�V
				if (layout.second.m_variables.end() != itr)
				{
					auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
					std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
					break;
				}
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto cbufferLayouts = pRHIShader->GetCBufferLayoutMap(stage);

		for (auto& layout : cbufferLayouts)
		{
			auto itr = layout.second.m_variables.find(name);
			// ��v������o�b�t�@���X�V
			if (layout.second.m_variables.end() != itr)
			{
				auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
				std::memcpy(pBuffer->GetData() + itr->second.offset, data, itr->second.size);
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief �f�[�^�擾
void* Material::GetData(const char* name, RHI::GraphicsShaderStage stage)
{
	// RHI�V�F�[�_�[�擾
	auto pShader = GetResourceManager()->GetResource<GraphicsShader>(m_shaderID);
	auto pRHIShader = pShader->GetRHIGraphicsShader();

	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�œ������O�̃f�[�^���X�V
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto cbufferLayouts = pRHIShader->GetCBufferLayoutMap(stage);

			for (auto& layout : cbufferLayouts)
			{
				auto itr = layout.second.m_variables.find(name);
				// ��v�����o�b�t�@��Ԃ�
				if (layout.second.m_variables.end() != itr)
				{
					auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
					return pBuffer->GetData() + itr->second.offset;
				}
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto cbufferLayouts = pRHIShader->GetCBufferLayoutMap(stage);

		for (auto& layout : cbufferLayouts)
		{
			auto itr = layout.second.m_variables.find(name);
			// ��v�����o�b�t�@��Ԃ�
			if (layout.second.m_variables.end() != itr)
			{
				auto& pBuffer = m_cbufferData[stageIndex][itr->second.slot];
				return pBuffer->GetData() + itr->second.offset;
			}
		}
	}
}

/// @brief �e�N�X�`���ݒ�
void Material::SetTexture(const char* name, const Texture::ID textureID, RHI::GraphicsShaderStage stage)
{
	constexpr auto TYPE = static_cast<std::size_t>(RHI::ShaderResourceType::TEXTURE);
	// RHI�V�F�[�_�[�擾
	auto pShader = GetResourceManager()->GetResource<GraphicsShader>(m_shaderID);
	auto pRHIShader = pShader->GetRHIGraphicsShader();

	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�œ������O�̃f�[�^���X�V
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto resourceLayouts = pRHIShader->GetResourceLayout(stage);

			auto itr = resourceLayouts.m_localResource[TYPE].find(name);
			// ��v������e�N�X�`�����i�[
			if (resourceLayouts.m_localResource[TYPE].end() != itr)
			{
				m_textureData[stageIndex][itr->second.slot] = textureID;
				break;
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto resourceLayouts = pRHIShader->GetResourceLayout(stage);

		auto itr = resourceLayouts.m_localResource[TYPE].find(name);
		// ��v������e�N�X�`�����i�[
		if (resourceLayouts.m_localResource[TYPE].end() != itr)
		{
			m_textureData[stageIndex][itr->second.slot] = textureID;
		}
	}
}

/// @brief �e�N�X�`���擾
Texture::ID Material::GetTexture(const char* name, RHI::GraphicsShaderStage stage)
{
	constexpr auto TYPE = static_cast<std::size_t>(RHI::ShaderResourceType::TEXTURE);
	// RHI�V�F�[�_�[�擾
	auto pShader = GetResourceManager()->GetResource<GraphicsShader>(m_shaderID);
	auto pRHIShader = pShader->GetRHIGraphicsShader();

	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�œ������O�̃f�[�^���X�V
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto resourceLayouts = pRHIShader->GetResourceLayout(stage);

			auto itr = resourceLayouts.m_localResource[TYPE].find(name);
			// ��v������e�N�X�`�����i�[
			if (resourceLayouts.m_localResource[TYPE].end() != itr)
			{
				return m_textureData[stageIndex][itr->second.slot];
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto resourceLayouts = pRHIShader->GetResourceLayout(stage);

		auto itr = resourceLayouts.m_localResource[TYPE].find(name);
		// ��v������e�N�X�`�����i�[
		if (resourceLayouts.m_localResource[TYPE].end() != itr)
		{
			return m_textureData[stageIndex][itr->second.slot];
		}
	}
}

/// @brief �e�N�X�`���ݒ�
void Material::SetSampler(const char* name, const RHI::SamplerState sampler, RHI::GraphicsShaderStage stage)
{
	constexpr auto TYPE = static_cast<std::size_t>(RHI::ShaderResourceType::SAMPLER);
	// RHI�V�F�[�_�[�擾
	auto pShader = GetResourceManager()->GetResource<GraphicsShader>(m_shaderID);
	auto pRHIShader = pShader->GetRHIGraphicsShader();

	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�œ������O�̃f�[�^���X�V
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto resourceLayouts = pRHIShader->GetResourceLayout(stage);

			auto itr = resourceLayouts.m_localResource[TYPE].find(name);
			// ��v������e�N�X�`�����i�[
			if (resourceLayouts.m_localResource[TYPE].end() != itr)
			{
				m_samplerData[stageIndex][itr->second.slot] = sampler;
				break;
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto resourceLayouts = pRHIShader->GetResourceLayout(stage);

		auto itr = resourceLayouts.m_localResource[TYPE].find(name);
		// ��v������e�N�X�`�����i�[
		if (resourceLayouts.m_localResource[TYPE].end() != itr)
		{
			m_samplerData[stageIndex][itr->second.slot] = sampler;
		}
	}
}

/// @brief �e�N�X�`���擾
RHI::SamplerState Material::GetSampler(const char* name, RHI::GraphicsShaderStage stage)
{
	constexpr auto TYPE = static_cast<std::size_t>(RHI::ShaderResourceType::SAMPLER);
	// RHI�V�F�[�_�[�擾
	auto pShader = GetResourceManager()->GetResource<GraphicsShader>(m_shaderID);
	auto pRHIShader = pShader->GetRHIGraphicsShader();

	// �S�X�e�[�W�T��
	if (stage == RHI::GraphicsShaderStage::MAX)
	{
		// �S�X�e�[�W�œ������O�̃f�[�^���X�V
		for (RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::VS; stage < RHI::GraphicsShaderStage::MAX; ++stage)
		{
			auto stageIndex = static_cast<size_t>(stage);
			auto resourceLayouts = pRHIShader->GetResourceLayout(stage);

			auto itr = resourceLayouts.m_localResource[TYPE].find(name);
			// ��v������e�N�X�`�����i�[
			if (resourceLayouts.m_localResource[TYPE].end() != itr)
			{
				return m_samplerData[stageIndex][itr->second.slot];
			}
		}
	}
	else
	{
		// �w��X�e�[�W�Ō����E�X�V
		auto stageIndex = static_cast<size_t>(stage);
		auto resourceLayouts = pRHIShader->GetResourceLayout(stage);

		auto itr = resourceLayouts.m_localResource[TYPE].find(name);
		// ��v������e�N�X�`�����i�[
		if (resourceLayouts.m_localResource[TYPE].end() != itr)
		{
			return m_samplerData[stageIndex][itr->second.slot];
		}
	}
}
