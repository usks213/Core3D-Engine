/*****************************************************************//**
 * \file   Mesh.h
 * \brief  メッシュ情報
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
		std::uint32_t		 count = 0;			///< 頂点数
		std::vector<Vector3> positions;			///< 座標
		std::vector<Vector3> normals;			///< 法線
		std::vector<Vector3> tangents;			///< 接線
		std::vector<Vector3> binormals;			///< 従法線
		std::vector<Vector4> colors;			///< 色
		std::vector<Vector2> texcoord0s;		///< テクスチャ座標0
		std::vector<Vector2> texcoord1s;		///< テクスチャ座標1
		std::vector<Vector4> boneWeights;		///< ボーンの重み
		std::vector<VectorUint4> boneIndexes;	///< ボーンのインデックス
	};

	struct IndexInfo
	{
		std::uint32_t				count = 0;	///< インデックス数
		std::vector<std::uint32_t>  data;		///< インデックスデータ
	};

	struct BoneInfo
	{
		std::uint32_t									count = 0;		///< ボーン数
		std::vector<Matrix>								invMatrixData;	///< 逆行列データ
		std::vector<Matrix>								calcBoneBuffer;	///< ボーンデータ
		std::unordered_map<std::string, std::uint32_t>	indexTable;		///< インデックステーブル
	};

	struct SubMeshInfo
	{
		struct Data
		{
			std::uint32_t start = 0;	///< 頂点orインデックスの開始位置
			std::uint32_t count = 0;	///< 頂点orインデックスの数
		};

		std::uint32_t		count = 0;	///< サブメッシュ数
		std::vector<Data>	data;		///< サブメッシュデータ
	};
}

#endif // !_MESH_INFO_

