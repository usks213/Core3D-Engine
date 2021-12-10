/*****************************************************************//**
 * \file   RHI_Device.h
 * \brief  デバイスクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _CORE_RENDER_DEVICE_
#define _CORE_RENDER_DEVICE_

#include <Resource\Core\GPUBuffer.h>
#include <Resource\Core\Material.h>
#include <Resource\Core\RenderBuffer.h>
#include <Resource\Core\RenderTarget.h>
#include <Resource\Core\DepthStencil.h>
#include <Resource\Core\ShaderResource.h>


namespace Core::RHI
{
	/// @class Device
	/// @brief デバイス
	class Device
	{
		friend class RHI;
		friend class CommandList;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit Device();

		/// @brief デストラクタ
		virtual ~Device() noexcept = default;

		//----- リソース生成 -----

		virtual GPUBufferID			CreateBuffer(GPUBufferDesc& desc, const GPUBufferData* pData = nullptr)	= 0;
		virtual DepthStencilID	CreateDepthStencil(TextureDesc& desc, float depth = 1.0f, std::uint8_t stencil = 0)	 = 0;
		virtual MaterialID		CreateMaterial(std::string name, ShaderID& shaderID)				= 0;
		virtual MeshID			CreateMesh(std::string name)										= 0;
		virtual RenderBufferID	CreateRenderBuffer(ShaderID& shaderID, MeshID& meshID)				= 0;
		virtual RenderTargetID	CreateRenderTarget(TextureDesc& desc, const Color& color = Color())	= 0;
		virtual ShaderID			CreateShader(ShaderDesc& desc)										= 0;
		virtual TextureID			CreateTexture(std::string filePath)								= 0;
		virtual TextureID			CreateTexture(TextureDesc& desc, const TextureData* pData = nullptr)	= 0;

		//----- リソース取得 -----

		GPUBuffer*			getBuffer(const GPUBufferID& id) noexcept;
		CoreDepthStencil*		getDepthStencil(const DepthStencilID& id) noexcept;
		CoreMaterial*		getMaterial(const MaterialID& id) noexcept;
		CoreMesh*			getMesh(const MeshID& id) noexcept;
		CoreRenderBuffer*		GetRenderBuffer(const RenderBufferID& id) noexcept;
		CoreRenderTarget*		GetRenderTarget(const RenderTargetID& id) noexcept;
		CoreShader*			GetShader(const ShaderID& id) noexcept;
		Texture*			getTexture(const TextureID& id) noexcept;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		SampleDesc		m_sampleDesc;	///< サンプリング情報

		//----- リソースプール -----
		std::unordered_map<GPUBufferID,		std::unique_ptr<GPUBuffer>>			m_bufferPool;
		std::unordered_map<DepthStencilID,	std::unique_ptr<CoreDepthStencil>>		m_depthStencilPool;
		std::unordered_map<MaterialID,		std::unique_ptr<CoreMaterial>>			m_materialPool;
		std::unordered_map<MeshID,		std::unique_ptr<CoreMesh>>			m_meshPool;
		std::unordered_map<RenderBufferID,	std::unique_ptr<CoreRenderBuffer>>		m_renderBufferPool;
		std::unordered_map<RenderTargetID,	std::unique_ptr<CoreRenderTarget>>		m_renderTargetPool;
		std::unordered_map<ShaderID,		std::unique_ptr<CoreShader>>			m_shaderPool;
		std::unordered_map<TextureID,		std::unique_ptr<Texture>>			m_texturePool;

	private:


	};
}

#endif // !_CORE_RENDER_DEVICE_
