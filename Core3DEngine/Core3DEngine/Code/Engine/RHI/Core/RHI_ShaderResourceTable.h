/*****************************************************************//**
 * \file   RHI_ShaderResourceTable.h
 * \brief  �V�F�[�_�[���\�[�X�e�[�u��
 *
 * \author USAMI KOSHI
 * \date   2021/12/10
 *********************************************************************/
#ifndef _RHI_SHADER_RESOURCE_TABLE_
#define _RHI_SHADER_RESOURCE_TABLE_

#include "RHI_ShaderUtil.h"
#include "RHI_CommonState.h"
#include <unordered_map>
#include <memory>

namespace Core::RHI
{
	class ShaderResourceTable;

	class ShaderResourceTableLayout
	{
		friend class ShaderResourceTable;
	public:
		ShaderResourceTableLayout();
		~ShaderResourceTableLayout();

		/// @brief �V�F�[�_�[���\�[�X�o�C���h���
		struct ShaderResoureData
		{
			//std::string			name;
			//ShaderStage			stage;
			//ShaderResourceType	type;
			Slot		slot		= 0;
			Space		space		= 0;
			RootIndex	rootIndex	= 0;
		};

	private:

		//--- �V�F�[�_�[���\�[�X�o�C���h���(�f�B�X�N���v�^) ---

		/// @brief ���[�J�����\�[�X�o�C���h���
		std::unordered_map<std::string, ShaderResoureData> m_localResourceData
			[static_cast<size_t>(ShaderStage::MAX)][static_cast<size_t>(ShaderResourceType::MAX)];

		/// @brief �O���[�o�����\�[�X�o�C���h���
		std::unordered_map<std::string, ShaderResoureData> m_globalResourceData
			[static_cast<size_t>(ShaderStage::MAX)][static_cast<size_t>(ShaderResourceType::MAX)];
	};

	class ConstantBuffer;
	class GPUBuffer;
	class Texture;

	class ShaderResourceTable
	{
	public:
		ShaderResourceTable();
		~ShaderResourceTable();

		bool SetConstantBuffer(std::string_view name, std::shared_ptr<ConstantBuffer> constantBuffer);

		bool SetGPUBuffer(std::string_view name, std::shared_ptr<GPUBuffer> gupBuffer);

		bool SetTexture(std::string_view name, std::shared_ptr<Texture> texture);

		bool SetSampler(std::string_view name, SamplerState samplerstate);

	private:

		// �R���X�^���g�o�b�t�@�̔z��
		std::unordered_map<Slot, std::shared_ptr<ConstantBuffer>>	m_ConstantBuffers;
		// GPU�o�b�t�@�̔z��
		std::unordered_map<Slot, std::shared_ptr<GPUBuffer>>		m_GPUBuffers;
		// �e�N�X�`���̔z��
		std::unordered_map<Slot, std::shared_ptr<Texture>>			m_Textures;
		// �T���v���[�̔z��
		std::unordered_map<Slot, SamplerState>						m_Samplers;

	};
}

#endif // !_RHI_SHADER_RESOURCE_TABLE_


