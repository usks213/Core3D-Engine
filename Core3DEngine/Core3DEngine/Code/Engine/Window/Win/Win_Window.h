/*****************************************************************//**
 * \file   Win_Window.h
 * \brief  ウィンドウズのウィンドウクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _WIN_WINDOW_
#define _WIN_WINDOW_

#include "../Core/Window.h"
#include <Windows.h>

namespace Core::Win
{
	/// @class WinWindow
	/// @brief ウィンドウズのウィンドウクラス
	class WinWindow final : public Core::Window
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param windowName[in] ウィンドウ名
		/// @param windowWidth[in] ウィンドウの幅
		/// @param windowHeight[in] ウィンドウの高さ
		explicit WinWindow(Util::String windowName, UINT windowWidth, UINT windowHeight);

		/// @brief デストラクタ
		~WinWindow() noexcept = default;

		/// @brief ウィンドウ初期化関数
		/// @param hInstance インスタンスハンドル
		/// @param className クラス名
		/// @param nCmdShow 
		/// @param lpfnWndProc ウィンドウプロシージャ関数のポインタ
		/// @return 初期化: 成功 true | 失敗 false
		bool initialize(HINSTANCE& hInstance, Util::String className, int nCmdShow, WNDPROC lpfnWndProc);

		/// @brief 終了処理
		void finalize() override;

		/// @brief ウィンドウハンドル取得
		/// @return ウィンドウハンドル
		HWND GetWindowHandle() { return m_hWnd; }

		/// @brief コピーコンストラクタ削除
		WinWindow(const WinWindow&) = delete;
		/// @brief ムーブコンストラクタ削除
		WinWindow(WinWindow&&) = delete;

	private:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		HINSTANCE		m_hInstance;		///< インスタンスハンドル
		HWND				m_hWnd;			///< ウィンドウハンドル
		Util::String		m_className;		///< クラス名
		int				m_nCmdShow;		///< フルスクリーン切り替えで使うかも？
	};

}

#endif // !_WIN_WINDOW_
