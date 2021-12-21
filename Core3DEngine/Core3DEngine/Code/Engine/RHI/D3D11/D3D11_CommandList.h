/*****************************************************************//**
 * \file   D3D11_CommandList.h
 * \brief  DirectX11レンダーコマンドリストクラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _D3D11_RENDER_CONTEXT_
#define _D3D11_RENDER_CONTEXT_

#include <RHI/Core/RHI_CommandList.h>

namespace Core::RHI::D3D11
{
	// 前定義
	class D3D11Renderer;
	class D3D11Device;

	/// @class D3D11CommandList
	/// @brief DirectX11レンダーコマンドリスト
	class D3D11CommandList final : public CommandList
	{
		friend class D3D11Renderer;
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit D3D11CommandList();

		/// @brief デストラクタ(デフォルト)
		~D3D11CommandList() noexcept = default;

		/// @brief 初期化処理
		/// @param pRenderer D3D11レンダラーポインタ
		/// @param pDevice D3D11デバイスポインタ
		/// @return 初期化: 成功 true | 失敗 false
		HRESULT initialize(D3D11Renderer* pRenderer, D3D11Device* pDevice);


		//----- ターゲットステート命令 -----

		void SetBackBuffer() override;

		void SetRenderTarget(std::shared_ptr<RenderTarget> pRT) override;
		void SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[]) override;
		void SetRenderTarget(std::shared_ptr<RenderTarget> pRT, std::shared_ptr<DepthStencil> pDS) override;
		void SetRenderTarget(const std::uint32_t num, std::shared_ptr<RenderTarget> pRTs[], std::shared_ptr<DepthStencil> pDS) override;

		void SetViewport(const Rect& rect) override;
		void SetViewport(const Viewport& viewport) override;


		//----- パイプラインステート命令 -----

		void SetGraphicsPipelineState(std::shared_ptr<GraphicsShader> pShader, const BlendState& bs,
			const RasterizeState& rs, const DepthStencilState& ds) override;

		void SetComputePipelineState() override;

		//----- リソース命令 -----

		void SetLocalBuffer(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, std::shared_ptr<GPUBuffer> pGPUBuffer) override;

		void SetLocalTexture(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, std::shared_ptr<Texture> pTexture) override;

		void SetLocalSampler(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, SamplerState samplerState) override;

		void SetGlobalBuffer(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, std::shared_ptr<GPUBuffer> pGPUBuffer) override;

		void SetGlobalTexture(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, std::shared_ptr<Texture> pTexture) override;

		void SetGlobalSampler(std::shared_ptr<GraphicsShader> pShader, const std::string& bindName, SamplerState samplerState) override;


		//----- ジオメトリーステート命令 -----

		void SetVertexBuffer() override;

		void SetIndexBuffer() override;

		void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) override;


		//----- 描画・実行命令 -----

		void DrawInstanced(std::uint32_t VertexCountPerInstance, std::uint32_t InstanceCount,
			std::uint32_t StartVertexLocation, std::uint32_t StartInstanceLocation) override;

		void DrawIndexedInstanced(std::uint32_t IndexCountPerInstance, std::uint32_t InstanceCount,
			std::uint32_t StartIndexLocation, std::int32_t  BaseVertexLocation, std::uint32_t StartInstanceLocation) override;

		void ExecuteIndirect() override;

		void Dispatch() override;


		//----- クリア命令 -----

		void ClearCommand() override;		///< コマンドのクリア

		void ClearBackBuffer(const Color& color) override;

		void ClearRederTarget(std::shared_ptr<RenderTarget> pRT, const Color& color) override;

		void ClearDepthStencil(std::shared_ptr<DepthStencil> pDS, float depth, std::uint8_t stencil) override;


		//----- コピー命令 -----

		void CopyBackBuffer(std::shared_ptr<Texture> pSource) override;

		void CopyBuffer(std::shared_ptr<GPUBuffer> pDest, std::shared_ptr<GPUBuffer> pSource) override;

		void CopyTexture(std::shared_ptr<Texture> pDest, std::shared_ptr<Texture> pSource) override;

		//----- Native -----

		D3D11Renderer* GetD3D11Renderer() { return m_pRenderer; }

		D3D11Device* GetD3D11Device() { return m_pDevice; }

	private:
		//------------------------------------------------------------------------------
		// private methods 
		//------------------------------------------------------------------------------

		void setCBufferResource(std::uint32_t slot, const Core::GPUBufferID& bufferID, Core::GraphicsShaderStage stage);

		void setTextureResource(std::uint32_t slot, const Core::TextureID& textureID, Core::GraphicsShaderStage stage);

		void setSamplerResource(std::uint32_t slot, Core::SamplerState state, Core::GraphicsShaderStage stage);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		D3D11Renderer*					m_pRenderer;				///< レンダラー
		D3D11Device*						m_pDevice;				///< デバイス

		ComPtr<ID3D11DeviceContext1>		m_pDeferredContext;		///< デファードコンテキスト
		ComPtr<ID3D11CommandList>			m_pCmdList;				///< コマンドリスト

		static constexpr std::uint32_t MAX_RENDER_TARGET = 8;	///< レンダーターゲットの最大数

	};
}

#endif // !_D3D11_RENDER_CONTEXT_
