/*****************************************************************//**
 * \file   RHI_CommandList.h
 * \brief  レンダーコマンドリストクラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/
#ifndef _RHI_RENDER_CONTEXT_
#define _RHI_RENDER_CONTEXT_

#include "RHI_DepthStencil.h"
#include "RHI_GPUBuffer.h"
#include "RHI_GraphicsShader.h"
#include "RHI_RenderTarget.h"
#include "RHI_Texture.h"


namespace Core::RHI
{
	/// @class CommandList
	/// @brief レンダーコマンドリスト
	class CommandList
	{
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


		//----- ターゲットステート命令 -----

		virtual void SetBackBuffer() = 0;

		virtual void SetRenderTarget(std::shared_ptr<RenderTarget> pRT) = 0;
		virtual void SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[]) = 0;
		virtual void SetRenderTarget(std::shared_ptr<RenderTarget> pRT, std::shared_ptr<DepthStencil> pDS) = 0;
		virtual void SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[], std::shared_ptr<DepthStencil> pDS) = 0;

		virtual void SetViewport(const Rect& rect) = 0;
		virtual void SetViewport(const Viewport& viewport) = 0;


		//----- パイプラインステート命令 -----

		virtual void SetGraphicsPipelineState(std::shared_ptr<GraphicsShader> pShader, const BlendState& bs,
			const RasterizeState& rs, const DepthStencilState& ds) = 0;

		virtual void SetComputePipelineState() = 0;


		//----- リソース命令 -----

		virtual void SetConstantBuffer(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal) = 0;

		virtual void SetShaderResource(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal) = 0;

		virtual void SetUnorderedAccess(ShaderResourceLayout& resourceLayout, std::string_view name, std::shared_ptr<Resource> pResource, bool isGlobal) = 0;

		virtual void SetSampler(ShaderStage stage, ShaderResourceLayout& resourceLayout, std::string_view name, SamplerState samplerState, bool isGlobal) = 0;


		//----- ジオメトリーステート命令 -----

		virtual void SetVertexBuffer(std::shared_ptr<GPUBuffer> pVertexBuffer, const std::uint32_t offset) = 0;

		virtual void SetIndexBuffer(std::shared_ptr<GPUBuffer> pIndexBuffer, const std::uint32_t offset) = 0;

		virtual void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) = 0;


		//----- 描画・実行命令 -----

		virtual void DrawInstanced(std::uint32_t VertexCountPerInstance, std::uint32_t InstanceCount,
			std::uint32_t StartVertexLocation, std::uint32_t StartInstanceLocation) = 0;

		virtual void DrawIndexedInstanced(std::uint32_t IndexCountPerInstance, std::uint32_t InstanceCount,
			std::uint32_t StartIndexLocation, std::int32_t  BaseVertexLocation, std::uint32_t StartInstanceLocation) = 0;

		virtual void ExecuteIndirect() = 0;

		virtual void Dispatch() = 0;


		//----- クリア命令 -----

		virtual void ClearCommand() = 0;		///< コマンドのクリア

		virtual void ClearBackBuffer(const Color& color) = 0;

		virtual void ClearRederTarget(std::shared_ptr<RenderTarget> pRT, const Color& color) = 0;

		virtual void ClearDepthStencil(std::shared_ptr<DepthStencil> pDS, float depth, std::uint8_t stencil) = 0;


		//----- コピー命令 -----

		virtual void CopyToBackBuffer(std::shared_ptr<Resource> pSource) = 0;

		virtual void CopyFromBackBuffer(std::shared_ptr<Resource> pDest) = 0;

		virtual void CopyResource(std::shared_ptr<Resource> pDest, std::shared_ptr<Resource> pSource) = 0;


		////----- アップロード命令 -----

		//virtual void UpdateSubresources() = 0;

		//virtual void UploadBuffer() = 0;

		//virtual void UploadTexture() = 0;


	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		std::shared_ptr<DepthStencil>					m_pCurDSV;			///< 現在のDSV
		std::vector<std::shared_ptr<Resource>>			m_usedResourceList;	///< 使用リソースリスト
		std::vector<std::shared_ptr<GraphicsShader>>	m_usedShaderList;	///< 使用リソースリスト


	private:

	};
}

#endif // !_RHI_RENDER_CONTEXT_
