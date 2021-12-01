/*****************************************************************//**
 * \file   Core_RenderBuffer.h
 * \brief  �`��o�b�t�@(Vertex,Index)
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_RENDER_BUFFER_
#define _CORE_RENDER_BUFFER_

#include "Core_Shader.h"
#include "Core_Mesh.h"


namespace core
{
	/// @brief �����_�[�o�b�t�@ID
	enum class RenderBufferID : std::uint32_t {};
	/// @brief ���݂��Ȃ������_�[�o�b�t�@ID
	constexpr RenderBufferID NONE_RENDERBUFFER_ID = std::numeric_limits<RenderBufferID>::max();

	/// @class CoreRenderBuffer
	/// @brief �����_�[�o�b�t�@
	class CoreRenderBuffer
	{
	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		/// @brief ���_�f�[�^
		struct VertexData
		{
		public:
			/// @brief �R���X�g���N�^
			/// @param shader �V�F�[�_�[
			/// @param vertexNum ���_��
			explicit VertexData(const CoreShader& shader, std::size_t vertexNum) :
				size(0), count(vertexNum), shaderID(shader.m_id)
			{
				// ���_���C�A�E�g�R�s�[
				inputLayoutVariableList = shader.m_inputLayoutVariableList;
				// �o�b�t�@�T�C�Y�v�Z
				for (auto& var : inputLayoutVariableList) {
					size += var.arrayNum * var.formatWidth;
				}
				// �o�b�t�@�쐬
				buffer = std::make_unique<std::byte[]>(size * count);
				std::memset(buffer.get(), 0, size * count);
			}

			void setPosition(const Vector3& data, const std::uint32_t& index) {
				setVertexData<Vector3>(SEMANTIC_NAME::POSITION, 0, data, index);
			}
			void setNormal(const Vector3& data, const std::uint32_t& index) {
				setVertexData<Vector3>(SEMANTIC_NAME::NORMAL, 0, data, index);
			}
			void setTangent(const Vector3& data, const std::uint32_t& index) {
				setVertexData<Vector3>(SEMANTIC_NAME::TANGENT, 0, data, index);
			}
			void setBinormal(const Vector3& data, const std::uint32_t& index) {
				setVertexData<Vector3>(SEMANTIC_NAME::BINORMAL, 0, data, index);
			}
			void setColor(const Vector4& data, const std::uint32_t& index) {
				setVertexData<Vector4>(SEMANTIC_NAME::COLOR, 0, data, index);
			}
			void setTexCoord(const Vector2& data, const std::uint32_t& semanticIndex,
				const std::uint32_t& index) {
				setVertexData<Vector2>(SEMANTIC_NAME::TEXCOORD, semanticIndex, data, index);
			}
			void setBoneWeight(const Vector4& data, const std::uint32_t& index) {
				setVertexData<Vector4>(SEMANTIC_NAME::BONE_WEIGHT, 0, data, index);
			}
			void setBoneIndex(const VectorUint4& data, const std::uint32_t& index) {
				setVertexData<VectorUint4>(SEMANTIC_NAME::BONE_INDEX, 0, data, index);
			}

			template<class T>
			void setVertexData(std::string_view semanticName, const std::uint32_t& semanticIndex,
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

			std::size_t count;						// ���_��
			std::size_t size;						// �꒸�_�T�C�Y
			std::unique_ptr<std::byte[]> buffer;	// �S���_�f�[�^
			ShaderID shaderID;
			std::vector<CoreShader::InputLayoutVariable> inputLayoutVariableList;
		};

		/// @brief �C���f�b�N�X�f�[�^
		struct IndexData
		{
			/// @brief �R���X�g���N�^
			/// @param count �C���f�b�N�X��
			/// @param size �C���f�b�N�X�T�C�Y
			IndexData(const std::size_t& count, const std::size_t& size) :
				count(count), size(size)
			{}
		public:
			std::size_t	count;	///< �C���f�b�N�X��
			std::size_t	size;	///< �C���f�b�N�X�T�C�Y
			// �C���f�b�N�X�̃f�[�^�^�C�v? ���͌Œ�
			// IndexDataType
		};

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param id �����_�[�o�b�t�@ID
		/// @param shader �V�F�[�_�[
		/// @param mesh ���b�V��
		explicit CoreRenderBuffer(const RenderBufferID id, const CoreShader& shader, const CoreMesh& mesh) :
			m_id(id),
			m_shaderID(shader.m_id),
			m_meshID(mesh.m_id),
			m_vertexData(shader, mesh.m_vertexCount),
			m_indexData(mesh.m_indexCount, sizeof(std::uint32_t)),
			m_topology(mesh.m_topology)
		{
			// ���_�f�[�^�̐���
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
					m_vertexData.setBinormal(verData.binormals[i], i);
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
					m_vertexData.setBoneWeight(verData.boneWeights[i], i);
				}
			if (m_vertexData.hasVertexVariable(SEMANTIC_NAME::BONE_INDEX))
				for (std::uint32_t i = 0; i < verData.boneIndexes.size(); ++i) {
					m_vertexData.setBoneIndex(verData.boneIndexes[i], i);
				}
		}

		/// @brief �f�X�g���N�^
		virtual ~CoreRenderBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		RenderBufferID		m_id;			///< �����_�[�o�b�t�@ID
		ShaderID			m_shaderID;		///< �V�F�[�_�[ID
		MeshID				m_meshID;		///< ���b�V��ID

		VertexData			m_vertexData;	///< ���_�f�[�^
		IndexData			m_indexData;	///< �C���f�b�N�X�f�[�^
		PrimitiveTopology	m_topology;		///< �v���~�e�B�u�g�|���W�[
	};
}

#endif // !_CORE_RENDER_BUFFER_
