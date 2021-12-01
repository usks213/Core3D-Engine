/*****************************************************************//**
 * \file   Core_Shader.h
 * \brief  シェーダー
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
	/// @brief シェーダーID (格納先ハッシュ値)
	enum class ShaderID : std::uint32_t {};
	/// @brief 存在しないシェーダーID
	constexpr ShaderID NONE_SHADER_ID = std::numeric_limits<ShaderID>::max();

	/// @brief シェーダータイプ
	enum class ShaderType : std::uint8_t {
		Forward,
		Deferred,
		Pre,
		Post,
		Compute,
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


	/// @brief シェーダー生成用構造体
	struct ShaderDesc
	{
		std::uint32_t	m_stages;	// シェーダーステージフラグ
		std::string		m_name;		// シェーダー名
		// シェーダマクロ
	};

	/// @class CoreShader
	/// @brief シェーダ
	class CoreShader
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit CoreShader(ShaderDesc shaderDesc, const ShaderID& id) :
			m_id(id),
			m_desc(shaderDesc),
			m_type(ShaderType::Forward)
		{
		}

		/// @brief デストラクタ
		virtual ~CoreShader() noexcept = default;

	public:
		/// @brief 入力レイアウト情報構造体
		struct InputLayoutVariable
		{
			std::string semanticName;		///< セマンティック名		例:TEXCOOD
			std::uint32_t semanticIndex;	///< セマンティック番号	例:TEXCOOD[0]←
			std::size_t offset;			///< 変数オフセット
			std::size_t arrayNum;			///< 配列の数 例:R32=1,R32B32=2,
			std::size_t formatWidth;		///< フォーマットの幅 例:r16=2,r32=4
			InputLayoutVariable() :
				semanticName(),
				semanticIndex(0),
				offset(0),
				arrayNum(0),
				formatWidth(0) {}
		};

		/// @brief 入力レイアウト情報リスト
		std::vector<InputLayoutVariable> m_inputLayoutVariableList;

		/// @brief CBufferの変数情報
		struct CBufferVariable
		{
			std::string name;		///< 変数名
			std::size_t size;		///< 型サイズ
			std::size_t offset;	///< 変数オフセット
			std::uint8_t stage;	///< ステージ
			std::uint8_t slot;	///< スロット
		};
		/// @brief CBufferの構造体レイアウト情報
		struct CBufferLayout
		{
			std::string		name;	///< cbuffer宣言名
			std::uint32_t	slot;	///< レジスタスロット
			std::size_t		size;	///< cbufferサイズ
			std::vector<CBufferVariable> variables;	// 変数データ
			CBufferLayout() :name(), slot(0), size(0), variables() {}
			CBufferLayout(const std::uint32_t& slot, const std::string& name, const std::size_t& size) :
				slot(slot), name(name), size(size), variables() {}
		};
		/// @brief 全ステージのCBufferレイアウト
		std::array<std::unordered_map<std::uint32_t, CBufferLayout>,
			static_cast<size_t>(ShaderStage::MAX)> m_cbufferLayouts;
		/// @brief CBuffer変数のデフォルト値(初期化子付き値)
		std::unordered_map<std::string, std::unique_ptr<std::byte[]>> m_cbufferDefaults;

		/// @brief シェーダーリソースバインド情報
		struct ShaderBindData
		{
			ShaderStage			stage;
			BindType				type;
			std::string			name;
			std::uint32_t		slot;
			std::uint32_t		space;
			std::uint32_t		rootIndex;
		};

		//--- シェーダーバインド情報(ディスクリプタ) ---

		/// @brief 動的バインド情報
		std::unordered_map<std::string, ShaderBindData> m_dynamicBindData
			[static_cast<size_t>(ShaderStage::MAX)][static_cast<size_t>(BindType::MAX)];

		/// @brief 静的バインド情報
		std::unordered_map<std::string, ShaderBindData> m_staticBindData
			[static_cast<size_t>(ShaderStage::MAX)][static_cast<size_t>(BindType::MAX)];

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief シェーダID
		ShaderID	m_id;
		/// @brief シェーダー生成情報
		ShaderDesc  m_desc;
		/// @brief マクロのハッシュ値

		/// @brief シェーダータイプ
		ShaderType m_type;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		constexpr static std::uint32_t STATIC_BIND_SLOT_BORDER = 8;	///< このスロット移行は共通リソース

	};
}

#endif // !_CORE_SHADER_
