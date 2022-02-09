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

#include "GraphicsShader.h"
#include "RenderBuffer.h"

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

		/// @brief シェーダーに対応するレンダーバッファの取得
		/// @param shaderID グラフィックスシェーダーID
		/// @return レンダーバッファ参照
		std::shared_ptr<RenderBuffer> GetRenderBuffer(const GraphicsShader::ID& shaderID);

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

		std::unordered_map<GraphicsShader::ID, std::shared_ptr<RenderBuffer>> m_renderBuffers;
	};
}

#endif // !_MESH_
