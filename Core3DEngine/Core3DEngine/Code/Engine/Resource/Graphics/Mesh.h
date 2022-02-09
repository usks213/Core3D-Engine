/*****************************************************************//**
 * \file   Mesh.h
 * \brief  ���b�V���N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _MESH_
#define _MESH_

#include <Resource\Core\Resource.h>
#include <RHI\Core\RHI_CommonState.h>
#include "MeshInfo.h"

#include "GraphicsShader.h"
#include "RenderBuffer.h"

namespace Core
{
	/// @class Mesh
	/// @brief ���b�V��
	class Mesh : public Resource
	{
		DECLARE_RESOURCE_INFO(Mesh);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		explicit Mesh() :
			m_topology(RHI::PrimitiveTopology::TRIANGLE_STRIP)
		{}

		/// @brief �f�X�g���N�^
		~Mesh() noexcept = default;

		/// @brief �V�F�[�_�[�ɑΉ����郌���_�[�o�b�t�@�̎擾
		/// @param shaderID �O���t�B�b�N�X�V�F�[�_�[ID
		/// @return �����_�[�o�b�t�@�Q��
		std::shared_ptr<RenderBuffer> GetRenderBuffer(const GraphicsShader::ID& shaderID);

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		VertexInfo					m_vertex;			///< ���_���
		IndexInfo					m_index;			///< �C���f�b�N�X���
		BoneInfo					m_bone;				///< �{�[�����
		SubMeshInfo					m_subMesh;			///< �T�u���b�V�����
		AABB						m_aabb;				///< AABB
		RHI::PrimitiveTopology		m_topology;			///< �v���~�e�B�u�g�|���W�[

		std::unordered_map<GraphicsShader::ID, std::shared_ptr<RenderBuffer>> m_renderBuffers;
	};
}

#endif // !_MESH_
