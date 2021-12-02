/*****************************************************************//**
 * \file   Material.h
 * \brief  �}�e���A��
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_MATERIAL_
#define _CORE_MATERIAL_

#include "Shader.h"
#include "Texture.h"
#include <Utils/Util_Mathf.h>


namespace Core
{
	/// @brief �}�e���A��ID
	enum class MaterialID : std::uint32_t {};
	/// @brief ���݂��Ȃ��}�e���A��ID
	constexpr MaterialID NONE_MATERIAL_ID = std::numeric_limits<MaterialID>::max();


	/// @class CoreMaterial
	/// @brief �}�e���A��
	class CoreMaterial
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param �V�F�[�_���
		explicit CoreMaterial(const MaterialID& id, const std::string& name, const CoreShader& shader);

		/// @brief �f�X�g���N�^
		virtual ~CoreMaterial() noexcept = default;


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief �}�e���A��ID
		MaterialID			m_id;
		/// @brief �}�e���A����
		std::string			m_name;
		/// @brief �������t���O
		bool				m_isTransparent;
		/// @brief �u�����h�X�e�[�g(�������̂�)
		BlendState			m_blendState;
		/// @brief �[�x�X�e���V���X�e�[�g
		DepthStencilState	m_depthStencilState;
		/// @brief ���X�^���C�U�X�e�[�g
		RasterizeState		m_rasterizeState;
		/// @brief �V�F�[�_ID
		ShaderID			m_shaderID;
		/// @brief �V�F�[�_�[�^�C�v
		ShaderType			m_shaderType;

		/// @brief CBuffer�f�[�^
		struct CBuffer
		{
			std::string						name;
			std::unique_ptr<std::byte[]>	data;
			std::size_t						size;
			bool							isUpdate;	///< true�Ȃ�X�V����
		};

		/// @brief �e�N�X�`���f�[�^
		struct TextureData
		{
			std::string name;
			TextureID	id;
		};

		/// @brief �T���v���[�f�[�^
		struct SamplerData
		{
			std::string		name;
			SamplerState	state;
		};

		/// @brief �S�X�e�[�W�A�X���b�g����CBuffer�f�[�^
		std::array<std::unordered_map<std::uint32_t, CBuffer>,
			static_cast<size_t>(ShaderStage::MAX)>	m_cbufferData;
		/// @brief �S�X�e�[�W�A�X���b�g�̃o�C���h����e�N�X�`��
		std::array<std::unordered_map<std::uint32_t, TextureData>,
			static_cast<size_t>(ShaderStage::MAX)>	m_textureData;
		/// @brief �S�X�e�[�W�A�X���b�g���̃T���v���X�e�[�g
		std::array<std::unordered_map<std::uint32_t, SamplerData>,
			static_cast<size_t>(ShaderStage::MAX)>	m_samplerData;

		/// @brief CBuffer�ϐ��f�[�^
		std::unordered_map<std::string, CoreShader::CBufferVariable> m_cbufferVariable;

		/// @brief  �S�X�e�[�W�A�X���b�g����CBuffer�̐�
		std::uint32_t m_cbufferCount;

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief uint�ݒ�
		void setUint(const char* name, const unsigned int& data) { setData(name, &data); }

		/// @brief VectorUint2�ݒ�
		void setVectorUint2(const char* name, const VectorUint2& data) { setData(name, &data); }

		/// @brief VectorUint3�ݒ�
		void setVectorUint3(const char* name, const VectorUint3& data) { setData(name, &data); }

		/// @brief VectorUint4�ݒ�
		void setVectorUint4(const char* name, const VectorUint4& data) { setData(name, &data); }

		/// @brief float�ݒ�
		void setFloat(const char* name, const float& data) { setData(name, &data); }

		/// @brief Vector2�ݒ�
		void setVector2(const char* name, const Vector2& data) { setData(name, &data); }

		/// @brief Vector3�ݒ�
		void setVector3(const char* name, const Vector3& data) { setData(name, &data); }

		/// @brief Vector4�ݒ�
		void setVector4(const char* name, const Vector4& data) { setData(name, &data); }

		/// @brief Matrix�ݒ�
		void setMatrix(const char* name, const Matrix& data) { setData(name, &data); }

		/// @brief Struct�ݒ�
		void setStruct(const char* name, const void* data) { setData(name, &data); }

		/// @brief �e�N�X�`���ݒ�
		void setTexture(const char* name, const TextureID textureID);

		/// @brief �e�N�X�`���擾
		TextureID getTexture(const char* name);

		/// @brief �T���v���ݒ�
		void setSampler(const char* name, const SamplerState sampler);

		/// @brief �T���v���擾
		SamplerState GetSampler(const char* name);

		/// @brief �f�[�^�擾
		void* getData(const char* name);

	protected:
		//------------------------------------------------------------------------------
		// protected methods
		//------------------------------------------------------------------------------

		/// @brief �f�[�^�ݒ�
		void setData(const char* name, const void* data);

	};
}

#endif // !_CORE_MATERIAL_

