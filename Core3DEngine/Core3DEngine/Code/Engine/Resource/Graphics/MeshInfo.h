/*****************************************************************//**
 * \file   Mesh.h
 * \brief  ���b�V�����
 *
 * \author USAMI KOSHI
 * \date   2021/12/23
 *********************************************************************/
#ifndef _MESH_INFO_
#define _MESH_INFO_

#include <Utils/Util_Mathf.h>
#include <vector>
#include <unordered_map>

namespace Core
{
	struct VertexInfo
	{
		std::uint32_t		 count = 0;			///< ���_��
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

	struct IndexInfo
	{
		std::uint32_t				count = 0;	///< �C���f�b�N�X��
		std::vector<std::uint32_t>  data;		///< �C���f�b�N�X�f�[�^
	};

	struct BoneInfo
	{
		std::uint32_t									count = 0;		///< �{�[����
		std::vector<Matrix>								invMatrixData;	///< �t�s��f�[�^
		std::vector<Matrix>								calcBoneBuffer;	///< �{�[���f�[�^
		std::unordered_map<std::string, std::uint32_t>	indexTable;		///< �C���f�b�N�X�e�[�u��
	};

	struct SubMeshInfo
	{
		struct Data
		{
			std::uint32_t start = 0;	///< ���_or�C���f�b�N�X�̊J�n�ʒu
			std::uint32_t count = 0;	///< ���_or�C���f�b�N�X�̐�
		};

		std::uint32_t		count = 0;	///< �T�u���b�V����
		std::vector<Data>	data;		///< �T�u���b�V���f�[�^
	};
}

#endif // !_MESH_INFO_

