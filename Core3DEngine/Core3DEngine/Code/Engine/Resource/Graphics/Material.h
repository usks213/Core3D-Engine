/*****************************************************************//**
 * \file   Material.h
 * \brief  マテリアル
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
	/// @brief マテリアル
	class Material : public Resource
	{
		DECLARE_RESOURCE_INFO(Material);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		Material();

		/// @brief デストラクタ
		~Material() noexcept = default;

		/// @brief シェーダーからマテリアルデータを作成
		/// @param shader グラフィックスシェーダー
		/// @return 成功 TRUE / 失敗 FALSE
		bool CreateMaterialData(const GraphicsShader& shader);

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief 半透明フラグ
		bool					m_isTransparent;
		/// @brief ブレンドステート(半透明のみ)
		RHI::BlendState			m_blendState;
		/// @brief 深度ステンシルステート
		RHI::DepthStencilState	m_depthStencilState;
		/// @brief ラスタライザステート
		RHI::RasterizeState		m_rasterizeState;
		/// @brief シェーダID
		GraphicsShader::ID		m_shaderID;


		/// @brief 全ステージ、スロット分のCBufferデータ
		std::array<std::unordered_map<RHI::Slot, std::shared_ptr<RHI::GPUBuffer>>,
			static_cast<size_t>(RHI::GraphicsShaderStage::MAX)>	m_cbufferData;
		/// @brief 全ステージ、スロット分のテクスチャ
		std::array<std::unordered_map<RHI::Slot, Texture::ID>,
			static_cast<size_t>(RHI::GraphicsShaderStage::MAX)>	m_textureData;
		/// @brief 全ステージ、スロット分のサンプラステート
		std::array<std::unordered_map<RHI::Slot, RHI::SamplerState>,
			static_cast<size_t>(RHI::GraphicsShaderStage::MAX)>	m_samplerData;

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief uint設定
		void setUint(const char* name, const unsigned int& data, 
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief VectorUint2設定
		void SetVectorUint2(const char* name, const VectorUint2& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief VectorUint3設定
		void SetVectorUint3(const char* name, const VectorUint3& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief VectorUint4設定
		void SetVectorUint4(const char* name, const VectorUint4& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief float設定
		void SetFloat(const char* name, const float& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Vector2設定
		void SetVector2(const char* name, const Vector2& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Vector3設定
		void SetVector3(const char* name, const Vector3& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Vector4設定
		void SetVector4(const char* name, const Vector4& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Matrix設定
		void SetMatrix(const char* name, const Matrix& data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief Struct設定
		void SetStruct(const char* name, const void* data,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX) { SetData(name, &data, stage); }

		/// @brief テクスチャ設定
		void SetTexture(const char* name, const Texture::ID textureID,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

		/// @brief テクスチャ取得
		Texture::ID GetTexture(const char* name,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

		/// @brief サンプラ設定
		void SetSampler(const char* name, const RHI::SamplerState sampler,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

		/// @brief サンプラ取得
		RHI::SamplerState GetSampler(const char* name,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

		/// @brief データ取得
		void* GetData(const char* name,
			RHI::GraphicsShaderStage stage = RHI::GraphicsShaderStage::MAX);

	protected:
		//------------------------------------------------------------------------------
		// protected methods
		//------------------------------------------------------------------------------

		/// @brief データ設定
		void SetData(const char* name, const void* data, RHI::GraphicsShaderStage stage);

	};
}

#endif // !_MATERIAL_

