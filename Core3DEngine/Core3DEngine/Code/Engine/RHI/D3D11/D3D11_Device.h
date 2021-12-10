/*****************************************************************//**
 * \file   D3D11_Device.h
 * \brief  DirectX11デバイスクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/04
 *********************************************************************/

#ifndef _D3D11_RENDER_DEVICE_
#define _D3D11_RENDER_DEVICE_

#include <RHI/Core/Device.h>
#include "D3D11_CommonState.h"

namespace Core::D3D11
{
	// 前定義
	class D3D11Renderer;

	/// @class D3D11Device
	/// @brief D3D11デバイス
	class D3D11Device final : public Core::Device
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

		Core::GPUBufferID		CreateBuffer(Core::GPUBufferDesc& desc, const Core::GPUBufferData* pData = nullptr) override;
		Core::DepthStencilID	CreateDepthStencil(Core::TextureDesc& desc, float depth = 1.0f, std::uint8_t stencil = 0) override;
		Core::MaterialID		CreateMaterial(std::string name, Core::ShaderID& shaderID) override;
		Core::MeshID			CreateMesh(std::string name) override;
		Core::RenderBufferID	CreateRenderBuffer(Core::ShaderID& shaderID, Core::MeshID& meshID) override;
		Core::RenderTargetID	CreateRenderTarget(Core::TextureDesc& desc, const Color& color = Color()) override;
		Core::ShaderID		CreateShader(Core::ShaderDesc& desc) override;
		Core::TextureID		CreateTexture(std::string filePath) override;
		Core::TextureID		CreateTexture(Core::TextureDesc& desc, const Core::TextureData* pData = nullptr) override;

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief スワップチェーンとバッファの生成
		/// @return HRESULT
		HRESULT CreateSwapChainAndBuffer(IDXGIFactory2* pFactory2);

		/// @brief 共通ステートの生成
		/// @return HRESULT
		HRESULT CreateCommonState();

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

		ComPtr<ID3D11RasterizerState>		m_rasterizeStates[(size_t)Core::RasterizeState::MAX];		///< ラスタライザステート
		ComPtr<ID3D11SamplerState>		m_samplerStates[(size_t)Core::SamplerState::MAX];			///< サンプラステート
		ComPtr<ID3D11BlendState>			m_blendStates[(size_t)Core::BlendState::MAX];				///< ブレンドステート
		ComPtr<ID3D11DepthStencilState>	m_depthStencilStates[(size_t)Core::DepthStencilState::MAX];	///< 深度ステンシルステート

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
