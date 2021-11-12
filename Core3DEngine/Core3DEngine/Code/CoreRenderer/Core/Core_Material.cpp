/*****************************************************************//**
 * \file   Core_Material.h
 * \brief  �}�e���A��
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/

#include "Core_Material.h"
using namespace core;

 /// @brief �R���X�g���N�^
CoreMaterial::CoreMaterial(const MaterialID& id, const std::string& name, const CoreShader& shader) :
	m_id(id),
	m_name(name),
	m_isTransparent(false),
	m_blendState(BlendState::NONE),
	m_depthStencilState(DepthStencilState::ENABLE_TEST_AND_ENABLE_WRITE),
	m_rasterizeState(RasterizeState::CULL_NONE),
	m_shaderID(shader.m_id),
	m_shaderType(shader.m_type),
	m_cbufferCount(0)
{
	// �V�F�[�_����}�e���A���f�[�^�𐶐�
	for (ShaderStage stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
	{
		//--- CBuffer�m��
		auto stageIndex = static_cast<size_t>(stage);
		for (const auto& cbLayout : shader.m_cbufferLayouts[stageIndex])
		{
			auto& cbData = m_cbufferData[stageIndex][cbLayout.first];
			// ���O
			cbData.name = cbLayout.second.name;
			// �o�b�t�@�f�[�^�m��
			cbData.data = std::make_unique<std::byte[]>(cbLayout.second.size);
			// �o�b�t�@�T�C�Y
			cbData.size = cbLayout.second.size;
			// �X�V�t���O
			cbData.isUpdate = true;
			// �J�E���g���Z
			++m_cbufferCount;

			// �ϐ��f�[�^�i�[
			for (const auto& var : cbLayout.second.variables)
			{
				const auto& defaltVar = shader.m_cbufferDefaults.find(var.name);
				// �������q�f�[�^������ꍇ�͏���������
				if (defaltVar != shader.m_cbufferDefaults.end())
				{
					std::memcpy(cbData.data.get() + var.offset, 
						defaltVar->second.get(), var.size);	// �������c
				}
				else
				{
					std::memset(cbData.data.get() + var.offset, 0, var.size);
				}

				// CBuffer�ϐ��f�[�^
				m_cbufferVariable.emplace(var.name, var);
			}
		}

		//--- �e�N�X�`��������
		for (const auto& tex : shader.m_dynamicBindData[stageIndex][static_cast<size_t>(BindType::TEXTURE)])
		{
			m_textureData[stageIndex][tex.second.slot].name = tex.second.name;
			m_textureData[stageIndex][tex.second.slot].id = NONE_TEXTURE_ID;
		}

		//--- �T���v��
		for (const auto& smp : shader.m_dynamicBindData[stageIndex][static_cast<size_t>(BindType::SAMPLER)])
		{
			m_samplerData[stageIndex][smp.second.slot].name = smp.second.name;
			m_samplerData[stageIndex][smp.second.slot].state = SamplerState::NONE;
		}
	}
}

/// @brief �f�[�^�ݒ�
void CoreMaterial::setData(const char* name, const void* data)
{
	for (const auto& var : m_cbufferVariable)
	{
		if (var.second.name == name)
		{
			auto& cbData = m_cbufferData[var.second.stage][var.second.slot];
			std::memcpy(cbData.data.get() + var.second.offset, data, var.second.size);
			cbData.isUpdate = true;
			break;
		}
	}

	//// ����
	//for (ShaderStage stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
	//{
	//	auto stageIndex = static_cast<size_t>(stage);
	//	for (const auto& cbLayout : m_pShader->m_cbufferLayouts[stageIndex])
	//	{
	//		bool bBreak = false;
	//		// �ϐ��f�[�^
	//		for (const auto& var : cbLayout.second.variables)
	//		{
	//			// ��v����
	//			if (var.name == name)
	//			{
	//				auto& cbData = m_cbufferData[stageIndex][cbLayout.first];
	//				std::memcpy(cbData.data.get() + var.offset, data, var.size);
	//				cbData.isUpdate = true;
	//				bBreak = true;
	//				break;
	//			}
	//		}
	//		if (bBreak) break;
	//	}
	//}
}

/// @brief �f�[�^�擾
void* CoreMaterial::getData(const char* name)
{
	for (const auto& var : m_cbufferVariable)
	{
		if (var.second.name == name)
		{
			return m_cbufferData[var.second.stage][var.second.slot].data.get() + var.second.offset;
		}
	}

	return nullptr;

	//// ����
	//for (ShaderStage stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
	//{
	//	auto stageIndex = static_cast<size_t>(stage);
	//	for (const auto& cbLayout : m_pShader->m_cbufferLayouts[stageIndex])
	//	{
	//		bool bBreak = false;
	//		// �ϐ��f�[�^
	//		for (const auto& var : cbLayout.second.variables)
	//		{
	//			// ��v����
	//			if (var.name == name)
	//			{
	//				auto& cbData = m_cbufferData[stageIndex][cbLayout.first];
	//				return cbData.data.get() + var.offset;
	//			}
	//		}
	//		if (bBreak) break;
	//	}
	//}
}

/// @brief �e�N�X�`���ݒ�
void CoreMaterial::setTexture(const char* name, const TextureID textureID)
{
	// ����
	for (ShaderStage stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
	{
		auto stageIndex = static_cast<size_t>(stage);
		for (auto& texData : m_textureData[stageIndex])
		{
			if (texData.second.name == name)
			{
				texData.second.id = textureID;
				return;
			}
		}
	}
}

/// @brief �e�N�X�`���擾
TextureID CoreMaterial::getTexture(const char* name)
{
	// ����
	for (ShaderStage stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
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
void CoreMaterial::setSampler(const char* name, const SamplerState sampler)
{
	// ����
	for (ShaderStage stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
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
SamplerState CoreMaterial::getSampler(const char* name)
{
	// ����
	for (ShaderStage stage = ShaderStage::VS; stage < ShaderStage::MAX; ++stage)
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
