/*****************************************************************//**
 * \file   RenderBuffer.h
 * \brief  描画バッファ(Vertex,Index)
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_RENDER_BUFFER_
#define _CORE_RENDER_BUFFER_

#include "Shader.h"
#include "Mesh.h"


namespace Core
{
	/// @brief レンダーバッファID
	enum class RenderBufferID : std::uint32_t {};
	/// @brief 存在しないレンダーバッファID
	constexpr RenderBufferID NONE_RENDERBUFFER_ID = std::numeric_limits<RenderBufferID>::max();

	/// @class CoreRenderBuffer
	/// @brief レンダーバッファ
	class CoreRenderBuffer
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
			explicit VertexData(const CoreShader& shader, std::size_t vertexNum) :
				size(0), count(vertexNum), shaderID(shader.m_id)
			{
				// 頂点レイアウトコピー
				inputLayoutVariableList = shader.m_inputLayoutVariableList;
				// バッファサイズ計算
				for (auto& var : inputLayoutVariableList) {
					size += var.arrayNum * var.formatWidth;
				}
				// バッファ作成
				buffer = std::make_unique<std::byte[]>(size * count);
				std::memset(buffer.get(), 0, size * count);
			}

			void setPosition(const Vector3& data, const std::uint32_t& index) {
				SetVertexData<Vector3>(SEMANTIC_NAME::POSITION, 0, data, index);
			}
			void setNormal(const Vector3& data, const std::uint32_t& index) {
				SetVertexData<Vector3>(SEMANTIC_NAME::NORMAL, 0, data, index);
			}
			void setTangent(const Vector3& data, const std::uint32_t& index) {
				SetVertexData<Vector3>(SEMANTIC_NAME::TANGENT, 0, data, index);
			}
			void SetBinormal(const Vector3& data, const std::uint32_t& index) {
				SetVertexData<Vector3>(SEMANTIC_NAME::BINORMAL, 0, data, index);
			}
			void setColor(const Vector4& data, const std::uint32_t& index) {
				SetVertexData<Vector4>(SEMANTIC_NAME::COLOR, 0, data, index);
			}
			void setTexCoord(const Vector2& data, const std::uint32_t& semanticIndex,
				const std::uint32_t& index) {
				SetVertexData<Vector2>(SEMANTIC_NAME::TEXCOORD, semanticIndex, data, index);
			}
			void SetBoneWeight(const Vector4& data, const std::uint32_t& index) {
				SetVertexData<Vector4>(SEMANTIC_NAME::BONE_WEIGHT, 0, data, index);
			}
			void SetBoneIndex(const VectorUint4& data, const std::uint32_t& index) {
				SetVertexData<VectorUint4>(SEMANTIC_NAME::BONE_INDEX, 0, data, index);
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
				for (auto& var : inputLayoutVariableList) {
					if (var.semanticName == semanticName && var.semanticIndex == semanticIndex) {
						return true;
					}
				}
				return false;
			}

		public:

			std::size_t count;						// 頂点数
			std::size_t size;						// 一頂点サイズ
			std::unique_ptr<std::byte[]> buffer;	// 全頂点データ
			ShaderID shaderID;
			std::vector<CoreShader::InputLayoutVariable> inputLayoutVariableList;
		};

		/// @brief インデックスデータ
		struct IndexData
		{
			/// @brief コンストラクタ
			/// @param count インデックス数
			/// @param size インデックスサイズ
			IndexData(const std::size_t& count, const std::size_t& size) :
				count(count), size(size)
			{}
		public:
			std::size_t	count;	///< インデックス数
			std::size_t	size;	///< インデックスサイズ
			// インデックスのデータタイプ? 今は固定
			// IndexDataType
		};

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param id レンダーバッファID
		/// @param shader シェーダー
		/// @param mesh メッシュ
		explicit CoreRenderBuffer(const RenderBufferID id, const CoreShader& shader, const CoreMesh& mesh) :
			m_id(id),
			m_shaderID(shader.m_id),
			m_meshID(mesh.m_id),
			m_vertexData(shader, mesh.m_vertexCount),
			m_indexData(mesh.m_indexCount, sizeof(std::uint32_t)),
			m_topology(mesh.m_topology)
		{
			// 頂点データの生成
			const auto& verData = mesh.m_vertexData;
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::POSITION))
				for (std::uint32_t i = 0; i < verData.positions.size(); ++i) {
					m_vertexData.setPosition(verData.positions[i], i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::NORMAL))
				for (std::uint32_t i = 0; i < verData.normals.size(); ++i) {
					m_vertexData.setNormal(verData.normals[i], i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::TANGENT))
				for (std::uint32_t i = 0; i < verData.tangents.size(); ++i) {
					m_vertexData.setTangent(verData.tangents[i], i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::BINORMAL))
				for (std::uint32_t i = 0; i < verData.binormals.size(); ++i) {
					m_vertexData.SetBinormal(verData.binormals[i], i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::COLOR))
				for (std::uint32_t i = 0; i < verData.colors.size(); ++i) {
					m_vertexData.setColor(verData.colors[i], i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::TEXCOORD, 0))
				for (std::uint32_t i = 0; i < verData.texcoord0s.size(); ++i) {
					m_vertexData.setTexCoord(verData.texcoord0s[i], 0, i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::TEXCOORD, 1))
				for (std::uint32_t i = 0; i < verData.texcoord1s.size(); ++i) {
					m_vertexData.setTexCoord(verData.texcoord1s[i], 1, i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::BONE_WEIGHT))
				for (std::uint32_t i = 0; i < verData.boneWeights.size(); ++i) {
					m_vertexData.SetBoneWeight(verData.boneWeights[i], i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::BONE_INDEX))
				for (std::uint32_t i = 0; i < verData.boneIndexes.size(); ++i) {
					m_vertexData.SetBoneIndex(verData.boneIndexes[i], i);
				}
		}

		/// @brief デストラクタ
		virtual ~CoreRenderBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		RenderBufferID		m_id;			///< レンダーバッファID
		ShaderID			m_shaderID;		///< シェーダーID
		MeshID				m_meshID;		///< メッシュID

		VertexData			m_vertexData;	///< 頂点データ
		IndexData			m_indexData;	///< インデックスデータ
		PrimitiveTopology	m_topology;		///< プリミティブトポロジー
	};
}

#endif // !_CORE_RENDER_BUFFER_
