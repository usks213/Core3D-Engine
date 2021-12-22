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
	};
}

#endif // !_MESH_
