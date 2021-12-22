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
		explicit Device() :
			m_sampleDesc()
		{
		}

		/// @brief デストラクタ
		virtual ~Device() noexcept = default;

		//----- リソース生成 -----

		virtual std::shared_ptr<DepthStencil> CreateDepthStencil(ResourceDesc& desc, float depth = 1.0f, std::uint8_t stencil = 0) = 0;

		virtual std::shared_ptr<GPUBuffer> CreateGPUBuffer(ResourceDesc& desc, const ResourceData* pData = nullptr) = 0;

		virtual std::shared_ptr<GraphicsShader> CreateGraphicsShader(GraphicsShaderDesc& desc) = 0;

		virtual std::shared_ptr<RenderTarget> CreateRenderTarget(ResourceDesc& desc, const Color& color = Color()) = 0;

		virtual std::shared_ptr<Texture> CreateTexture(std::string filePath) = 0;

		virtual std::shared_ptr<Texture> CreateTexture(ResourceDesc& desc, const ResourceData* pData = nullptr) = 0;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		SampleDesc		m_sampleDesc;	///< サンプリング情報

	private:


	};
}

#endif // !_RHI_DEVICE_
