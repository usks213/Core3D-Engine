/*****************************************************************//**
 * \file   RHI_CommandList.h
 * \brief  レンダーコマンドリストクラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _RHI_RENDER_CONTEXT_
#define _RHI_RENDER_CONTEXT_

#include <Resource\Core\GPUBuffer.h>
#include <Resource\Core\Material.h>
#include <Resource\Core\RenderBuffer.h>
#include <Resource\Core\RenderTarget.h>
#include <Resource\Core\DepthStencil.h>
#include <Resource\Core\ShaderResource.h>


namespace Core::RHI
{
	/// @class CommandList
	/// @brief レンダーコマンドリスト
	class CommandList
	{
		friend class RHI;
	public:

		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit CommandList()
		{
		}

		/// @brief デストラクタ
		virtual ~CommandList() noexcept = default;


		//----- リソース指定命令 -----

		/// @brief マテリアル指定
		/// @param materialID マテリアルID
		virtual void setMaterial(const MaterialID& materialID) = 0;

		/// @brief レンダーバッファ指定
		/// @param renderBufferID レンダーバッファID
		virtual void setRenderBuffer(const RenderBufferID& renderBufferID) = 0;


		//----- セット命令 -----

		virtual void setBackBuffer() = 0;

		virtual void setGraphicsPipelineState(const ShaderID& shaderID, const BlendState& bs,
			const RasterizeState& rs, const DepthStencilState& ds) = 0;

		virtual void setRenderTarget(const RenderTargetID& rtID) = 0;
		virtual void setRenderTarget(const std::uint32_t num, const RenderTargetID rtIDs[]) = 0;
		virtual void setRenderTarget(const RenderTargetID& rtID, const DepthStencilID& dsID) = 0;
		virtual void setRenderTarget(const std::uint32_t num, const RenderTargetID rtIDs[], const DepthStencilID& dsID) = 0;

		virtual void setViewport(const Rect& rect) = 0;
		virtual void setViewport(const Viewport& viewport) = 0;

		//----- ゲット命令 -----


		//----- バインド命令 -----

		virtual void bindGlobalBuffer(const Core::ShaderID& shaderID, const std::string& bindName, const Core::GPUBufferID& bufferID) = 0;

		virtual void bindGlobalTexture(const Core::ShaderID& shaderID, const std::string& bindName, const Core::TextureID& textureID) = 0;

		virtual void bindGlobalSampler(const Core::ShaderID& shaderID, const std::string& bindName, const Core::SamplerState& sampler) = 0;


		//----- 描画命令 -----

		/// @brief 描画命令
		/// @param renderBufferID レンダーバッファID
		virtual void render(const RenderBufferID& renderBufferID, const std::uint32_t instanceCount = 1) = 0;

		/// @brief 
		/// @param destID 対象のレンダーターゲット
		/// @param sourceID 
		/// @param matID 
		virtual void blit(const RenderBufferID& destID, const TextureID& sourceID, const MaterialID& matID) = 0;


		//----- クリア -----

		virtual void clearCommand() = 0;		///< コマンドのクリア

		virtual void clearBackBuffer(const Color& color) = 0;

		virtual void clearRederTarget(const RenderTargetID& rtID, const Color& color) = 0;

		virtual void clearDepthStencil(const DepthStencilID& dsID, float depth, std::uint8_t stencil) = 0;


		//----- コピー -----

		virtual void copyBackBuffer(const TextureID& sourceID) = 0;

		virtual void copyTexture(const TextureID& destID, const TextureID& sourceID) = 0;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------


	private:

	};
}

#endif // !_RHI_RENDER_CONTEXT_
