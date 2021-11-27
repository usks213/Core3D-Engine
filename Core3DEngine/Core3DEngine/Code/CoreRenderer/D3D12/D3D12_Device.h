/*****************************************************************//**
 * \file   D3D12_Device.h
 * \brief  DirectX12デバイス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/13
 *********************************************************************/

#ifndef _D3D12_RENDER_DEVICE_
#define _D3D12_RENDER_DEVICE_

#include <CoreRenderer/Core/Core_Device.h>
#include "D3D12_CommonState.h"
#include "D3D12_DescriptorPool.h"
#include <tuple>
#include <map>


namespace d3d12
{
	// 前定義
	class D3D12Renderer;
	class D3D12Shader;
	class D3D12Material;
	class D3D12Texture;

	/// @class D3D12Device
	/// @brief D3D12デバイス
	class D3D12Device final : public core::CoreDevice
	{
		friend class D3D12Renderer;
		friend class D3D12CommandList;
		friend class D3D12Shader;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit D3D12Device();

		/// @brief デストラクタ
		~D3D12Device() noexcept = default;

		/// @brief 初期化処理
		/// @param pDevice D3D12デバイスポインタ
		/// @param hWnd ウィンドウハンドル
		/// @param width ウィンドウの幅
		/// @param height ウィンドウの高さ
		/// @return 初期化: 成功 true | 失敗 false
		HRESULT initialize(ID3D12Device* pDevice, IDXGIFactory2* pFactory2, 
			HWND hWnd, UINT width, UINT height);

		//----- リソース生成 -----

		core::BufferID		createBuffer(core::BufferDesc& desc, const core::BufferData* pData = nullptr) override;
		core::DepthStencilID	createDepthStencil(core::TextureDesc& desc, float depth = 1.0f, std::uint8_t stencil = 0) override;
		core::MaterialID		createMaterial(std::string name, core::ShaderID& shaderID) override;
		core::MeshID			createMesh(std::string name) override;
		core::RenderBufferID	createRenderBuffer(core::ShaderID& shaderID, core::MeshID& meshID) override;
		core::RenderTargetID	createRenderTarget(core::TextureDesc& desc, const Color& color = Color()) override;
		core::ShaderID		createShader(core::ShaderDesc& desc) override;
		core::TextureID		createTexture(std::string filePath) override;
		core::TextureID		createTexture(core::TextureDesc& desc, const core::TextureData* pData = nullptr) override;

		//----- Native DirectX12 -----

		ID3D12Device* GetD3D12Device() { return m_pD3DDevice; }
		UINT GetBackBufferCount() { return m_backBufferCount; }
		DXGI_FORMAT GetBackBufferFormat() { return m_backBufferFormat; }
		D3D12DescriptorPool* GetTextureDescriptor() { return m_pTexturePool.get(); }

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief 共通ステートの生成
		/// @return HRESULT
		HRESULT createCommonState();

		/// @brief D3D12テクスチャ生成(クリア値あり)
		/// @param desc テクスチャDesc
		/// @param pClear クリアデータ
		/// @return D3D12テクスチャポインタ
		D3D12Texture* createD3D12Texture(core::TextureDesc& desc, D3D12_CLEAR_VALUE* pClear);

		/// @brief パイプラインステート生成
		/// @param d3d12Shader シェーダー
		/// @param d3d12Mat マテリアル
		/// @return パイプラインステート
		ID3D12PipelineState* createGraphicsPipelineState(D3D12Shader& d3d12Shader, const core::BlendState& bs,
			const core::RasterizeState& rs, const core::DepthStencilState& ds);


		//--- 更新リソース ---
		
		/// @brief 更新リソースをリストに追加
		/// @param pResource D3D12リソースポインタ
		/// @param pData データポインタ
		/// @param size データサイズ
		void AddUpdateResource(ID3D12Resource* pResource, void* pData, std::size_t size);

		/// @brief 更新リソースリストの実行
		void ExecuteUpdateResurce();

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		ID3D12Device*						m_pD3DDevice;			///< デバイスポインタ

		//ComPtr<IDXGISwapChain1>				m_swapChain;			///< スワップチェーン

		//ComPtr<ID3D12Texture2D>				m_backBufferRT;			///< バックバッファ
		//ComPtr<ID3D12RenderTargetView>		m_backBufferRTV;		///< バックバッファビュー
		DXGI_FORMAT							m_backBufferFormat;		///< バッファバッファフォーマット

		//ComPtr<ID3D12Texture2D>				m_depthStencilTexture;	///< Zバッファ
		//ComPtr<ID3D12DepthStencilView>		m_depthStencilView;		///< Zバッファビュー
		DXGI_FORMAT							m_depthStencilFormat;	///< Zバッファフォーマット

		HWND									m_hWnd;					///< ウィンドウハンドル
		D3D12_VIEWPORT						m_viewport;				///< ビューポート

		UINT									m_backBufferCount;		///< バックバッファ数
		UINT									m_nOutputWidth;			///< 出力サイズ(幅)
		UINT									m_nOutputHeight;		///< 出力サイズ(高さ)

		// ステート
		D3D12_RASTERIZER_DESC              	m_rasterizeStates[(size_t)core::RasterizeState::MAX];		///< ラスタライザステート
		D3D12_BLEND_DESC                   	m_blendStates[(size_t)core::BlendState::MAX];				///< ブレンドステート
		D3D12_DEPTH_STENCIL_DESC           	m_depthStencilStates[(size_t)core::DepthStencilState::MAX];	///< 深度ステンシルステート

		// サンプラー
		D3D12_STATIC_SAMPLER_DESC 			m_staticSamplers[(size_t)core::SamplerState::MAX];			///< 静的サンプラステート
		D3D12_GPU_DESCRIPTOR_HANDLE			m_dynamicSamplers[(size_t)core::SamplerState::MAX];			///< ダイナックサンプラー
		ComPtr<ID3D12DescriptorHeap>			m_pSamplerHeap;											///< サンプラーヒープ

		// グラフィクスパイプラインステート
		using GraphicsPipelineStateID = std::tuple<core::ShaderID, core::BlendState, core::RasterizeState, core::DepthStencilState>;
		std::map<GraphicsPipelineStateID, ComPtr<ID3D12PipelineState>>	m_pGraphicsPipelineState;

		//--- 更新リソース ---
		struct UpdateResourceData
		{
			ID3D12Resource*			pResource = nullptr;
			std::vector<std::byte>	data;
		};
		std::vector<UpdateResourceData>			m_updateResourceList;

		// ディスクリプタプール
		std::unique_ptr<D3D12DescriptorPool>	m_pTexturePool;
	};
}

#endif // !_D3D12_RENDER_DEVICE_
