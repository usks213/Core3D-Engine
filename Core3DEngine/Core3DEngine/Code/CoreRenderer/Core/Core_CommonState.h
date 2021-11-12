/*****************************************************************//**
 * \file   Core_CommonState.h
 * \brief  ���ʃX�e�C�g
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _CORE_COMMON_STATE_
#define _CORE_COMMON_STATE_

#include <cstdint>

namespace core
{
	/// @enum RasterizeState
	/// @brief ���X�^���C�U�X�e�[�g
	enum class RasterizeState : std::uint8_t
	{
		UNKNOWN = 0,			///< �s��
		CULL_NONE,				///< �J�����O�Ȃ�
		CULL_FRONT,				///< �\�ʃJ�����O
		CULL_BACK,				///< ���ʃJ�����O
		CULL_NONE_WIREFRAME,	///< ���C���[�t���[�� �J�����O�Ȃ�
		CULL_FRONT_WIREFRAME,	///< ���C���[�t���[�� �\�ʃJ�����O
		CULL_BACK_WIREFRAME,	///< ���C���[�t���[�� ���ʃJ�����O
		SHADOW,					///< �V���h�E�p
		MAX,					///< ���X�^���C�U�X�e�[�g�̐�
	};

	/// @enum SamplerState
	/// @brief �T���v���X�e�[�g
	enum class SamplerState : std::uint8_t
	{
		NONE = 0,			///< �T���v���Ȃ�
		LINEAR_CLAMP,		///< ���j�A�N�����v
		POINT_CLAMP,		///< �|�C���g�N�����v
		ANISOTROPIC_CLAMP,	///< �ٕ����N�����v
		LINEAR_WRAP,		///< ���j�A���b�v
		POINT_WRAP,			///< �|�C���g���b�v
		ANISOTROPIC_WRAP,	///< �ٕ������b�v
		SHADOW,				///< �V���h�E�p
		MAX,				///< �T���v���X�e�[�g�̐�
	};

	/// @enum BlendState
	/// @brief �u�����h�X�e�[�g
	enum class BlendState : std::uint8_t
	{
		UNKNOWN = 0,///< �s��
		NONE,		///< �u�����h�Ȃ�
		ALPHA,		///< ����������
		ADD,		///< ���Z����
		SUB,		///< ���Z����
		MUL,		///< ��Z����
		INV,		///< ���]����
		MAX,		///< �u�����h�X�e�[�g�̐�
	};

	/// @enum DepthStencilState
	/// @brief �[�x�X�e���V���X�e�[�g
	enum class DepthStencilState : std::uint8_t
	{
		UNKNOWN = 0,
		ENABLE_TEST_AND_ENABLE_WRITE,	///< �[�x�X�e���V���e�X�g�L�� & �[�x�X�e���V���X�V�L��
		ENABLE_TEST_AND_DISABLE_WRITE,	///< �[�x�X�e���V���e�X�g�L�� & �[�x�X�e���V���X�V����
		DISABLE_TEST_AND_ENABLE_WRITE,	///< �[�x�X�e���V���e�X�g���� & �[�x�X�e���V���X�V�L��
		DISABLE_TEST_AND_DISABLE_WRITE,	///< �[�x�X�e���V���e�X�g���� & �[�x�X�e���V���X�V����
		MAX,							///< �[�x�X�e���V���X�e�[�g�̐�
	};

	/// @enum PrimitiveTopology
	/// @brief �v���~�e�B�u�g�|���W
	enum class PrimitiveTopology : std::uint8_t
	{
		UNKNOWN = 0,						///< �v���~�e�B�u�g�|���W�s��
		TRIANGLE_LIST,						///< �g���C�A���O�����X�g
		TRIANGLE_STRIP,						///< �g���C�A���O���X�g���b�v
		POINT_LIST,							///< �|�C���g���X�g
		LINE_LIST,							///< ���C�����X�g
		LINE_STRIP,							///< ���C���X�g���b�v
		TRIANGLE_CONTROL_POINT_PATCHLIST,	///< �g���C�A���O���R���g���[���|�C���g�p�b�`���X�g
		MAX,								///< �v���~�e�B�u�g�|���W�̐�
	};

	//----- Bind -----

	/// @brief �V�F�[�_�[�o�C���h���
	enum class BindType : std::uint8_t
	{
		CBV,
		SRV,
		UAV,
		TEXTURE,
		SAMPLER,
		MAX,
	};

	//----- Buffer -----

	/// @enum Usage
	/// @brief ���\�[�X�g�p����
	enum class Usage : std::uint8_t
	{
		DEFAULT = 0,	///< �f�t�H���g
		STATIC,			///< �ÓI
		DYNAMIC,		///< ���I
		STAGING,		///< �f�[�^�]��(�R�s�[)
	};

	/// @enum BindFlags
	/// @brief ���\�[�X�o�C���h�t���O
	enum class BindFlags : std::uint32_t
	{
		UNKNOWN = 0,
		VERTEX_BUFFER = 1 << 0,		///< ���_�o�b�t�@
		INDEX_BUFFER = 1 << 1,		///< �C���f�b�N�X�o�b�t�@
		CONSTANT_BUFFER = 1 << 2,	///< �萔�o�b�t�@
		SHADER_RESOURCE = 1 << 3,	///< �V�F�[�_�[���\�[�X
		STREAM_OUTPUT = 1 << 4,		///< �X�g���[���o��
		RENDER_TARGET = 1 << 5,		///< �����_�[�^�[�Q�b�g
		DEPTH_STENCIL = 1 << 6,		///< �[�x�X�e���V��
		UNORDERED_ACCESS = 1 << 7,	///< Unorderd���\�[�X
		DECODER = 1 << 8,			///< �f�R�[�_�[
		VIDEO_ENCODER = 1 << 9,		///< �G���R�[�_�[
	};

	inline std::uint32_t operator&(const BindFlags& lhs, const BindFlags& rhs) {
		return static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs);
	}
	inline std::uint32_t operator&(const BindFlags& lhs, const std::uint32_t& rhs) {
		return static_cast<std::uint32_t>(lhs) & rhs;
	}
	inline std::uint32_t operator&(const std::uint32_t& lhs, const BindFlags& rhs) {
		return lhs & static_cast<std::uint32_t>(rhs);
	}
	inline std::uint32_t operator|(const BindFlags& lhs, const BindFlags& rhs) {
		return static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs);
	}
	inline std::uint32_t operator|(const BindFlags& lhs, const std::uint32_t& rhs) {
		return static_cast<std::uint32_t>(lhs) | rhs;
	}
	inline std::uint32_t operator|(const std::uint32_t& lhs, const BindFlags& rhs) {
		return lhs | static_cast<std::uint32_t>(rhs);
	}

	/// @enum CPUAccessFlags
	/// @brief CPU�A�N�Z�X�t���O
	enum class CPUAccessFlags : std::uint8_t
	{
		NONE = 0,		///< CPU�A�N�Z�X�Ȃ�
		WRITE = 1 << 0,	///< CPU��������
		READ = 1 << 1,	///< CPU�ǂݍ���
	};

	inline std::uint8_t operator&(const CPUAccessFlags& lhs, const CPUAccessFlags& rhs) {
		return static_cast<std::uint8_t>(lhs) & static_cast<std::uint8_t>(rhs);
	}
	inline std::uint8_t operator&(const CPUAccessFlags& lhs, const std::uint8_t& rhs) {
		return static_cast<std::uint8_t>(lhs) & rhs;
	}
	inline std::uint8_t operator&(const std::uint8_t& lhs, const CPUAccessFlags& rhs) {
		return lhs & static_cast<std::uint8_t>(rhs);
	}
	inline std::uint8_t operator|(const CPUAccessFlags& lhs, const CPUAccessFlags& rhs) {
		return static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs);
	}
	inline std::uint8_t operator|(const CPUAccessFlags& lhs, const std::uint8_t& rhs) {
		return static_cast<std::uint8_t>(lhs) | rhs;
	}
	inline std::uint8_t operator|(const std::uint8_t& lhs, const CPUAccessFlags& rhs) {
		return lhs | static_cast<std::uint8_t>(rhs);
	}

	/// @enum MiscFlags
	/// @brief �o�b�t�@�t���O
	enum class MiscFlags : std::uint32_t
	{
		UNKNONE = 0,
		GENERATE_MIPS = 1 << 0,				///< MIP�}�b�v�̐�����L��
		TEXTURECUBE = 1 << 1,				///< 6�̃e�N�X�`�����܂�Texture2DArray����L���[�u�e�N�X�`�����쐬
		DRAWINDIRECT_ARGS = 1 << 2,			///< InDirect���ߗp�t���O
		BUFFER_ALLOW_RAW_VIEWS = 1 << 3,	///< �o�C�g�A�h���X�o�b�t�@
		BUFFER_STRUCTURED = 1 << 4,			///< �X�g���N�`���[�h�o�b�t�@
		RESOURCE_CLAMP = 1 << 5,			///< MIP�}�b�v�N�����v���g�p���ă��\�[�X��L��
		SHARED_KEYEDMUTEX = 1 << 6,			///< ���\�[�X�̓���
		TILE_POOL = 1 << 7,					///< �^�C���v�[��	 (dx11.2)
		TILED = 1 << 8,						///< �^�C�����\�[�X	 (dx11.2)
	};

	inline std::uint32_t operator&(const MiscFlags& lhs, const MiscFlags& rhs) {
		return static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs);
	}
	inline std::uint32_t operator&(const MiscFlags& lhs, const std::uint32_t& rhs) {
		return static_cast<std::uint32_t>(lhs) & rhs;
	}
	inline std::uint32_t operator&(const std::uint32_t& lhs, const MiscFlags& rhs) {
		return lhs & static_cast<std::uint32_t>(rhs);
	}
	inline std::uint32_t operator|(const MiscFlags& lhs, const MiscFlags& rhs) {
		return static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs);
	}
	inline std::uint32_t operator|(const MiscFlags& lhs, const std::uint32_t& rhs) {
		return static_cast<std::uint32_t>(lhs) | rhs;
	}
	inline std::uint32_t operator|(const std::uint32_t& lhs, const MiscFlags& rhs) {
		return lhs | static_cast<std::uint32_t>(rhs);
	}

	//----- CoreTexture -----

	/// @enum TextureFormat
	/// @brief �e�N�X�`���t�H�[�}�b�g
	enum class TextureFormat : std::uint32_t
	{
		UNKNOWN = 0, // �s��

		R32G32B32A32_TYPELESS,
		R32G32B32A32_FLOAT,
		R32G32B32A32_UINT,
		R32G32B32A32_SINT,

		R32G32B32_TYPELESS,
		R32G32B32_FLOAT,
		R32G32B32_UINT,
		R32G32B32_SINT,

		R16G16B16A16_TYPELESS,
		R16G16B16A16_FLOAT,
		R16G16B16A16_UNORM,
		R16G16B16A16_UINT,
		R16G16B16A16_SNORM,
		R16G16B16A16_SINT,

		R32G32_TYPELESS,
		R32G32_FLOAT,
		R32G32_UINT,
		R32G32_SINT,

		R11G11B10_FLOAT,

		R8G8B8A8_TYPELESS,
		R8G8B8A8_UNORM,
		R8G8B8A8_UNORM_SRGB,
		R8G8B8A8_UINT,
		R8G8B8A8_SNORM,
		R8G8B8A8_SINT,

		R16G16_TYPELESS,
		R16G16_FLOAT,
		R16G16_UNORM,
		R16G16_UINT,
		R16G16_SNORM,
		R16G16_SINT,

		R32_TYPELESS,
		D32_FLOAT,
		R32_FLOAT,
		R32_UINT,
		R32_SINT,

		R24G8_TYPELESS,
		D24_UNORM_S8_UINT,

		R24_UNORM_X8_TYPELESS,
		X24_TYPELESS_G8_UINT,

		R8G8_TYPELESS,
		R8G8_UNORM,
		R8G8_UINT,
		R8G8_SNORM,
		R8G8_SINT,

		R16_TYPELESS,
		R16_FLOAT,
		D16_UNORM,
		R16_UNORM,
		R16_UINT,
		R16_SNORM,
		R16_SINT,

		R8_TYPELESS,
		R8_UNORM,
		R8_UINT,
		R8_SNORM,
		R8_SINT,

		// �u���b�N���k�e�N�X�`��
		BC1_TYPELESS,
		BC1_UNORM,
		BC1_UNORM_SRGB,
		BC2_TYPELESS,
		BC2_UNORM,
		BC2_UNORM_SRGB,
		BC3_TYPELESS,
		BC3_UNORM,
		BC3_UNORM_SRGB,
		BC4_TYPELESS,
		BC4_UNORM,
		BC4_SNORM,
		BC5_TYPELESS,
		BC5_UNORM,
		BC5_SNORM,
		BC6H_TYPELESS,
		BC6H_UF16,
		BC6H_SF16,
		BC7_TYPELESS,
		BC7_UNORM,
		BC7_UNORM_SRGB,

		MAX,
	};

	/// @brief �}���`�T���v��
	struct SampleDesc
	{
		bool			isUse	= false;	///< �}���`�T���v�����邩
		std::uint32_t	count	= 1;		///< �T���v����
		std::uint32_t	quality = 0;		///< �T���v���N�I���e�B
	};

}

#endif // !_CORE_COMMON_STATE_
