/*****************************************************************//**
 * \file   RHI_ShaderUtil.h
 * \brief  シェーダーユーティリティ
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

	constexpr static Slot GLOBAL_BIND_SLOT_BORDER = 8;	///< このスロット移行は共通リソース


	/// @brief シェーダータイプ
	enum class ShaderType : std::uint8_t {
		Forward,
		Deferred,
		Pre,
		Post,
		Compute,
	};

	/// @brief シェーダーバインド種別
	enum class ShaderResourceType : std::uint8_t
	{
		CBV,
		SRV,
		UAV,
		TEXTURE,
		SAMPLER,
		MAX,
	};

	/// @brief セマンティック名
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

	/// @brief シェーダーマクロ
	namespace SHADER_MACRO
	{
#define SHADER_MACRO_NAME(name) constexpr char name[] = #name
		// パス
		SHADER_MACRO_NAME(PASS_FORWARD_BASE);
		SHADER_MACRO_NAME(PASS_FORWARD_ADD);
		SHADER_MACRO_NAME(PASS_DEFERRED_GBUFFER);
		SHADER_MACRO_NAME(PASS_DEFERRED_LIGHTING);
		SHADER_MACRO_NAME(PASS_SHADOW_CASTER);
		SHADER_MACRO_NAME(PASS_MOTION_VECTORS);
		// フラグ
		SHADER_MACRO_NAME(FLAG_TEXTURE);
		SHADER_MACRO_NAME(FLAG_LIGHTING);
		SHADER_MACRO_NAME(FLAG_SHADOW);
		SHADER_MACRO_NAME(FLAG_FOG);
	}


	/// @enum ShaderStage
	/// @brief シェーダーステージ
	enum class ShaderStage : std::uint32_t
	{
		VS,		///< 頂点シェーダー
		HS,		///< ハルシェーダー
		DS,		///< ドメインシェーダー
		GS,		///< ジオメトリシェーダー
		PS,		///< ピクセルシェーダー
		CS,		///< コンピュートシェーダー
		MAX,		///< シェーダーステージ数
	};

	/// @enum ShaderStageFlags
	/// @brief シェーダーステージフラグ
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

	/// @brief ループ用インクリメント
	ShaderStage operator++(ShaderStage& value);
	/// @brief ループ用インクリメント
	ShaderStage operator++(ShaderStage& value, int);
	/// @brief シェーダーステージフラグ用論理和
	std::uint32_t operator|(const ShaderStageFlags& l, const ShaderStageFlags& r);
	/// @brief シェーダーステージフラグ用論理和
	std::uint32_t operator|(const std::uint32_t& l, const ShaderStageFlags& r);

	/// @brief 
	/// @param shaderStage 
	/// @return 
	constexpr ShaderStageFlags ConvertShaderStage2Flags(const ShaderStage& shaderStage);
	/// @brief シェーダーステージがフラグに含まれているか
	/// @details FlagsとANDを取る
	/// @param shaderStageFlags シェーダーステージフラグ
	/// @param shaderStage シェーダーステージ
	/// @return 含まれているならTRUE
	bool hasStaderStage(const std::uint32_t& shaderStageFlags, const ShaderStage& shaderStage);

}

#endif // !_RHI_SHADER_UTIL_

