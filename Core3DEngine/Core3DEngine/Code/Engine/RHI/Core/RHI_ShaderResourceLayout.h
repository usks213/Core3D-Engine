/*****************************************************************//**
 * \file   RHI_ShaderResourceLayout.h
 * \brief  �V�F�[�_�[���\�[�X���C�A�E�g
 *
 * \author USAMI KOSHI
 * \date   2021/12/10
 *********************************************************************/
#ifndef RHI_SHADER_RESOURCE_LAYOUT_
#define RHI_SHADER_RESOURCE_LAYOUT_

#include "RHI_ShaderUtil.h"
#include "RHI_CommonState.h"
#include <unordered_map>
#include <memory>

namespace Core::RHI
{
	class ShaderResourceLayout
	{
	public:
		ShaderResourceLayout();
		~ShaderResourceLayout();

		/// @brief �V�F�[�_�[���\�[�X�o�C���h���
		struct ShaderResoureData
		{
			//std::string			name;
			//ShaderResourceType	type;
			Slot		slot		= 0;
			Space		space		= 0;
			RootIndex	rootIndex	= 0;
		};

	public:
		//--- �V�F�[�_�[���\�[�X�o�C���h���(�f�B�X�N���v�^) ---

		/// @brief ���[�J�����\�[�X�o�C���h���
		std::unordered_map<std::string, ShaderResoureData> m_localResource[static_cast<size_t>(ShaderResourceType::MAX)];

		/// @brief �O���[�o�����\�[�X�o�C���h���
		std::unordered_map<std::string, ShaderResoureData> m_globalResource[static_cast<size_t>(ShaderResourceType::MAX)];

	};

	//class ConstantBuffer;
	//class GPUBuffer;
	//class Texture;

	//class ShaderResourceTable
	//{
	//public:
	//	ShaderResourceTable();
	//	~ShaderResourceTable();

	//	bool SetConstantBuffer(GraphicsShaderStage stage, std::string_view name, std::shared_ptr<ConstantBuffer> constantBuffer);

	//	bool SetGPUBuffer(GraphicsShaderStage stage, std::string_view name, std::shared_ptr<GPUBuffer> gupBuffer);

	//	bool SetTexture(GraphicsShaderStage stage, std::string_view name, std::shared_ptr<Texture> texture);

	//	bool SetSampler(GraphicsShaderStage stage, std::string_view name, SamplerState samplerState);

	//private:

	//	// �e�[�u�����C�A�E�g
	//	ShaderResourceLayout									m_layout;
	//	// �R���X�^���g�o�b�t�@�̔z��
	//	std::unordered_map<Slot, std::shared_ptr<ConstantBuffer>>	m_ConstantBuffers[static_cast<size_t>(GraphicsShaderStage::MAX)];
	//	// GPU�o�b�t�@�̔z��
	//	std::unordered_map<Slot, std::shared_ptr<GPUBuffer>>		m_GPUBuffers[static_cast<size_t>(GraphicsShaderStage::MAX)];
	//	// �e�N�X�`���̔z��
	//	std::unordered_map<Slot, std::shared_ptr<Texture>>			m_Textures[static_cast<size_t>(GraphicsShaderStage::MAX)];
	//	// �T���v���[�̔z��
	//	std::unordered_map<Slot, SamplerState>						m_Samplers[static_cast<size_t>(GraphicsShaderStage::MAX)];

	//};
}

#endif // !RHI_SHADER_RESOURCE_LAYOUT_


