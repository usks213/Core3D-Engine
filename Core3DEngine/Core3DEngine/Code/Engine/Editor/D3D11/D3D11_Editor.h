/*****************************************************************//**
 * \file   D3D11_Editor.h
 * \brief  DirectX11エディター
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _D3D11_EDITOR_
#define _D3D11_EDITOR_

#include <Editor/Core/Editor.h>
#include <Renderer/D3D11/D3D11_Defines.h>

namespace Core::D3D11
{
	class D3D11Editor final : public Core::Editor
	{
	public:

		/// @brief コンストラクタ
		/// @param pEngine エンジンポインタ
		explicit D3D11Editor() noexcept 
		{
		}

		/// @brief デストラクタ
		~D3D11Editor() noexcept = default;

		/// @brief 初期化処理
		/// @param hWnd ウィンドウハンドル
		/// @param pDevice デバイス
		/// @param pContext イミディエイトコンテキスト
		/// @return 成功 TRUE / 失敗 FALSE
		bool initialize(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

		/// @brief 終了処理
		void finalize() override;

		/// @brief 新しい描画フレーム作成
		void NewFrame() override;

		/// @brief 描画
		/// @param cmdList コマンドリスト
		void Render(Core::CommandList* cmdList) override;

	private:

	};
}


#endif // !_D3D11_EDITOR_
