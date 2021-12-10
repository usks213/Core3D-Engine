/*****************************************************************//**
 * \file   D3D12_Editor.h
 * \brief  DirectX12エディター
 *
 * \author USAMI KOSHI
 * \date   2021/12/23
 *********************************************************************/
#ifndef _D3D12_EDITOR_
#define _D3D12_EDITOR_

#include <Editor/Core/Editor.h>
#include <RHI\D3D12\D3D12_Device.h>

namespace Core::D3D12
{
	class D3D12Editor final : public Core::Editor
	{
	public:

		/// @brief コンストラクタ
		/// @param pEngine エンジンポインタ
		explicit D3D12Editor() noexcept
		{
		}

		/// @brief デストラクタ
		~D3D12Editor() noexcept = default;

		/// @brief 初期化処理
		/// @param hWnd ウィンドウハンドル
		/// @param pDevice デバイス
		/// @param pContext イミディエイトコンテキスト
		/// @return 成功 TRUE / 失敗 FALSE
		bool initialize(HWND hWnd, D3D12Device* pDevice, int nBackBufferCount, DXGI_FORMAT backBufferFormat);

		/// @brief 終了処理
		void finalize() override;

		/// @brief 新しい描画フレーム作成
		void NewFrame() override;

		/// @brief 描画
		/// @param cmdList コマンドリスト
		void Render(Core::CommandList* cmdList) override;

	private:

		/// @brief ImGui用GUPヒープ
		ID3D12DescriptorHeap*	 m_pTexHeap;

	};
}


#endif // !_D3D12_EDITOR_
