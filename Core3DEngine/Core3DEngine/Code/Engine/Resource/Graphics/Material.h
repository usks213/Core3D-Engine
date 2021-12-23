/*****************************************************************//**
 * \file   Material.h
 * \brief  �}�e���A��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _MATERIAL_
#define _MATERIAL_

#include "GraphicsShader.h"
#include "Texture.h"
#include <Utils/Util_Mathf.h>
#include <RHI\Core\RHI_GPUBuffer.h>

namespace Core
{
	/// @class Material
	/// @brief �}�e���A��
	class Material : public Resource
	{
		DECLARE_RESOURCE_INFO(Material);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		Material();

		/// @brief �f�X�g���N�^
		~Material() noexcept = default;

		/// @brief �V�F�[�_�[����}�e���A���f�[�^���쐬
		/// @param shader �O���t�B�b�N�X�V�F�[�_�[
		/// @return ���� TRUE / ���s FALSE
		bool CreateMaterialData(const GraphicsShader& shader);

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief �������t���O
		bool					m_isTransparent;
		/// @brief �u�����h�X�e�[�g(�������̂�)
		RHI::BlendState			m_blendState;
		/// @brief �[�x�X�e���V���X�e�[�g
		RHI::DepthStencilState	m_depthStencilState;
		/// @brief ���X�^���C�U�X�e�[�g
		RHI::RasterizeState		m_rasterizeState;
		/// @brief �V�F�[�_ID
		GraphicsShader::ID		m_shaderID;


		/// @brief �S�X�e�[�W�A�X���b�g����CBuffer�f�[�^
		std::array<std::unordered_map<RHI::Slot, std::shared_ptr<RHI::GPUBuffer>>,
			static_cast<size_t>(RHI::GraphicsShaderStage::MAX)>	m_cbufferData;
		/// @brief �S�X�e�[�W�A�X���b�g���̃e�N�X�`��
		std::array<std::unordered_map<RHI::Slot, Texture::ID>,
			static_cast<size_t>(RHI::GraphicsShaderStage::MAX)>	m_textureData;
		/// @brief �S�X�e�[�W�A�X���b�g���̃T���v���X�e�[�g
		std::array<std::unordered_map<RHI::Slot, RHI::SamplerState>,
			static_cast<size_t>(RHI::GraphicsShaderStage::MAX)>	m_samplerData;

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief uint�ݒ�
		void setUint(const char* name, const unsigned int& data, 
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief VectorUint2�ݒ�
		void SetVectorUint2(const char* name, const VectorUint2& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief VectorUint3�ݒ�
		void SetVectorUint3(const char* name, const VectorUint3& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief VectorUint4�ݒ�
		void SetVectorUint4(const char* name, const VectorUint4& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief float�ݒ�
		void SetFloat(const char* name, const float& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Vector2�ݒ�
		void SetVector2(const char* name, const Vector2& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Vector3�ݒ�
		void SetVector3(const char* name, const Vector3& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Vector4�ݒ�
		void SetVector4(const char* name, const Vector4& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Matrix�ݒ�
		void SetMatrix(const char* name, const Matrix& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Struct�ݒ�
		void SetStruct(const char* name, const void* data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief �e�N�X�`���ݒ�
		void SetTexture(const char* name, const Texture::ID textureID,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

		/// @brief �e�N�X�`���擾
		Texture::ID GetTexture(const char* name,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

		/// @brief �T���v���ݒ�
		void SetSampler(const char* name, const RHI::SamplerState sampler,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

		/// @brief �T���v���擾
		RHI::SamplerState GetSampler(const char* name,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

		/// @brief �f�[�^�擾
		void* GetData(const char* name,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

	protected:
		//------------------------------------------------------------------------------
		// protected methods
		//------------------------------------------------------------------------------

		/// @brief �f�[�^�ݒ�
		void SetData(const char* name, const void* data, RHI::GraphicsShaderStage stage);

	};
}

#endif // !_MATERIAL_

