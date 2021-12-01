/*****************************************************************//**
 * \file   Core_CommandList.h
 * \brief  レンダーコマンドリストクラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _CORE_RENDER_CONTEXT_
#define _CORE_RENDER_CONTEXT_

#include "Core_Buffer.h"
#include "Core_Material.h"
#include "Core_RenderBuffer.h"
#include "Core_RenderTarget.h"
#include "Core_DepthStencil.h"
#include "Core_ShaderResource.h"


namespace core
{
	/// @class CoreCommandList
	/// @brief レンダーコマンドリスト
	class CoreCommandList
	{
		friend class CoreRenderer;
	public:

		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit CoreCommandList()
		{
		}

		/// @brief デストラクタ
		virtual ~CoreCommandList() noexcept = default;


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

		virtual void bindGlobalBuffer(const core::ShaderID& shaderID, const std::string& bindName, const core::BufferID& bufferID) = 0;

		virtual void bindGlobalTexture(const core::ShaderID& shaderID, const std::string& bindName, const core::TextureID& textureID) = 0;

		virtual void bindGlobalSampler(const core::ShaderID& shaderID, const std::string& bindName, const core::SamplerState& sampler) = 0;


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

#endif // !_CORE_RENDER_CONTEXT_
