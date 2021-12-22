/*****************************************************************//**
 * \file   RenderBuffer.h
 * \brief  �`��o�b�t�@(Vertex,Index)
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
	/// @brief �����_�[�o�b�t�@
	class RenderBuffer
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
			explicit VertexData(const RHI::ShaderInputLayout& inputLayout, std::size_t vertexNum) :
				size(0), count(vertexNum)
			{
				// ���_���C�A�E�g�R�s�[
				layout = inputLayout;
				// �o�b�t�@�T�C�Y�v�Z
				for (auto& var : layout.GetVariableList()) {
					size += var.arrayNum * var.formatWidth;
				}
				// �o�b�t�@�쐬
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

			std::size_t count;						///< ���_��
			std::size_t size;						///< �꒸�_�T�C�Y
			std::unique_ptr<std::byte[]> buffer;	///< �S���_�f�[�^
			RHI::ShaderInputLayout layout;			///< ���_���C�A�E�g
		};

		/// @brief �C���f�b�N�X�f�[�^
		struct IndexData
		{
			/// @brief �R���X�g���N�^
			/// @param count �C���f�b�N�X��
			/// @param size �C���f�b�N�X�T�C�Y
			IndexData(const std::size_t& count, const std::size_t& size) :
				count(count), size(size)
			{
				// �C���f�b�N�X�o�b�t�@�쐬
				buffer = std::make_unique<std::byte[]>(size * count);
				std::memset(buffer.get(), 0, size * count);
			}
		public:
			std::size_t	count;	///< �C���f�b�N�X��
			std::size_t	size;	///< �C���f�b�N�X�T�C�Y
			std::unique_ptr<std::byte[]> buffer;	///< �C���f�b�N�X�f�[�^
		};

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param inputLayout �C���v�b�g���C�A�E�g
		/// @param vertexInfo ���_���
		/// @param indexInfo �C���f�b�N�X���
		explicit RenderBuffer(const RHI::ShaderInputLayout& inputLayout, 
			const VertexInfo& vertexInfo, const IndexInfo& indexInfo) :
			m_vertexData(inputLayout, vertexInfo.count),
			m_indexData(indexInfo.count,
				vertexInfo.count <= std::numeric_limits<std::uint16_t>::max() ? 2 : 4)
		{
			// ���_�f�[�^�̐���
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

			// �C���f�b�N�X�o�b�t�@�̐���
			for (std::uint32_t i = 0; i < indexInfo.count; ++i)
			{
				// �����������H�H
				std::memcpy(m_indexData.buffer.get() + m_indexData.size * i, 
					&indexInfo.data[i], m_indexData.size);
			}
		}

		/// @brief �f�X�g���N�^
		virtual ~RenderBuffer() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		VertexData				m_vertexData;	///< ���_�f�[�^
		IndexData				m_indexData;	///< �C���f�b�N�X�f�[�^

		std::shared_ptr<RHI::GPUBuffer> m_pRHIVertexBuffer;
		std::shared_ptr<RHI::GPUBuffer> m_pRHIIndexBuffer;
	};
}

#endif // !_RENDER_BUFFER_
