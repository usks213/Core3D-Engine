/*****************************************************************//**
 * \file   Core_Shader.h
 * \brief  �V�F�[�_�[
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_SHADER_
#define _CORE_SHADER_

#include <cstdint>
#include <limits>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <array>

#include "Core_CommonState.h"

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace core
{
	/// @brief �V�F�[�_�[ID (�i�[��n�b�V���l)
	enum class ShaderID : std::uint32_t {};
	/// @brief ���݂��Ȃ��V�F�[�_�[ID
	constexpr ShaderID NONE_SHADER_ID = std::numeric_limits<ShaderID>::max();

	/// @brief �V�F�[�_�[�^�C�v
	enum class ShaderType : std::uint8_t {
		Forward,
		Deferred,
		Pre,
		Post,
		Compute,
	};

	/// @brief �Z�}���e�B�b�N��
	namespace SEMANTIC_NAME
	{
		constexpr char POSITION[] = "POSITION";
		constexpr char NORMAL[] = "NORMAL";
		constexpr char TANGENT[] = "TANGENT";
		constexpr char BINORMAL[] = "BINORMAL";
		constexpr char COLOR[] = "COLOR";
		constexpr char TEXCOORD[] = "TEXCOORD";
		constexpr char BONE_WEIGHT[] = "BLENDWEIGHT";
		constexpr char BONE_INDEX[] = "BLENDINDICES";
	}

	/// @brief �V�F�[�_�[�}�N��
	namespace SHADER_MACRO
	{
#define SHADER_MACRO_NAME(name) constexpr char name[] = #name
		// �p�X
		SHADER_MACRO_NAME(PASS_FORWARD_BASE);
		SHADER_MACRO_NAME(PASS_FORWARD_ADD);
		SHADER_MACRO_NAME(PASS_DEFERRED_GBUFFER);
		SHADER_MACRO_NAME(PASS_DEFERRED_LIGHTING);
		SHADER_MACRO_NAME(PASS_SHADOW_CASTER);
		SHADER_MACRO_NAME(PASS_MOTION_VECTORS);
		// �t���O
		SHADER_MACRO_NAME(FLAG_TEXTURE);
		SHADER_MACRO_NAME(FLAG_LIGHTING);
		SHADER_MACRO_NAME(FLAG_SHADOW);
		SHADER_MACRO_NAME(FLAG_FOG);
	}


	/// @enum ShaderStage
	/// @brief �V�F�[�_�[�X�e�[�W
	enum class ShaderStage : std::uint32_t
	{
		VS,		///< ���_�V�F�[�_�[
		HS,		///< �n���V�F�[�_�[
		DS,		///< �h���C���V�F�[�_�[
		GS,		///< �W�I���g���V�F�[�_�[
		PS,		///< �s�N�Z���V�F�[�_�[
		CS,		///< �R���s���[�g�V�F�[�_�[
		MAX,		///< �V�F�[�_�[�X�e�[�W��
	};

	/// @enum ShaderStageFlags
	/// @brief �V�F�[�_�[�X�e�[�W�t���O
	enum class ShaderStageFlags : std::uint32_t
	{
		NONE = 0,
		VS = 1 << 1,
		HS = 1 << 2,
		DS = 1 << 3,
		GS = 1 << 4,
		PS = 1 << 5,
		CS = 1 << 6,
		MAX = std::numeric_limits<std::uint32_t>::max(),
		ALL = MAX,
	};

	/// @brief ���[�v�p�C���N�������g
	ShaderStage operator++(ShaderStage& value);
	/// @brief ���[�v�p�C���N�������g
	ShaderStage operator++(ShaderStage& value, int);
	/// @brief �V�F�[�_�[�X�e�[�W�t���O�p�_���a
	std::uint32_t operator|(const ShaderStageFlags& l, const ShaderStageFlags& r);
	/// @brief �V�F�[�_�[�X�e�[�W�t���O�p�_���a
	std::uint32_t operator|(const std::uint32_t& l, const ShaderStageFlags& r);

	/// @brief 
	/// @param shaderStage 
	/// @return 
	constexpr ShaderStageFlags ConvertShaderStage2Flags(const ShaderStage& shaderStage);
	/// @brief �V�F�[�_�[�X�e�[�W���t���O�Ɋ܂܂�Ă��邩
	/// @details Flags��AND�����
	/// @param shaderStageFlags �V�F�[�_�[�X�e�[�W�t���O
	/// @param shaderStage �V�F�[�_�[�X�e�[�W
	/// @return �܂܂�Ă���Ȃ�TRUE
	bool hasStaderStage(const std::uint32_t& shaderStageFlags, const ShaderStage& shaderStage);


	/// @brief �V�F�[�_�[�����p�\����
	struct ShaderDesc
	{
		std::uint32_t	m_stages;	// �V�F�[�_�[�X�e�[�W�t���O
		std::string		m_name;		// �V�F�[�_�[��
		// �V�F�[�_�}�N��
	};

	/// @class CoreShader
	/// @brief �V�F�[�_
	class CoreShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit CoreShader(ShaderDesc shaderDesc, const ShaderID& id) :
			m_id(id),
			m_desc(shaderDesc),
			m_type(ShaderType::Forward)
		{
		}

		/// @brief �f�X�g���N�^
		virtual ~CoreShader() noexcept = default;

	public:
		/// @brief ���̓��C�A�E�g���\����
		struct InputLayoutVariable
		{
			std::string semanticName;		///< �Z�}���e�B�b�N��		��:TEXCOOD
			std::uint32_t semanticIndex;	///< �Z�}���e�B�b�N�ԍ�	��:TEXCOOD[0]��
			std::size_t offset;			///< �ϐ��I�t�Z�b�g
			std::size_t arrayNum;			///< �z��̐� ��:R32=1,R32B32=2,
			std::size_t formatWidth;		///< �t�H�[�}�b�g�̕� ��:r16=2,r32=4
			InputLayoutVariable() :
				semanticName(),
				semanticIndex(0),
				offset(0),
				arrayNum(0),
				formatWidth(0) {}
		};

		/// @brief ���̓��C�A�E�g��񃊃X�g
		std::vector<InputLayoutVariable> m_inputLayoutVariableList;

		/// @brief CBuffer�̕ϐ����
		struct CBufferVariable
		{
			std::string name;		///< �ϐ���
			std::size_t size;		///< �^�T�C�Y
			std::size_t offset;	///< �ϐ��I�t�Z�b�g
			std::uint8_t stage;	///< �X�e�[�W
			std::uint8_t slot;	///< �X���b�g
		};
		/// @brief CBuffer�̍\���̃��C�A�E�g���
		struct CBufferLayout
		{
			std::string		name;	///< cbuffer�錾��
			std::uint32_t	slot;	///< ���W�X�^�X���b�g
			std::size_t		size;	///< cbuffer�T�C�Y
			std::vector<CBufferVariable> variables;	// �ϐ��f�[�^
			CBufferLayout() :name(), slot(0), size(0), variables() {}
			CBufferLayout(const std::uint32_t& slot, const std::string& name, const std::size_t& size) :
				slot(slot), name(name), size(size), variables() {}
		};
		/// @brief �S�X�e�[�W��CBuffer���C�A�E�g
		std::array<std::unordered_map<std::uint32_t, CBufferLayout>,
			static_cast<size_t>(ShaderStage::MAX)> m_cbufferLayouts;
		/// @brief CBuffer�ϐ��̃f�t�H���g�l(�������q�t���l)
		std::unordered_map<std::string, std::unique_ptr<std::byte[]>> m_cbufferDefaults;

		/// @brief �V�F�[�_�[���\�[�X�o�C���h���
		struct ShaderBindData
		{
			ShaderStage			stage;
			BindType				type;
			std::string			name;
			std::uint32_t		slot;
			std::uint32_t		space;
			std::uint32_t		rootIndex;
		};

		//--- �V�F�[�_�[�o�C���h���(�f�B�X�N���v�^) ---

		/// @brief ���I�o�C���h���
		std::unordered_map<std::string, ShaderBindData> m_dynamicBindData
			[static_cast<size_t>(ShaderStage::MAX)][static_cast<size_t>(BindType::MAX)];

		/// @brief �ÓI�o�C���h���
		std::unordered_map<std::string, ShaderBindData> m_staticBindData
			[static_cast<size_t>(ShaderStage::MAX)][static_cast<size_t>(BindType::MAX)];

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief �V�F�[�_ID
		ShaderID	m_id;
		/// @brief �V�F�[�_�[�������
		ShaderDesc  m_desc;
		/// @brief �}�N���̃n�b�V���l

		/// @brief �V�F�[�_�[�^�C�v
		ShaderType m_type;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		constexpr static std::uint32_t STATIC_BIND_SLOT_BORDER = 8;	///< ���̃X���b�g�ڍs�͋��ʃ��\�[�X

	};
}

#endif // !_CORE_SHADER_
