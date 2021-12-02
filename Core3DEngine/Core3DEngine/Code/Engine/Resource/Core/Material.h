/*****************************************************************//**
 * \file   Material.h
 * \brief  マテリアル
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
	/// @brief マテリアルID
	enum class MaterialID : std::uint32_t {};
	/// @brief 存在しないマテリアルID
	constexpr MaterialID NONE_MATERIAL_ID = std::numeric_limits<MaterialID>::max();


	/// @class CoreMaterial
	/// @brief マテリアル
	class CoreMaterial
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param シェーダ情報
		explicit CoreMaterial(const MaterialID& id, const std::string& name, const CoreShader& shader);

		/// @brief デストラクタ
		virtual ~CoreMaterial() noexcept = default;


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief マテリアルID
		MaterialID			m_id;
		/// @brief マテリアル名
		std::string			m_name;
		/// @brief 半透明フラグ
		bool				m_isTransparent;
		/// @brief ブレンドステート(半透明のみ)
		BlendState			m_blendState;
		/// @brief 深度ステンシルステート
		DepthStencilState	m_depthStencilState;
		/// @brief ラスタライザステート
		RasterizeState		m_rasterizeState;
		/// @brief シェーダID
		ShaderID			m_shaderID;
		/// @brief シェーダータイプ
		ShaderType			m_shaderType;

		/// @brief CBufferデータ
		struct CBuffer
		{
			std::string						name;
			std::unique_ptr<std::byte[]>	data;
			std::size_t						size;
			bool							isUpdate;	///< trueなら更新した
		};

		/// @brief テクスチャデータ
		struct TextureData
		{
			std::string name;
			TextureID	id;
		};

		/// @brief サンプラーデータ
		struct SamplerData
		{
			std::string		name;
			SamplerState	state;
		};

		/// @brief 全ステージ、スロット分のCBufferデータ
		std::array<std::unordered_map<std::uint32_t, CBuffer>,
			static_cast<size_t>(ShaderStage::MAX)>	m_cbufferData;
		/// @brief 全ステージ、スロットのバインドするテクスチャ
		std::array<std::unordered_map<std::uint32_t, TextureData>,
			static_cast<size_t>(ShaderStage::MAX)>	m_textureData;
		/// @brief 全ステージ、スロット分のサンプラステート
		std::array<std::unordered_map<std::uint32_t, SamplerData>,
			static_cast<size_t>(ShaderStage::MAX)>	m_samplerData;

		/// @brief CBuffer変数データ
		std::unordered_map<std::string, CoreShader::CBufferVariable> m_cbufferVariable;

		/// @brief  全ステージ、スロット分のCBufferの数
		std::uint32_t m_cbufferCount;

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief uint設定
		void setUint(const char* name, const unsigned int& data) { setData(name, &data); }

		/// @brief VectorUint2設定
		void setVectorUint2(const char* name, const VectorUint2& data) { setData(name, &data); }

		/// @brief VectorUint3設定
		void setVectorUint3(const char* name, const VectorUint3& data) { setData(name, &data); }

		/// @brief VectorUint4設定
		void setVectorUint4(const char* name, const VectorUint4& data) { setData(name, &data); }

		/// @brief float設定
		void setFloat(const char* name, const float& data) { setData(name, &data); }

		/// @brief Vector2設定
		void setVector2(const char* name, const Vector2& data) { setData(name, &data); }

		/// @brief Vector3設定
		void setVector3(const char* name, const Vector3& data) { setData(name, &data); }

		/// @brief Vector4設定
		void setVector4(const char* name, const Vector4& data) { setData(name, &data); }

		/// @brief Matrix設定
		void setMatrix(const char* name, const Matrix& data) { setData(name, &data); }

		/// @brief Struct設定
		void setStruct(const char* name, const void* data) { setData(name, &data); }

		/// @brief テクスチャ設定
		void setTexture(const char* name, const TextureID textureID);

		/// @brief テクスチャ取得
		TextureID getTexture(const char* name);

		/// @brief サンプラ設定
		void setSampler(const char* name, const SamplerState sampler);

		/// @brief サンプラ取得
		SamplerState GetSampler(const char* name);

		/// @brief データ取得
		void* getData(const char* name);

	protected:
		//------------------------------------------------------------------------------
		// protected methods
		//------------------------------------------------------------------------------

		/// @brief データ設定
		void setData(const char* name, const void* data);

	};
}

#endif // !_CORE_MATERIAL_

