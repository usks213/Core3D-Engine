/*****************************************************************//**
 * \file   RHI_CommonState.h
 * \brief  共通ステイト
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _RHI_COMMON_STATE_
#define _RHI_COMMON_STATE_

#include <cstdint>

namespace Core::RHI
{
	/// @enum RasterizeState
	/// @brief ラスタライザステート
	enum class RasterizeState : std::uint8_t
	{
		UNKNOWN = 0,			///< 不明
		CULL_NONE,				///< カリングなし
		CULL_FRONT,				///< 表面カリング
		CULL_BACK,				///< 裏面カリング
		CULL_NONE_WIREFRAME,	///< ワイヤーフレーム カリングなし
		CULL_FRONT_WIREFRAME,	///< ワイヤーフレーム 表面カリング
		CULL_BACK_WIREFRAME,	///< ワイヤーフレーム 裏面カリング
		SHADOW,					///< シャドウ用
		MAX,					///< ラスタライザステートの数
	};

	/// @enum SamplerState
	/// @brief サンプラステート
	enum class SamplerState : std::uint8_t
	{
		NONE = 0,			///< サンプラなし
		LINEAR_CLAMP,		///< リニアクランプ
		POINT_CLAMP,		///< ポイントクランプ
		ANISOTROPIC_CLAMP,	///< 異方性クランプ
		LINEAR_WRAP,		///< リニアラップ
		POINT_WRAP,			///< ポイントラップ
		ANISOTROPIC_WRAP,	///< 異方性ラップ
		SHADOW,				///< シャドウ用
		MAX,				///< サンプラステートの数
	};

	/// @enum BlendState
	/// @brief ブレンドステート
	enum class BlendState : std::uint8_t
	{
		UNKNOWN = 0,///< 不明
		NONE,		///< ブレンドなし
		ALPHA,		///< 半透明合成
		ADD,		///< 加算合成
		SUB,		///< 減算合成
		MUL,		///< 乗算合成
		INV,		///< 反転合成
		MAX,		///< ブレンドステートの数
	};

	/// @enum DepthStencilState
	/// @brief 深度ステンシルステート
	enum class DepthStencilState : std::uint8_t
	{
		UNKNOWN = 0,
		ENABLE_TEST_AND_ENABLE_WRITE,	///< 深度ステンシルテスト有効 & 深度ステンシル更新有効
		ENABLE_TEST_AND_DISABLE_WRITE,	///< 深度ステンシルテスト有効 & 深度ステンシル更新無効
		DISABLE_TEST_AND_ENABLE_WRITE,	///< 深度ステンシルテスト無効 & 深度ステンシル更新有効
		DISABLE_TEST_AND_DISABLE_WRITE,	///< 深度ステンシルテスト無効 & 深度ステンシル更新無効
		MAX,							///< 深度ステンシルステートの数
	};

	/// @enum PrimitiveTopology
	/// @brief プリミティブトポロジ
	enum class PrimitiveTopology : std::uint8_t
	{
		UNKNOWN = 0,						///< プリミティブトポロジ不明
		TRIANGLE_LIST,						///< トライアングルリスト
		TRIANGLE_STRIP,						///< トライアングルストリップ
		POINT_LIST,							///< ポイントリスト
		LINE_LIST,							///< ラインリスト
		LINE_STRIP,							///< ラインストリップ
		TRIANGLE_CONTROL_POINT_PATCHLIST,	///< トライアングルコントロールポイントパッチリスト
		MAX,								///< プリミティブトポロジの数
	};

	//----- Buffer -----

	/// @enum Usage
	/// @brief リソース使用識別
	enum class Usage : std::uint8_t
	{
		DEFAULT = 0,	///< デフォルト
		STATIC,			///< 静的
		DYNAMIC,		///< 動的
		STAGING,		///< データ転送(コピー)
	};

	/// @enum BindFlags
	/// @brief リソースバインドフラグ
	enum class BindFlags : std::uint32_t
	{
		UNKNOWN = 0,
		VERTEX_BUFFER = 1 << 0,		///< 頂点バッファ
		INDEX_BUFFER = 1 << 1,		///< インデックスバッファ
		CONSTANT_BUFFER = 1 << 2,	///< 定数バッファ
		SHADER_RESOURCE = 1 << 3,	///< シェーダーリソース
		STREAM_OUTPUT = 1 << 4,		///< ストリーム出力
		RENDER_TARGET = 1 << 5,		///< レンダーターゲット
		DEPTH_STENCIL = 1 << 6,		///< 深度ステンシル
		UNORDERED_ACCESS = 1 << 7,	///< Unorderdリソース
		DECODER = 1 << 8,			///< デコーダー
		VIDEO_ENCODER = 1 << 9,		///< エンコーダー
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
	/// @brief CPUアクセスフラグ
	enum class CPUAccessFlags : std::uint8_t
	{
		NONE = 0,		///< CPUアクセスなし
		WRITE = 1 << 0,	///< CPU書き込み
		READ = 1 << 1,	///< CPU読み込み
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
	/// @brief バッファフラグ
	enum class MiscFlags : std::uint32_t
	{
		UNKNONE = 0,
		GENERATE_MIPS = 1 << 0,				///< MIPマップの生成を有効
		TEXTURECUBE = 1 << 1,				///< 6つのテクスチャを含むTexture2DArrayからキューブテクスチャを作成
		DRAWINDIRECT_ARGS = 1 << 2,			///< InDirect命令用フラグ
		BUFFER_ALLOW_RAW_VIEWS = 1 << 3,	///< バイトアドレスバッファ
		BUFFER_STRUCTURED = 1 << 4,			///< ストラクチャードバッファ
		RESOURCE_CLAMP = 1 << 5,			///< MIPマップクランプを使用してリソースを有効
		SHARED_KEYEDMUTEX = 1 << 6,			///< リソースの同期
		TILE_POOL = 1 << 7,					///< タイルプール	 (dx11.2)
		TILED = 1 << 8,						///< タイルリソース	 (dx11.2)
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

	//----- Texture -----

	/// @enum TextureFormat
	/// @brief テクスチャフォーマット
	enum class TextureFormat : std::uint32_t
	{
		UNKNOWN = 0, // 不明

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

		// ブロック圧縮テクスチャ
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

	/// @brief マルチサンプル
	struct SampleDesc
	{
		bool			isUse	= false;	///< マルチサンプルするか
		std::uint32_t	count	= 1;		///< サンプル数
		std::uint32_t	quality = 0;		///< サンプルクオリティ
	};

}

#endif // !_RHI_COMMON_STATE_
