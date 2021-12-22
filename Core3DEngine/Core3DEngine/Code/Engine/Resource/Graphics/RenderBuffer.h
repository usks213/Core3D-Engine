/*****************************************************************//**
 * \file   RenderBuffer.h
 * \brief  描画バッファ(Vertex,Index)
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _RENDER_BUFFER_
#define _RENDER_BUFFER_

#include "MeshInfo.h"
#include <RHI\Core\RHI_ShaderUtil.h>
#include <RHI\Core\RHI_ShaderInputLayout.h>
#include <RHI\Core\RHI_GPUBuffer.h>

namespace Core
{
	/// @class RenderBuffer
	/// @brief レンダーバッファ
	class RenderBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief 頂点データ
		struct VertexData
		{
		public:
			/// @brief コンストラクタ
			/// @param shader シェーダー
			/// @param vertexNum 頂点数
			explicit VertexData(const RHI::ShaderInputLayout& inputLayout, std::size_t vertexNum) :
				size(0), count(vertexNum)
			{
				// 頂点レイアウトコピー
				layout = inputLayout;
				// バッファサイズ計算
				for (auto& var : layout.GetVariableList()) {
					size += var.arrayNum * var.formatWidth;
				}
				// バッファ作成
				buffer = std::make_unique<std::byte[]>(size * count);
				std::memset(buffer.get(), 0, size * count);
			}

			void setPosition(const Vector3& data, const std::uint32_t& index) {
				SetVertexData<Vector3>(RHI::SEMANTIC_NAME::POSITION, 0, data, index);
			}
			void setNormal(const Vector3& data, const std::uint32_t& index) {
				SetVertexData<Vector3>(RHI::SEMANTIC_NAME::NORMAL, 0, data, index);
			}
			void setTangent(const Vector3& data, const std::uint32_t& index) {
				SetVertexData<Vector3>(RHI::SEMANTIC_NAME::TANGENT, 0, data, index);
			}
			void SetBinormal(const Vector3& data, const std::uint32_t& index) {
				SetVertexData<Vector3>(RHI::SEMANTIC_NAME::BINORMAL, 0, data, index);
			}
			void setColor(const Vector4& data, const std::uint32_t& index) {
				SetVertexData<Vector4>(RHI::SEMANTIC_NAME::COLOR, 0, data, index);
			}
			void setTexCoord(const Vector2& data, const std::uint32_t& semanticIndex,
				const std::uint32_t& index) {
				SetVertexData<Vector2>(RHI::SEMANTIC_NAME::TEXCOORD, semanticIndex, data, index);
			}
			void SetBoneWeight(const Vector4& data, const std::uint32_t& index) {
				SetVertexData<Vector4>(RHI::SEMANTIC_NAME::BONE_WEIGHT, 0, data, index);
			}
			void SetBoneIndex(const VectorUint4& data, const std::uint32_t& index) {
				SetVertexData<VectorUint4>(RHI::SEMANTIC_NAME::BONE_INDEX, 0, data, index);
			}

			template<class T>
			void SetVertexData(std::string_view semanticName, const std::uint32_t& semanticIndex,
				const T& data, const std::uint32_t& index) {
				for (auto& var : inputLayoutVariableList) {
					if (var.semanticName == semanticName && var.semanticIndex == semanticIndex) {
						std::memcpy(buffer.get() + size * index + var.offset, &data,
							var.arrayNum * var.formatWidth);
					}
				}
			}

			bool hasVertexVariable(std::string_view semanticName, const std::uint32_t& semanticIndex = 0) {
				for (auto& var : layout.GetVariableList()) {
					if (var.semanticName == semanticName && var.semanticIndex == semanticIndex) {
						return true;
					}
				}
				return false;
			}

		public:

			std::size_t count;						///< 頂点数
			std::size_t size;						///< 一頂点サイズ
			std::unique_ptr<std::byte[]> buffer;	///< 全頂点データ
			RHI::ShaderInputLayout layout;			///< 頂点レイアウト
		};

		/// @brief インデックスデータ
		struct IndexData
		{
			/// @brief コンストラクタ
			/// @param count インデックス数
			/// @param size インデックスサイズ
			IndexData(const std::size_t& count, const std::size_t& size) :
				count(count), size(size)
			{
				// インデックスバッファ作成
				buffer = std::make_unique<std::byte[]>(size * count);
				std::memset(buffer.get(), 0, size * count);
			}
		public:
			std::size_t	count;	///< インデックス数
			std::size_t	size;	///< インデックスサイズ
			std::unique_ptr<std::byte[]> buffer;	///< インデックスデータ
		};

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param inputLayout インプットレイアウト
		/// @param vertexInfo 頂点情報
		/// @param indexInfo インデックス情報
		explicit RenderBuffer(const RHI::ShaderInputLayout& inputLayout, 
			const VertexInfo& vertexInfo, const IndexInfo& indexInfo) :
			m_vertexData(inputLayout, vertexInfo.count),
			m_indexData(indexInfo.count,
				vertexInfo.count <= std::numeric_limits<std::uint16_t>::max() ? 2 : 4)
		{
			// 頂点データの生成
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::POSITION))
				for (std::uint32_t i = 0; i < vertexInfo.positions.size(); ++i) {
					m_vertexData.setPosition(vertexInfo.positions[i], i);
				}
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::NORMAL))
				for (std::uint32_t i = 0; i < vertexInfo.normals.size(); ++i) {
					m_vertexData.setNormal(vertexInfo.normals[i], i);
				}
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::TANGENT))
				for (std::uint32_t i = 0; i < vertexInfo.tangents.size(); ++i) {
					m_vertexData.setTangent(vertexInfo.tangents[i], i);
				}
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::BINORMAL))
				for (std::uint32_t i = 0; i < vertexInfo.binormals.size(); ++i) {
					m_vertexData.SetBinormal(vertexInfo.binormals[i], i);
				}
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::COLOR))
				for (std::uint32_t i = 0; i < vertexInfo.colors.size(); ++i) {
					m_vertexData.setColor(vertexInfo.colors[i], i);
				}
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::TEXCOORD, 0))
				for (std::uint32_t i = 0; i < vertexInfo.texcoord0s.size(); ++i) {
					m_vertexData.setTexCoord(vertexInfo.texcoord0s[i], 0, i);
				}
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::TEXCOORD, 1))
				for (std::uint32_t i = 0; i < vertexInfo.texcoord1s.size(); ++i) {
					m_vertexData.setTexCoord(vertexInfo.texcoord1s[i], 1, i);
				}
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::BONE_WEIGHT))
				for (std::uint32_t i = 0; i < vertexInfo.boneWeights.size(); ++i) {
					m_vertexData.SetBoneWeight(vertexInfo.boneWeights[i], i);
				}
			if (m_vertexData.hasVertexVariable(RHI::SEMANTIC_NAME::BONE_INDEX))
				for (std::uint32_t i = 0; i < vertexInfo.boneIndexes.size(); ++i) {
					m_vertexData.SetBoneIndex(vertexInfo.boneIndexes[i], i);
				}

			// インデックスバッファの生成
			for (std::uint32_t i = 0; i < indexInfo.count; ++i)
			{
				// 怪しいかも？？
				std::memcpy(m_indexData.buffer.get() + m_indexData.size * i, 
					&indexInfo.data[i], m_indexData.size);
			}
		}

		/// @brief デストラクタ
		virtual ~RenderBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		VertexData				m_vertexData;	///< 頂点データ
		IndexData				m_indexData;	///< インデックスデータ

		std::shared_ptr<RHI::GPUBuffer> m_pRHIVertexBuffer;
		std::shared_ptr<RHI::GPUBuffer> m_pRHIIndexBuffer;
	};
}

#endif // !_RENDER_BUFFER_
