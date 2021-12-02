/*****************************************************************//**
 * \file   D3D11_CommandList.h
 * \brief  DirectX11レンダーコマンドリストクラス
 *
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _D3D11_RENDER_CONTEXT_
#define _D3D11_RENDER_CONTEXT_

#include <Renderer/Core/CommandList.h>
#include <Resource/D3D11/D3D11_Shader.h>
#include <Resource/D3D11/D3D11_Material.h>


namespace Core::D3D11
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


		//----- リソース指定命令 -----

		void setMaterial(const Core::MaterialID& materialID) override;

		void setRenderBuffer(const Core::RenderBufferID& renderBufferID)  override;

		//----- セット命令 -----

		void setBackBuffer() override;

		void setGraphicsPipelineState(const Core::ShaderID& shaderID, const Core::BlendState& bs,
			const Core::RasterizeState& rs, const Core::DepthStencilState& ds) override;

		void setRenderTarget(const Core::RenderTargetID& rtID) override;
		void setRenderTarget(const std::uint32_t num, const Core::RenderTargetID rtIDs[]) override;
		void setRenderTarget(const Core::RenderTargetID& rtID, const Core::DepthStencilID& dsID) override;
		void setRenderTarget(const std::uint32_t num, const Core::RenderTargetID rtIDs[], const Core::DepthStencilID& dsID) override;

		void setViewport(const Rect& rect) override;
		void setViewport(const Viewport& viewport) override;

		//----- ゲット命令 -----


		//----- バインド命令 -----

		void bindGlobalBuffer(const Core::ShaderID& shaderID, const std::string& bindName, const Core::GPUBufferID& bufferID) override;

		void bindGlobalTexture(const Core::ShaderID& shaderID, const std::string& bindName, const Core::TextureID& textureID) override;

		void bindGlobalSampler(const Core::ShaderID& shaderID, const std::string& bindName, const Core::SamplerState& sampler) override;

		//----- 描画命令

		void render(const Core::RenderBufferID& renderBufferID, std::uint32_t instanceCount = 1)  override;

		/// @brief 
		/// @param destID 対象のレンダーターゲット
		/// @param sourceID 
		/// @param matID 
		void blit(const Core::RenderBufferID& destID, const Core::TextureID& sourceID, const Core::MaterialID& matID) override;


		//----- クリア -----

		void clearCommand() override;		///< コマンドのクリア

		void clearBackBuffer(const Color& color) override;

		void clearRederTarget(const Core::RenderTargetID& rtID, const Color& color) override;

		void clearDepthStencil(const Core::DepthStencilID& dsID, float depth, std::uint8_t stencil) override;


		//----- コピー -----

		void copyBackBuffer(const Core::TextureID& sourceID) override;

		void copyTexture(const Core::TextureID& destID, const Core::TextureID& sourceID) override;

		//----- Native -----

		D3D11Renderer* GetD3D11Renderer() { return m_pRenderer; }

	private:
		//------------------------------------------------------------------------------
		// private methods 
		//------------------------------------------------------------------------------

		void setCBufferResource(std::uint32_t slot, const Core::GPUBufferID& bufferID, Core::ShaderStage stage);

		void setTextureResource(std::uint32_t slot, const Core::TextureID& textureID, Core::ShaderStage stage);

		void setSamplerResource(std::uint32_t slot, Core::SamplerState state, Core::ShaderStage stage);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		D3D11Renderer*					m_pRenderer;				///< レンダラー
		D3D11Device*						m_pDevice;				///< デバイス

		ComPtr<ID3D11DeviceContext1>		m_pDeferredContext;		///< デファードコンテキスト
		ComPtr<ID3D11CommandList>			m_pCmdList;				///< コマンドリスト

		Core::DepthStencilID				m_curDepthStencilID;	///< 現在のデプスステンシル

		static constexpr std::uint32_t MAX_RENDER_TARGET = 8;	///< レンダーターゲットの最大数

	};
}

#endif // !_D3D11_RENDER_CONTEXT_
