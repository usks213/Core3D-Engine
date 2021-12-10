/*****************************************************************//**
 * \file   RHI_ShaderUtil.h
 * \brief  �V�F�[�_�[���[�e�B���e�B
 *
 * \author USAMI KOSHI
 * \date   2021/12/10
 *********************************************************************/
#ifndef _RHI_SHADER_UTIL_
#define _RHI_SHADER_UTIL_

#include <cstdint>
#include <limits>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace Core::RHI
{
	using Slot = std::uint32_t;
	using Space = std::uint32_t;
	using RootIndex = std::uint32_t;

	constexpr static Slot GLOBAL_BIND_SLOT_BORDER = 8;	///< ���̃X���b�g�ڍs�͋��ʃ��\�[�X


	/// @brief �V�F�[�_�[�^�C�v
	enum class ShaderType : std::uint8_t {
		Forward,
		Deferred,
		Pre,
		Post,
		Compute,
	};

	/// @brief �V�F�[�_�[�o�C���h���
	enum class ShaderResourceType : std::uint8_t
	{
		CBV,
		SRV,
		UAV,
		TEXTURE,
		SAMPLER,
		MAX,
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

}

#endif // !_RHI_SHADER_UTIL_

