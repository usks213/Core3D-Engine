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
		//--- グラフィックスシェーダー ---
		VS,		///< 頂点シェーダー
		HS,		///< ハルシェーダー
		DS,		///< ドメインシェーダー
		GS,		///< ジオメトリシェーダー
		PS,		///< ピクセルシェーダー

		//--- コンピュートシェーダー ---
		CS,		///< コンピュートシェーダー

		//--- レイトレーシングシェーダー ---


		MAX,		///< シェーダーステージ数
	};


	/// @enum GraphicsShaderStage
	/// @brief グラフィックスシェーダーステージ
	enum class GraphicsShaderStage : std::uint32_t
	{
		VS = static_cast<std::uint32_t>(ShaderStage::VS),		///< 頂点シェーダー
		HS = static_cast<std::uint32_t>(ShaderStage::HS),		///< ハルシェーダー
		DS = static_cast<std::uint32_t>(ShaderStage::DS),		///< ドメインシェーダー
		GS = static_cast<std::uint32_t>(ShaderStage::GS),		///< ジオメトリシェーダー
		PS = static_cast<std::uint32_t>(ShaderStage::PS),		///< ピクセルシェーダー
		MAX,		///< シェーダーステージ数
	};

	/// @enum GraphicsShaderStageFlags
	/// @brief グラフィックスシェーダーステージフラグ
	enum class GraphicsShaderStageFlags : std::uint32_t
	{
		NONE = 0,
		VS = 1 << 1,
		HS = 1 << 2,
		DS = 1 << 3,
		GS = 1 << 4,
		PS = 1 << 5,
		MAX = std::numeric_limits<std::uint32_t>::max(),
		ALL = MAX,
	};

	/// @brief ループ用インクリメント
	GraphicsShaderStage operator++(GraphicsShaderStage& value);
	/// @brief ループ用インクリメント
	GraphicsShaderStage operator++(GraphicsShaderStage& value, int);
	/// @brief シェーダーステージフラグ用論理和
	std::uint32_t operator|(const GraphicsShaderStageFlags& l, const GraphicsShaderStageFlags& r);
	/// @brief シェーダーステージフラグ用論理和
	std::uint32_t operator|(const std::uint32_t& l, const GraphicsShaderStageFlags& r);

	/// @brief 
	/// @param shaderStage 
	/// @return 
	constexpr GraphicsShaderStageFlags ConvertGraphicsShaderStage2Flags(const GraphicsShaderStage& shaderStage);
	/// @brief シェーダーステージがフラグに含まれているか
	/// @details FlagsとANDを取る
	/// @param shaderStageFlags シェーダーステージフラグ
	/// @param shaderStage シェーダーステージ
	/// @return 含まれているならTRUE
	bool hasStaderStage(const std::uint32_t& shaderStageFlags, const GraphicsShaderStage& shaderStage);

}

#endif // !_RHI_SHADER_UTIL_

