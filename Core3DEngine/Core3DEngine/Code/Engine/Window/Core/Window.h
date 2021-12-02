/*****************************************************************//**
 * \file   Window.h
 * \brief  ウィンドウクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_WINDOW_
#define _CORE_WINDOW_

#include <Utils/Util_String.h>

namespace Core
{
	// 前定義
	class Engine;

	/// @class Window
	/// @brief コアウィンドウクラス
	class Window
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param windowName[in] ウィンドウ名
		/// @param windowWidth[in] ウィンドウの幅
		/// @param windowHeight[in] ウィンドウの高さ
		explicit Window(Util::String windowName, std::uint32_t windowWidth, std::uint32_t windowHeight);

		/// @brief デストラクタ
		virtual ~Window() noexcept = default;

		/// @brief 終了処理
		virtual void finalize() = 0;

		/// @brief ウィンドウ名取得
		/// @return ウィンドウ名
		[[nodiscard]] Util::String GetWindowName() const noexcept { return m_windowName; }

		/// @brief ウィンドウの幅取得
		/// @return ウィンドウの幅(整数)
		[[nodiscard]] int GetWindowWidth() const noexcept { return m_windowWidth; }

		/// @brief ウィンドウの高さ取得
		/// @return ウィンドウの高さ(整数)
		[[nodiscard]] int GetWindowHeight() const noexcept { return m_windowHeight; }

		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		Engine* GetEngine() const noexcept { return m_pCoreEngine; }

		/// @brief エンジンの設定
		/// @param pCoreEngine エンジンのポインタ
		void SetEngine(Engine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief コピーコンストラクタ削除
		Window(const Window&) = delete;
		/// @brief ムーブコンストラクタ削除
		Window(Window&&) = delete;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		Engine*		m_pCoreEngine;			///< エンジンのポインタ
		Util::String		m_windowName;		///< ウィンドウ名
		int				m_windowWidth;		///< ウィンドウの幅
		int				m_windowHeight;		///< ウィンドウの高さ
	};
}

#endif // !_CORE_WINDOW_
