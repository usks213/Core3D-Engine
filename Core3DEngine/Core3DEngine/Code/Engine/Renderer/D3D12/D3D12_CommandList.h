/*****************************************************************//**
 * \file   D3D12_CommandList.h
 * \brief  DiectX12レンダーコマンドリスト
 * 
 * \author USAMI KOSHI
 * \date   2021/10/13
 *********************************************************************/

#ifndef _D3D12_RENDER_CONTEXT_
#define _D3D12_RENDER_CONTEXT_

#include <CoreRenderer/Core/Core_CommandList.h>
#include "D3D12_Shader.h"
#include "D3D12_Material.h"

#include <tuple>
#include <map>

namespace d3d12
{
	// 前定義
	class D3D12Renderer;
	class D3D12Device;

	/// @class D3D12CommandList
	/// @brief DirectX11レンダーコマンドリスト
	class D3D12CommandList final : public core::CoreCommandList
	{
		friend class D3D12Renderer;
	public:
		//------------------------------------------------------------------------------
		// public methods 
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit D3D12CommandList();

		/// @brief デストラクタ(デフォルト)
		~D3D12CommandList() noexcept = default;

		/// @brief 初期化処理
		/// @param pRenderer D3D12レンダラーポインタ
		/// @param pDevice D3D12デバイスポインタ
		/// @return 初期化: 成功 true | 失敗 false
		HRESULT initialize(D3D12Renderer* pRenderer, D3D12Device* pDevice);


		//----- リソース指定命令 -----

		void setMaterial(const core::MaterialID& materialID) override;

		void setRenderBuffer(const core::RenderBufferID& renderBufferID)  override;

		//----- セット命令 -----

		void setBackBuffer() override;

		void setGraphicsPipelineState(const core::ShaderID& shaderID, const core::BlendState& bs,
			const core::RasterizeState& rs, const core::DepthStencilState& ds) override;

		void setRenderTarget(const core::RenderTargetID& rtID) override;
		void setRenderTarget(const std::uint32_t num, const core::RenderTargetID rtIDs[]) override;
		void setRenderTarget(const core::RenderTargetID& rtID, const core::DepthStencilID& dsID) override;
		void setRenderTarget(const std::uint32_t num, const core::RenderTargetID rtIDs[], const core::DepthStencilID& dsID) override;

		void setViewport(const Rect& rect) override;
		void setViewport(const Viewport& viewport) override;

		//----- ゲット命令 -----

		//----- バインド命令 -----

		void bindGlobalBuffer(const core::ShaderID& shaderID, const std::string& bindName, const core::BufferID& bufferID) override;

		void bindGlobalTexture(const core::ShaderID& shaderID, const std::string& bindName, const core::TextureID& textureID) override;

		void bindGlobalSampler(const core::ShaderID& shaderID, const std::string& bindName, const core::SamplerState& sampler) override;

		//----- 描画命令 -----

		void render(const core::RenderBufferID& renderBufferID, std::uint32_t instanceCount = 1)  override;

		/// @brief 
		/// @param destID 対象のレンダーターゲット
		/// @param sourceID 
		/// @param matID 
		void blit(const core::RenderBufferID& destID, const core::TextureID& sourceID, const core::MaterialID& matID) override;


		//----- クリア -----

		void clearCommand() override;		///< コマンドのクリア

		void clearBackBuffer(const Color& color) override;

		void clearRederTarget(const core::RenderTargetID& rtID, const Color& color) override;

		void clearDepthStencil(const core::DepthStencilID& dsID, float depth, std::uint8_t stencil) override;


		//----- コピー -----

		void copyBackBuffer(const core::TextureID& sourceID) override;

		void copyTexture(const core::TextureID& destID, const core::TextureID& sourceID) override;


	public:
		// native

		ID3D12GraphicsCommandList* GetD3D12GraphicsCommandList() { return m_pCmdList.Get(); }

	private:
		//------------------------------------------------------------------------------
		// private methods 
		//------------------------------------------------------------------------------

		void setTextureResource(core::ShaderStage stage, std::uint32_t rootIndex, const core::TextureID& textureID);

		void setSamplerResource(core::ShaderStage stage, std::uint32_t rootIndex, core::SamplerState state);

		void setTrasitionResourceBarrier(ID3D12Resource* pResource, 
			D3D12_RESOURCE_STATES& before, const D3D12_RESOURCE_STATES after);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		D3D12Renderer*					m_pRenderer;			///< レンダラー
		D3D12Device*						m_pDevice;			///< デバイス

		ComPtr<ID3D12CommandAllocator>		m_pCmdAllocator;		///< コマンドアロケーター
		ComPtr<ID3D12GraphicsCommandList>	m_pCmdList;			///< コマンドリスト

		core::DepthStencilID				m_curDepthStencilID;	///< 現在のデプスステンシル

		static constexpr std::uint32_t MAX_RENDER_TARGET = 8;	///< レンダーターゲットの最大数
	};
}

#endif // !_D3D12_RENDER_CONTEXT_
