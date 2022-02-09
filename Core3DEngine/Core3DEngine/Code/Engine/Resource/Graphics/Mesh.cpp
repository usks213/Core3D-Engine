/*****************************************************************//**
 * \file   Mesh.h
 * \brief  メッシュクラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/05
 *********************************************************************/
#include "Mesh.h"
#include <Resource\Core\ResourceManager.h>

using namespace Core;

/// @brief シェーダーに対応するレンダーバッファの取得
/// @param shaderID グラフィックスシェーダーID
/// @return レンダーバッファ参照
std::shared_ptr<RenderBuffer> Mesh::GetRenderBuffer(const GraphicsShader::ID& shaderID)
{
	// 既に格納済み
	auto itr = m_renderBuffers.find(shaderID);
	if (m_renderBuffers.end() != itr)
	{
		return itr->second;
	}

	// シェーダー取得
	auto pShader = ResourceManager::get().GetResource<GraphicsShader>(shaderID);
	if (pShader == nullptr) return nullptr;
	auto pRHIShader = pShader->GetRHIGraphicsShader();
	if (!pRHIShader) return nullptr;

	// 新規生成
	m_renderBuffers[shaderID] = std::make_shared<RenderBuffer>(
		pRHIShader->GetInputLayout(), m_vertex, m_index);

	return m_renderBuffers[shaderID];
}
