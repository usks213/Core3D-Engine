/*****************************************************************//**
 * \file   RHI_Device.h
 * \brief  デバイスクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _RHI_DEVICE_
#define _RHI_DEVICE_

#include "RHI_DepthStencil.h"
#include "RHI_GPUBuffer.h"
#include "RHI_GraphicsShader.h"
#include "RHI_RenderTarget.h"
#include "RHI_Texture.h"


namespace Core::RHI
{
	/// @class Device
	/// @brief デバイス
	class Device
	{
		friend class Renderer;
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

		virtual std::shared_ptr<DepthStencil> CreateDepthStencil(TextureDesc& desc, float depth = 1.0f, std::uint8_t stencil = 0) = 0;

		virtual std::shared_ptr<GPUBuffer> CreateGPUBuffer(GPUBufferDesc& desc, const GPUBufferData* pData = nullptr) = 0;

		virtual std::shared_ptr<GraphicsShader> CreateGraphicsShader(GraphicsShader& desc) = 0;

		virtual std::shared_ptr<RenderTarget> CreateRenderTarget(TextureDesc& desc, const Color& color = Color()) = 0;

		virtual std::shared_ptr<Texture> CreateTexture(std::string filePath) = 0;

		virtual std::shared_ptr<Texture> CreateTexture(TextureDesc& desc, const TextureData* pData = nullptr) = 0;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		SampleDesc		m_sampleDesc;	///< サンプリング情報

	private:


	};
}

#endif // !_RHI_DEVICE_
