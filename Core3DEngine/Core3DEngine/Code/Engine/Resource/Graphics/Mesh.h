/*****************************************************************//**
 * \file   Mesh.h
 * \brief  メッシュクラス
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
	/// @brief メッシュ
	class Mesh : public Resource
	{
		DECLARE_RESOURCE_INFO(Mesh);
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit Mesh() :
			m_topology(RHI::PrimitiveTopology::TRIANGLE_STRIP)
		{}

		/// @brief デストラクタ
		~Mesh() noexcept = default;

	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------

		VertexInfo					m_vertex;			///< 頂点情報
		IndexInfo					m_index;			///< インデックス情報
		BoneInfo					m_bone;				///< ボーン情報
		SubMeshInfo					m_subMesh;			///< サブメッシュ情報
		AABB						m_aabb;				///< AABB
		RHI::PrimitiveTopology		m_topology;			///< プリミティブトポロジー
	};
}

#endif // !_MESH_
