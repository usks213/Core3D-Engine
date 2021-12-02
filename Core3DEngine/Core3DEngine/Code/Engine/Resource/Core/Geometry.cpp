/*****************************************************************//**
 * \file   Geometry.cpp
 * \brief  ジオメトリ
 * 
 * \author USAMI KOSHI
 * \date   2021/07/03
 *********************************************************************/

#include "Geometry.h"

struct VERTEX_3D 
{
	Vector3 vtx;		// 頂点座標
	Vector3 nor;		// 法線ベクトル
	Vector4 diffuse;	// 拡散反射光
	Vector2 tex;		// テクスチャ座標
};

void Geometry::Quad(Core::CoreMesh& out)
{
	const float	SIZE_X = (0.5f); // 立方体のサイズ(X方向)
	const float	SIZE_Y = (0.5f); // 立方体のサイズ(Y方向)
	const float	SIZE_Z = (0.5f); // 立方体のサイズ(Z方向)

	const std::uint32_t QUAD_VERTEX = (4);

	// プリミティブ設定
	out.m_topology = Core::PrimitiveTopology::TRIANGLE_STRIP;

	VERTEX_3D	vertexWk[QUAD_VERTEX];	// 頂点情報格納ワーク

	// 頂点座標の設定
	// 前
	vertexWk[0].vtx = Vector3(-SIZE_X, SIZE_Y, -SIZE_Z);
	vertexWk[1].vtx = Vector3(SIZE_X, SIZE_Y, -SIZE_Z);
	vertexWk[2].vtx = Vector3(-SIZE_X, -SIZE_Y, -SIZE_Z);
	vertexWk[3].vtx = Vector3(SIZE_X, -SIZE_Y, -SIZE_Z);
	
	// 法線ベクトルの設定
	// 前
	vertexWk[0].nor = Vector3(0.0f, 0.0f, -1.0f);
	vertexWk[1].nor = Vector3(0.0f, 0.0f, -1.0f);
	vertexWk[2].nor = Vector3(0.0f, 0.0f, -1.0f);
	vertexWk[3].nor = Vector3(0.0f, 0.0f, -1.0f);

	// 拡散反射光の設定
	for (std::uint32_t i = 0; i < QUAD_VERTEX; i++)
	{
		vertexWk[i].diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// テクスチャ座標の設定
	for (std::uint32_t i = 0; i < QUAD_VERTEX; i += 4)
	{
		vertexWk[0 + i].tex = Vector2(0.0f, 0.0f);
		vertexWk[1 + i].tex = Vector2(1.0f, 0.0f);
		vertexWk[2 + i].tex = Vector2(0.0f, 1.0f);
		vertexWk[3 + i].tex = Vector2(1.0f, 1.0f);
	}

	// 頂点生成
	out.m_vertexCount = QUAD_VERTEX;
	for (std::uint32_t i = 0; i < out.m_vertexCount; ++i)
	{
		out.m_vertexData.positions.push_back(vertexWk[i].vtx);
		out.m_vertexData.normals.push_back(vertexWk[i].nor);
		out.m_vertexData.texcoord0s.push_back(vertexWk[i].tex);
		out.m_vertexData.colors.push_back(vertexWk[i].diffuse);
	}

	// インデックス
	out.m_indexCount = 0;
}

void Geometry::Plane(Core::CoreMesh& out, int split, float size, float texSize)
{
	int nNumBlockX = split;
	int nNumBlockZ = split;
	float fSizeBlockX = -size;
	float fSizeBlockZ = size;
	float fTexSizeX = texSize;
	float fTexSizeZ = texSize;

	// プリミティブ種別設定
	out.m_topology = Core::PrimitiveTopology::TRIANGLE_STRIP;
	// 頂点数の設定
	out.m_vertexCount = (nNumBlockX + 1) * (nNumBlockZ + 1);
	// インデックス数の設定(縮退ポリゴン用を考慮する)
	out.m_indexCount = (nNumBlockX + 1) * 2 * nNumBlockZ + (nNumBlockZ - 1) * 2;
	// 頂点配列の作成
	VERTEX_3D* pVertexWk = new VERTEX_3D[out.m_vertexCount];
	// インデックス配列の作成
	int* pIndexWk = new int[out.m_indexCount];
	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;


	for (int z = 0; z < nNumBlockZ + 1; ++z) {
		for (int x = 0; x < nNumBlockX + 1; ++x) {

			// 頂点座標の設定
			pVtx->vtx.x = x * fSizeBlockX - (nNumBlockX * 0.5f) * fSizeBlockX;
			pVtx->vtx.y = 0.0f;
			pVtx->vtx.z = -z * fSizeBlockZ + (nNumBlockZ * 0.5f) * fSizeBlockZ;
			// 法線の設定
			pVtx->nor = Vector3(0.0f, 1.0f, 0.0f);
			// 反射光の設定
			pVtx->diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標の設定
			pVtx->tex.x = fTexSizeX * x;
			pVtx->tex.y = fTexSizeZ * z;
			++pVtx;
		}
	}
	//インデックス配列の中身を埋める
	int* pIdx = pIndexWk;
	for (int z = 0; z < nNumBlockZ; ++z) {
		if (z > 0) {
			// 縮退ポリゴンのためのダブりの設定
			*pIdx++ = (z + 1) * (nNumBlockX + 1);
		}
		for (int x = 0; x < nNumBlockX + 1; ++x) {
			*pIdx++ = (z + 1) * (nNumBlockX + 1) + x;
			*pIdx++ = z * (nNumBlockX + 1) + x;
		}
		if (z < nNumBlockZ - 1) {
			// 縮退ポリゴンのためのダブりの設定
			*pIdx++ = z * (nNumBlockX + 1) + nNumBlockX;
		}
	}

	// 頂点生成
	for (auto i = 0u; i < out.m_vertexCount; ++i)
	{
		out.m_vertexData.positions.push_back(pVertexWk[i].vtx);
		out.m_vertexData.normals.push_back(pVertexWk[i].nor);
		out.m_vertexData.texcoord0s.push_back(pVertexWk[i].tex);
		out.m_vertexData.colors.push_back(pVertexWk[i].diffuse);
	}

	// インデックス
	for (auto i = 0; i < out.m_indexCount; ++i)
	{
		out.m_indexData.push_back(pIndexWk[i]);
	}

	// 一時配列の解放
	delete[] pVertexWk;
	delete[] pIndexWk;
}

void Geometry::Cube(Core::CoreMesh& out)
{
	const float	SIZE_X = (0.5f); // 立方体のサイズ(X方向)
	const float	SIZE_Y = (0.5f); // 立方体のサイズ(Y方向)
	const float	SIZE_Z = (0.5f); // 立方体のサイズ(Z方向)

	const std::uint32_t CUBE_VERTEX = (24);
	const std::uint32_t CUBE_INDEX = (36);

	// プリミティブ設定
	out.m_topology = Core::PrimitiveTopology::TRIANGLE_LIST;

	VERTEX_3D	vertexWk[CUBE_VERTEX];	// 頂点情報格納ワーク
	std::uint32_t			indexWk[CUBE_INDEX];	// インデックス格納ワーク

	// 頂点座標の設定
	// 前
	vertexWk[0].vtx = Vector3(-SIZE_X, SIZE_Y, -SIZE_Z);
	vertexWk[1].vtx = Vector3(SIZE_X, SIZE_Y, -SIZE_Z);
	vertexWk[2].vtx = Vector3(-SIZE_X, -SIZE_Y, -SIZE_Z);
	vertexWk[3].vtx = Vector3(SIZE_X, -SIZE_Y, -SIZE_Z);
	// 右
	vertexWk[4].vtx = Vector3(SIZE_X, SIZE_Y, -SIZE_Z);
	vertexWk[5].vtx = Vector3(SIZE_X, SIZE_Y, SIZE_Z);
	vertexWk[6].vtx = Vector3(SIZE_X, -SIZE_Y, -SIZE_Z);
	vertexWk[7].vtx = Vector3(SIZE_X, -SIZE_Y, SIZE_Z);
	// 上
	vertexWk[8].vtx = Vector3(-SIZE_X, SIZE_Y, SIZE_Z);
	vertexWk[9].vtx = Vector3(SIZE_X, SIZE_Y, SIZE_Z);
	vertexWk[10].vtx = Vector3(-SIZE_X, SIZE_Y, -SIZE_Z);
	vertexWk[11].vtx = Vector3(SIZE_X, SIZE_Y, -SIZE_Z);
	// 後
	vertexWk[12].vtx = Vector3(SIZE_X, SIZE_Y, SIZE_Z);
	vertexWk[13].vtx = Vector3(-SIZE_X, SIZE_Y, SIZE_Z);
	vertexWk[14].vtx = Vector3(SIZE_X, -SIZE_Y, SIZE_Z);
	vertexWk[15].vtx = Vector3(-SIZE_X, -SIZE_Y, SIZE_Z);
	// 左
	vertexWk[16].vtx = Vector3(-SIZE_X, SIZE_Y, SIZE_Z);
	vertexWk[17].vtx = Vector3(-SIZE_X, SIZE_Y, -SIZE_Z);
	vertexWk[18].vtx = Vector3(-SIZE_X, -SIZE_Y, SIZE_Z);
	vertexWk[19].vtx = Vector3(-SIZE_X, -SIZE_Y, -SIZE_Z);
	// 下
	vertexWk[20].vtx = Vector3(SIZE_X, -SIZE_Y, SIZE_Z);
	vertexWk[21].vtx = Vector3(-SIZE_X, -SIZE_Y, SIZE_Z);
	vertexWk[22].vtx = Vector3(SIZE_X, -SIZE_Y, -SIZE_Z);
	vertexWk[23].vtx = Vector3(-SIZE_X, -SIZE_Y, -SIZE_Z);


	// 法線ベクトルの設定
	// 前
	vertexWk[0].nor = Vector3(0.0f, 0.0f, -1.0f);
	vertexWk[1].nor = Vector3(0.0f, 0.0f, -1.0f);
	vertexWk[2].nor = Vector3(0.0f, 0.0f, -1.0f);
	vertexWk[3].nor = Vector3(0.0f, 0.0f, -1.0f);
	// 右
	vertexWk[4].nor = Vector3(1.0f, 0.0f, 0.0f);
	vertexWk[5].nor = Vector3(1.0f, 0.0f, 0.0f);
	vertexWk[6].nor = Vector3(1.0f, 0.0f, 0.0f);
	vertexWk[7].nor = Vector3(1.0f, 0.0f, 0.0f);
	// 上
	vertexWk[8].nor = Vector3(0.0f, 1.0f, 0.0f);
	vertexWk[9].nor = Vector3(0.0f, 1.0f, 0.0f);
	vertexWk[10].nor = Vector3(0.0f, 1.0f, 0.0f);
	vertexWk[11].nor = Vector3(0.0f, 1.0f, 0.0f);
	// 後
	vertexWk[12].nor = Vector3(0.0f, 0.0f, 1.0f);
	vertexWk[13].nor = Vector3(0.0f, 0.0f, 1.0f);
	vertexWk[14].nor = Vector3(0.0f, 0.0f, 1.0f);
	vertexWk[15].nor = Vector3(0.0f, 0.0f, 1.0f);
	// 左
	vertexWk[16].nor = Vector3(-1.0f, 0.0f, 0.0f);
	vertexWk[17].nor = Vector3(-1.0f, 0.0f, 0.0f);
	vertexWk[18].nor = Vector3(-1.0f, 0.0f, 0.0f);
	vertexWk[19].nor = Vector3(-1.0f, 0.0f, 0.0f);
	// 下
	vertexWk[20].nor = Vector3(0.0f, -1.0f, 0.0f);
	vertexWk[21].nor = Vector3(0.0f, -1.0f, 0.0f);
	vertexWk[22].nor = Vector3(0.0f, -1.0f, 0.0f);
	vertexWk[23].nor = Vector3(0.0f, -1.0f, 0.0f);


	// 拡散反射光の設定
	for (std::uint32_t i = 0; i < CUBE_VERTEX; i++)
	{
		vertexWk[i].diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// テクスチャ座標の設定
	for (std::uint32_t i = 0; i < CUBE_VERTEX; i += 4)
	{
		vertexWk[0 + i].tex = Vector2(0.0f, 0.0f);
		vertexWk[1 + i].tex = Vector2(1.0f, 0.0f);
		vertexWk[2 + i].tex = Vector2(0.0f, 1.0f);
		vertexWk[3 + i].tex = Vector2(1.0f, 1.0f);
	}

	// インデックス配列の設定
	for (std::uint32_t i = 0, j = 0; i < CUBE_INDEX; i += 6, j += 4)
	{
		indexWk[0 + i] = 0 + j;
		indexWk[1 + i] = 1 + j;
		indexWk[2 + i] = 2 + j;
		indexWk[3 + i] = 2 + j;
		indexWk[4 + i] = 1 + j;
		indexWk[5 + i] = 3 + j;
	}

	// 頂点生成
	out.m_vertexCount = CUBE_VERTEX;
	for (std::uint32_t i = 0; i < out.m_vertexCount; ++i)
	{
		out.m_vertexData.positions.push_back(vertexWk[i].vtx);
		out.m_vertexData.normals.push_back(vertexWk[i].nor);
		out.m_vertexData.texcoord0s.push_back(vertexWk[i].tex);
		out.m_vertexData.colors.push_back(vertexWk[i].diffuse);
	}

	// インデックス
	out.m_indexCount = CUBE_INDEX;
	for (std::uint32_t i = 0; i < out.m_indexCount; ++i)
	{
		out.m_indexData.push_back(static_cast<std::uint32_t>(indexWk[i]));
	}
}

void Geometry::Sphere(Core::CoreMesh& out, int nSplit, float fSize, float fTexSize)
{
	float nNumBlockX = nSplit;
	float nNumBlockY = nSplit;

	// プリミティブ種別設定
	out.m_topology = Core::PrimitiveTopology::TRIANGLE_STRIP;
	// 頂点数の設定
	std::uint32_t nNumVertex = (nNumBlockX + 1) * (nNumBlockY + 1);
	// インデックス数の設定(縮退ポリゴン用を考慮する)
	std::uint32_t nNumIndex = (nNumBlockX + 1) * 2 * nNumBlockY + (nNumBlockY - 1) * 2;
	// 頂点配列の作成
	VERTEX_3D* pVertexWk = new VERTEX_3D[nNumVertex];
	// インデックス配列の作成
	std::uint32_t* pIndexWk = new std::uint32_t[nNumIndex];
	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;

	for (std::uint32_t y = 0; y < nNumBlockY + 1; ++y) {
		for (std::uint32_t x = 0; x < nNumBlockX + 1; ++x) {

			// 頂点座標の設定
			pVtx->vtx.x = 0.0f;
			pVtx->vtx.y = 1.0f;
			pVtx->vtx.z = 0.0f;
			// 角度に対する回転マトリックスを求める
			Matrix mR = Matrix::CreateRotationX(Mathf::ToRadians(x * (180.0f / nNumBlockX)));
			mR *= Matrix::CreateRotationY(Mathf::ToRadians(y * -(360.0f / nNumBlockY)));
			// 座標を回転マトリックスで回転させる
			Vector3 v = pVtx->vtx;
			v = Vector3::Transform(v, mR);
			v.Normalize();
			pVtx->vtx = v;

			// 法線の設定
			pVtx->nor = pVtx->vtx;

			// 大きさ
			pVtx->vtx.x *= fSize;
			pVtx->vtx.y *= fSize;
			pVtx->vtx.z *= fSize;

			// 位置
			//pVtx->vtx.x += fPosX;
			//pVtx->vtx.y += fPosY;
			//pVtx->vtx.z += fPosZ;

			// 反射光の設定
			pVtx->diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標の設定
			pVtx->tex.x = fTexSize * y;
			pVtx->tex.y = fTexSize * x;
			++pVtx;
		}
	}
	//インデックス配列の中身を埋める
	std::uint32_t* pIdx = pIndexWk;
	for (std::uint32_t z = 0; z < nNumBlockY; ++z) {
		if (z > 0) {
			// 縮退ポリゴンのためのダブりの設定
			*pIdx++ = (z + 1) * (nNumBlockX + 1);
		}
		for (std::uint32_t x = 0; x < nNumBlockX + 1; ++x) {
			*pIdx++ = (z + 1) * (nNumBlockX + 1) + x;
			*pIdx++ = z * (nNumBlockX + 1) + x;
		}
		if (z < nNumBlockY - 1) {
			// 縮退ポリゴンのためのダブりの設定
			*pIdx++ = z * (nNumBlockX + 1) + nNumBlockX;
		}
	}

	// 頂点バッファ/インデックス バッファ生成
	// 頂点生成
	out.m_vertexCount = nNumVertex;
	for (std::uint32_t i = 0; i < out.m_vertexCount; ++i)
	{
		out.m_vertexData.positions.push_back(pVertexWk[i].vtx);
		out.m_vertexData.normals.push_back(pVertexWk[i].nor);
		out.m_vertexData.texcoord0s.push_back(pVertexWk[i].tex);
		out.m_vertexData.colors.push_back(pVertexWk[i].diffuse);
	}

	// インデックス
	out.m_indexCount = nNumIndex;
	for (std::uint32_t i = 0; i < out.m_indexCount; ++i)
	{
		out.m_indexData.push_back(pIndexWk[i]);
	}

	// 一時配列の解放
	delete[] pVertexWk;
	delete[] pIndexWk;
}

void Geometry::SkyDome(Core::CoreMesh& out, int nSegment, float fTexSplit)
{
	// プリミティブ種別設定
	out.m_topology = Core::PrimitiveTopology::TRIANGLE_LIST;
	float fScale = 0.5f;

	//頂点バッファ作成
	out.m_vertexCount = (nSegment + 1) * (nSegment / 2 + 1);
	VERTEX_3D* pVertexWk = new VERTEX_3D[out.m_vertexCount];

	for (int i = 0; i <= (nSegment / 2); ++i) {
		float irad = Mathf::Pi * 2.0f / (float)nSegment * (float)i;
		float y = (float)cos(irad);
		float r = (float)sin(irad);
		float v = (float)i / (float)(nSegment / 2) * fTexSplit;
		for (int j = 0; j <= nSegment; ++j) {
			float jrad = Mathf::Pi * 2.0f / (float)nSegment * (float)j;
			float x = r * (float)cos(jrad - Mathf::Pi * 0.5f);
			float z = r * (float)sin(jrad - Mathf::Pi * 0.5f);
			float u = (float)j / (float)nSegment * fTexSplit;
			int   inx = i * (nSegment + 1) + j;
			pVertexWk[inx].vtx.x = x * -fScale;
			pVertexWk[inx].vtx.y = y * fScale;
			pVertexWk[inx].vtx.z = z * -fScale;
			pVertexWk[inx].nor.x = x;
			pVertexWk[inx].nor.y = y;
			pVertexWk[inx].nor.z = z;
			pVertexWk[inx].tex.x = u;
			pVertexWk[inx].tex.y = v;
			pVertexWk[inx].diffuse = Vector4{ 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}

	// インデックスバッファの作成
	out.m_indexCount = nSegment * 3 + nSegment * (nSegment / 2 - 1) * 6 + nSegment * 3;
	std::uint32_t* pIndexWk = new std::uint32_t[out.m_indexCount];

	std::uint32_t icount = 0;
	std::uint32_t i = 0;
	for (std::uint32_t j = 0; j < nSegment; ++j) {
		pIndexWk[icount] = i * (nSegment + 1) + j;
		pIndexWk[icount + 1] = (i + 1) * (nSegment + 1) + j + 1;
		pIndexWk[icount + 2] = (i + 1) * (nSegment + 1) + j;
		icount += 3;
	}
	for (i = 1; i < nSegment / 2; ++i) {
		for (std::uint32_t j = 0; j < nSegment; ++j) {
			pIndexWk[icount] = i * (nSegment + 1) + j;
			pIndexWk[icount + 1] = i * (nSegment + 1) + j + 1;
			pIndexWk[icount + 2] = (i + 1) * (nSegment + 1) + j;
			icount += 3;
			pIndexWk[icount] = i * (nSegment + 1) + j + 1;
			pIndexWk[icount + 1] = (i + 1) * (nSegment + 1) + j + 1;
			pIndexWk[icount + 2] = (i + 1) * (nSegment + 1) + j;
			icount += 3;
		}
	}
	i = nSegment / 2;
	for (std::uint32_t j = 0; j < nSegment; ++j) {
		pIndexWk[icount] = i * (nSegment + 1) + j;
		pIndexWk[icount + 1] = (i + 1) * (nSegment + 1) + j + 1;
		pIndexWk[icount + 2] = (i + 1) * (nSegment + 1) + j;
		icount += 3;
	}

	// 頂点バッファ/インデックス バッファ生成
	// 頂点生成
	for (std::uint32_t i = 0; i < out.m_vertexCount; ++i)
	{
		out.m_vertexData.positions.push_back(pVertexWk[i].vtx);
		out.m_vertexData.normals.push_back(pVertexWk[i].nor);
		out.m_vertexData.texcoord0s.push_back(pVertexWk[i].tex);
		out.m_vertexData.colors.push_back(pVertexWk[i].diffuse);
	}

	// インデックス
	for (std::uint32_t i = 0; i < out.m_indexCount; ++i)
	{
		out.m_indexData.push_back(pIndexWk[i]);
	}

	// 一時配列の解放
	delete[] pVertexWk;
	delete[] pIndexWk;
}
