/*****************************************************************//**
 * \file   Core_Device.h
 * \brief  デバイスクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _CORE_RENDER_DEVICE_
#define _CORE_RENDER_DEVICE_

#include "Core_Buffer.h"
#include "Core_DepthStencil.h"
#include "Core_Material.h"
#include "Core_Mesh.h"
#include "Core_RenderBuffer.h"
#include "Core_RenderTarget.h"
#include "Core_Shader.h"
#include "Core_Texture.h"


namespace core
{
	/// @class CoreDevice
	/// @brief デバイス
	class CoreDevice
	{
		friend class CoreRenderer;
		friend class CoreCommandList;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit CoreDevice();

		/// @brief デストラクタ
		virtual ~CoreDevice() noexcept = default;

		//----- リソース生成 -----

		virtual BufferID			createBuffer(BufferDesc& desc, const BufferData* pData = nullptr)	= 0;
		virtual DepthStencilID	createDepthStencil(TextureDesc& desc, float depth = 1.0f, std::uint8_t stencil = 0)	 = 0;
		virtual MaterialID		createMaterial(std::string name, ShaderID& shaderID)				= 0;
		virtual MeshID			createMesh(std::string name)										= 0;
		virtual RenderBufferID	createRenderBuffer(ShaderID& shaderID, MeshID& meshID)				= 0;
		virtual RenderTargetID	createRenderTarget(TextureDesc& desc, const Color& color = Color())	= 0;
		virtual ShaderID			createShader(ShaderDesc& desc)										= 0;
		virtual TextureID			createTexture(std::string filePath)								= 0;
		virtual TextureID			createTexture(TextureDesc& desc, const TextureData* pData = nullptr)	= 0;

		//----- リソース取得 -----

		CoreBuffer*			getBuffer(const BufferID& id) noexcept;
		CoreDepthStencil*		getDepthStencil(const DepthStencilID& id) noexcept;
		CoreMaterial*		getMaterial(const MaterialID& id) noexcept;
		CoreMesh*			getMesh(const MeshID& id) noexcept;
		CoreRenderBuffer*		getRenderBuffer(const RenderBufferID& id) noexcept;
		CoreRenderTarget*		getRenderTarget(const RenderTargetID& id) noexcept;
		CoreShader*			getShader(const ShaderID& id) noexcept;
		CoreTexture*			getTexture(const TextureID& id) noexcept;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		SampleDesc		m_sampleDesc;	///< サンプリング情報

		//----- リソースプール -----
		std::unordered_map<BufferID,		std::unique_ptr<CoreBuffer>>			m_bufferPool;
		std::unordered_map<DepthStencilID,	std::unique_ptr<CoreDepthStencil>>		m_depthStencilPool;
		std::unordered_map<MaterialID,		std::unique_ptr<CoreMaterial>>			m_materialPool;
		std::unordered_map<MeshID,		std::unique_ptr<CoreMesh>>			m_meshPool;
		std::unordered_map<RenderBufferID,	std::unique_ptr<CoreRenderBuffer>>		m_renderBufferPool;
		std::unordered_map<RenderTargetID,	std::unique_ptr<CoreRenderTarget>>		m_renderTargetPool;
		std::unordered_map<ShaderID,		std::unique_ptr<CoreShader>>			m_shaderPool;
		std::unordered_map<TextureID,		std::unique_ptr<CoreTexture>>			m_texturePool;

	private:


	};
}

#endif // !_CORE_RENDER_DEVICE_
