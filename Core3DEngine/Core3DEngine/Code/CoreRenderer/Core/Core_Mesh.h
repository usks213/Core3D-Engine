/*****************************************************************//**
 * \file   Core_Mesh.h
 * \brief  メッシュクラス
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
	/// @brief メッシュID
	enum class MeshID : std::uint32_t {};
	/// @brief 存在しないメッシュID
	constexpr MeshID NONE_MESH_ID = std::numeric_limits<MeshID>::max();

	/// @class CoreMesh
	/// @brief メッシュ
	class CoreMesh
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param id メッシュID
		/// @param name メッシュ名
		explicit CoreMesh(const MeshID& id, const std::string& name) :
			m_id(id),
			m_name(name),
			m_vertexCount(0),
			m_indexCount(0),
			m_boneCount(0),
			m_topology(PrimitiveTopology::TRIANGLE_STRIP)
		{}

		/// @brief デストラクタ
		~CoreMesh() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		struct VertexInfo
		{
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
		struct SubMesh
		{
			std::uint32_t start = 0;				///< 頂点orインデックスの開始位置
			std::uint32_t count = 0;				///< 頂点orインデックスの数
		};

		MeshID						m_id;				///< メッシュID
		std::string					m_name;				///< メッシュ名
		std::vector<SubMesh>		m_subMeshes;		///< サブメッシュ数

		std::uint32_t				m_vertexCount;		///< 頂点数
		VertexInfo					m_vertexData;		///< 頂点データ
		std::uint32_t				m_indexCount;		///< インデックス数
		std::vector<std::uint32_t>  m_indexData;		///< インデックスデータ

		std::uint32_t				m_boneCount;		///< ボーン数
		std::vector<Matrix>			m_invMatrixData;	///< 逆行列データ
		std::vector<Matrix>			m_calcBoneBuffer;	///< ボーンデータ
		std::unordered_map<std::string, std::uint32_t>	m_boneTabel;	///< ボーンデーブル

		AABB						m_aabb;				///< AABB
		PrimitiveTopology			m_topology;			///< プリミティブトポロジー
	};
}

#endif // !_CORE_MESH_
