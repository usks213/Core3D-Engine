/*****************************************************************//**
 * \file   D3D11_Renderer.h
 * \brief  DirectX11レンダラークラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _D3D11_RENDERER_
#define _D3D11_RENDERER_

#include <Renderer/Core/Renderer.h>
#include <Renderer/D3D11/D3D11_Device.h>
#include <Renderer/D3D11/D3D11_CommandList.h>

namespace Core::D3D11
{
	class D3D11Device;
	class D3D11CommandList;

	/// @brief D3D11レンダラー
	/// @class D3D11Renderer
	class D3D11Renderer final : public Renderer
	{
		friend class D3D11Device;
		friend class D3D11CommandList;
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit D3D11Renderer();
		/// @brief デストラクタ
		~D3D11Renderer() noexcept = default;

		/// @brief 初期化処理
		/// @param hWnd ウィンドウハンドル
		/// @param width ウィンドウの幅
		/// @param height ウィンドウの高さ
		/// @return 初期化: 成功 true | 失敗 false
		HRESULT initialize(HWND hWnd, UINT width, UINT height);

		/// @brief 終了処理
		void finalize() override;

		/// @brief フレーム開始
		void beginFrame() override;
		/// @brief フレーム終了
		void endFrame() override;

		/// @brief デバイスの取得
		/// @return デバイスのポインタ
		Core::Device* getDevice() override
		{
			return &m_device;
		}

		/// @brief コマンドリストの取得
		/// @return コマンドリストのポインタ 
		Core::CommandList* getCommandList() override;

		/// @brief コピーコンストラクタ削除
		D3D11Renderer(const D3D11Renderer&) = delete;
		/// @brief ムーブコンストラクタ削除
		D3D11Renderer(D3D11Renderer&&) = delete;

	public:

		//--- Native ---

		/// @brief DirectX11デバイスの取得
		/// @return DirectX11デバイス
		ID3D11Device1* GetD3D11Device() const noexcept { return m_d3dDevice.Get(); }

		/// @brief DirectX11イミディエイトコンテキストの取得
		/// @return DirectX11デバイスコンテキスト
		ID3D11DeviceContext* GetD3D11Context() const noexcept { return m_d3dContext.Get(); }

		/// @brief イミディエイトコンテキストでバッファ指定
		void SetD3D11BackBuffer();

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief デバイスとコマンドリストの生成
		/// @return HRESULT
		HRESULT CreateDiveceAndContext(HWND hWnd);


	public:
		//------------------------------------------------------------------------------
		// public variables
		//------------------------------------------------------------------------------
		static constexpr std::uint32_t BACK_BUFFER_COUNT = 2;

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		D3D11Device						m_device;					///< デバイスクラス
		
		std::uint32_t m_curBackBufferIndex;

		std::vector<std::unique_ptr<D3D11CommandList>>	m_cmdLists[BACK_BUFFER_COUNT];			///< コマンドリスト配列
		std::uint32_t								m_useCmdListCnt[BACK_BUFFER_COUNT];	///< 使用されているコマンドリスト数

		ComPtr<ID3D11Device1>				m_d3dDevice;					///< デバイス
		ComPtr<ID3D11DeviceContext1>		m_d3dContext;				///< イミディエイトコンテキスト
		ComPtr<ID3DUserDefinedAnnotation>	m_d3dAnnotation;				///< アノテーション

		ComPtr<IDXGIFactory2>				m_dxgiFactory;				///< ファクトリー

	};
}

#endif // !_D3D11_RENDERER_
