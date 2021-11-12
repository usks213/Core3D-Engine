/*****************************************************************//**
 * \file   Core_Mesh.h
 * \brief  ���b�V���N���X
 * 
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#ifndef _CORE_MESH_
#define _CORE_MESH_

#include <vector>
#include <unordered_map>
#include <string>
#include "Core_CommonState.h"
#include <CoreSystem\Utils\Util_Mathf.h>

namespace core
{
	/// @brief ���b�V��ID
	enum class MeshID : std::uint32_t {};
	/// @brief ���݂��Ȃ����b�V��ID
	constexpr MeshID NONE_MESH_ID = std::numeric_limits<MeshID>::max();

	/// @class CoreMesh
	/// @brief ���b�V��
	class CoreMesh
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief �R���X�g���N�^
		/// @param id ���b�V��ID
		/// @param name ���b�V����
		explicit CoreMesh(const MeshID& id, const std::string& name) :
			m_id(id),
			m_name(name),
			m_vertexCount(0),
			m_indexCount(0),
			m_boneCount(0),
			m_topology(PrimitiveTopology::TRIANGLE_STRIP)
		{}

		/// @brief �f�X�g���N�^
		~CoreMesh() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		struct VertexInfo
		{
			std::vector<Vector3> positions;			///< ���W
			std::vector<Vector3> normals;			///< �@��
			std::vector<Vector3> tangents;			///< �ڐ�
			std::vector<Vector3> binormals;			///< �]�@��
			std::vector<Vector4> colors;			///< �F
			std::vector<Vector2> texcoord0s;		///< �e�N�X�`�����W0
			std::vector<Vector2> texcoord1s;		///< �e�N�X�`�����W1
			std::vector<Vector4> boneWeights;		///< �{�[���̏d��
			std::vector<VectorUint4> boneIndexes;	///< �{�[���̃C���f�b�N�X
		};
		struct SubMesh
		{
			std::uint32_t start = 0;				///< ���_or�C���f�b�N�X�̊J�n�ʒu
			std::uint32_t count = 0;				///< ���_or�C���f�b�N�X�̐�
		};

		MeshID						m_id;				///< ���b�V��ID
		std::string					m_name;				///< ���b�V����
		std::vector<SubMesh>		m_subMeshes;		///< �T�u���b�V����

		std::uint32_t				m_vertexCount;		///< ���_��
		VertexInfo					m_vertexData;		///< ���_�f�[�^
		std::uint32_t				m_indexCount;		///< �C���f�b�N�X��
		std::vector<std::uint32_t>  m_indexData;		///< �C���f�b�N�X�f�[�^

		std::uint32_t				m_boneCount;		///< �{�[����
		std::vector<Matrix>			m_invMatrixData;	///< �t�s��f�[�^
		std::vector<Matrix>			m_calcBoneBuffer;	///< �{�[���f�[�^
		std::unordered_map<std::string, std::uint32_t>	m_boneTabel;	///< �{�[���f�[�u��

		AABB						m_aabb;				///< AABB
		PrimitiveTopology			m_topology;			///< �v���~�e�B�u�g�|���W�[
	};
}

#endif // !_CORE_MESH_
