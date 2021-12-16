/*****************************************************************//**
 * \file   RHI_Device.h
 * \brief  デバイスクラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/

#include "RHI_Device.h"
using namespace Core::RHI;

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief コンストラクタ
Device::Device() :
	m_sampleDesc()
{
}

//----- リソース取得 -----

GPUBuffer* Device::getBuffer(const GPUBufferID& id) noexcept
{
	const auto& itr = m_bufferPool.find(id);
	if (m_bufferPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreDepthStencil* Device::GetDepthStencil(const DepthStencilID& id) noexcept
{
	const auto& itr = m_depthStencilPool.find(id);
	if (m_depthStencilPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreMaterial* Device::getMaterial(const MaterialID& id) noexcept
{
	const auto& itr = m_materialPool.find(id);
	if (m_materialPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreMesh* Device::getMesh(const MeshID& id) noexcept
{
	const auto& itr = m_meshPool.find(id);
	if (m_meshPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreRenderBuffer* Device::GetRenderBuffer(const RenderBufferID& id) noexcept
{
	const auto& itr = m_renderBufferPool.find(id);
	if (m_renderBufferPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreRenderTarget* Device::GetRenderTarget(const RenderTargetID& id) noexcept
{
	const auto& itr = m_renderTargetPool.find(id);
	if (m_renderTargetPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreShader* Device::GetShader(const ShaderID& id) noexcept
{
	const auto& itr = m_shaderPool.find(id);
	if (m_shaderPool.end() == itr) return nullptr;

	return itr->second.get();
}
Texture* Device::getTexture(const TextureID& id) noexcept
{
	const auto& itr = m_texturePool.find(id);
	if (m_texturePool.end() == itr) return nullptr;

	return itr->second.get();
}
