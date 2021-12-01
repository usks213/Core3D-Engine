/*****************************************************************//**
 * \file   D3D11_Device.h
 * \brief  DirectX11デバイスクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _D3D11_RENDER_DEVICE_
#define _D3D11_RENDER_DEVICE_

#include <CoreRenderer/Core/Core_Device.h>
#include "D3D11_CommonState.h"

namespace d3d11
{
	// 前定義
	class D3D11Renderer;

	/// @class D3D11Device
	/// @brief D3D11デバイス
	class D3D11Device final : public core::CoreDevice
	{
		friend class D3D11Renderer;
		friend class D3D11CommandList;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit D3D11Device();

		/// @brief デストラクタ
		~D3D11Device() noexcept = default;

		/// @brief 初期化処理
		/// @param pDevice D3D11デバイスポインタ
		/// @param hWnd ウィンドウハンドル
		/// @param width ウィンドウの幅
		/// @param height ウィンドウの高さ
		/// @return 初期化: 成功 true | 失敗 false
		HRESULT initialize(ID3D11Device1* pDevice, IDXGIFactory2* pFactory2, 
			HWND hWnd, UINT width, UINT height, UINT backBufferCount);

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

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief スワップチェーンとバッファの生成
		/// @return HRESULT
		HRESULT createSwapChainAndBuffer(IDXGIFactory2* pFactory2);

		/// @brief 共通ステートの生成
		/// @return HRESULT
		HRESULT createCommonState();

		//--- 更新リソース ---

		/// @brief 更新リソースをリストに追加
		/// @param pResource D3D11リソースポインタ
		/// @param pData データポインタ
		/// @param size データサイズ
		void AddUpdateResource(ID3D11Resource* pResource, void* pData, std::size_t size);

		/// @brief 更新リソースリストの実行
		void ExecuteUpdateResurce(ID3D11DeviceContext1* pContext);

	private:
		//------------------------------------------------------------------------------
		// private variables 
		//------------------------------------------------------------------------------

		ID3D11Device1*					m_pD3DDevice;			///< デバイスポインタ

		ComPtr<IDXGISwapChain1>			m_swapChain;			///< スワップチェーン

		ComPtr<ID3D11Texture2D>			m_backBufferRT;			///< バックバッファ
		ComPtr<ID3D11RenderTargetView>		m_backBufferRTV;		///< バックバッファビュー
		DXGI_FORMAT						m_backBufferFormat;		///< バッファバッファフォーマット

		ComPtr<ID3D11Texture2D>			m_depthStencilTexture;	///< Zバッファ
		ComPtr<ID3D11DepthStencilView>		m_depthStencilView;		///< Zバッファビュー
		DXGI_FORMAT						m_depthStencilFormat;	///< Zバッファフォーマット

		HWND								m_hWnd;					///< ウィンドウハンドル
		D3D11_VIEWPORT					m_viewport;				///< ビューポート

		UINT								m_backBufferCount;		///< バックバッファ数
		UINT								m_nOutputWidth;			///< 出力サイズ(幅)
		UINT								m_nOutputHeight;		///< 出力サイズ(高さ)

		ComPtr<ID3D11RasterizerState>		m_rasterizeStates[(size_t)core::RasterizeState::MAX];		///< ラスタライザステート
		ComPtr<ID3D11SamplerState>		m_samplerStates[(size_t)core::SamplerState::MAX];			///< サンプラステート
		ComPtr<ID3D11BlendState>			m_blendStates[(size_t)core::BlendState::MAX];				///< ブレンドステート
		ComPtr<ID3D11DepthStencilState>	m_depthStencilStates[(size_t)core::DepthStencilState::MAX];	///< 深度ステンシルステート

		//--- 更新リソース ---
		struct UpdateResourceData
		{
			ID3D11Resource* pResource = nullptr;
			std::vector<std::byte>	data;
		};
		std::vector<UpdateResourceData>		m_updateResourceList;

	};
}

#endif // !_D3D11_RENDER_DEVICE_
