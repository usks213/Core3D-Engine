/*****************************************************************//**
 * \file   Core_Device.h
 * \brief  デバイスクラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/

#include "Core_Device.h"
using namespace core;

//------------------------------------------------------------------------------
// public methods
//------------------------------------------------------------------------------

/// @brief コンストラクタ
CoreDevice::CoreDevice() :
	m_sampleDesc()
{
}

//----- リソース取得 -----

CoreBuffer* CoreDevice::getBuffer(const BufferID& id) noexcept
{
	const auto& itr = m_bufferPool.find(id);
	if (m_bufferPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreDepthStencil* CoreDevice::getDepthStencil(const DepthStencilID& id) noexcept
{
	const auto& itr = m_depthStencilPool.find(id);
	if (m_depthStencilPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreMaterial* CoreDevice::getMaterial(const MaterialID& id) noexcept
{
	const auto& itr = m_materialPool.find(id);
	if (m_materialPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreMesh* CoreDevice::getMesh(const MeshID& id) noexcept
{
	const auto& itr = m_meshPool.find(id);
	if (m_meshPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreRenderBuffer* CoreDevice::getRenderBuffer(const RenderBufferID& id) noexcept
{
	const auto& itr = m_renderBufferPool.find(id);
	if (m_renderBufferPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreRenderTarget* CoreDevice::getRenderTarget(const RenderTargetID& id) noexcept
{
	const auto& itr = m_renderTargetPool.find(id);
	if (m_renderTargetPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreShader* CoreDevice::getShader(const ShaderID& id) noexcept
{
	const auto& itr = m_shaderPool.find(id);
	if (m_shaderPool.end() == itr) return nullptr;

	return itr->second.get();
}
CoreTexture* CoreDevice::getTexture(const TextureID& id) noexcept
{
	const auto& itr = m_texturePool.find(id);
	if (m_texturePool.end() == itr) return nullptr;

	return itr->second.get();
}
