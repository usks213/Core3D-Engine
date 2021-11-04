/*****************************************************************//**
 * \file   Core_Window.h
 * \brief  ウィンドウクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_WINDOW_
#define _CORE_WINDOW_

#include <CoreSystem\Utils\Core_String.h>

namespace core
{
	// 前定義
	class CoreEngine;

	/// @class CoreWindow
	/// @brief コアウィンドウクラス
	class CoreWindow
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		/// @param windowName[in] ウィンドウ名
		/// @param windowWidth[in] ウィンドウの幅
		/// @param windowHeight[in] ウィンドウの高さ
		explicit CoreWindow(CoreString windowName, std::uint32_t windowWidth, std::uint32_t windowHeight);

		/// @brief デストラクタ
		virtual ~CoreWindow() noexcept = default;

		/// @brief 終了処理
		virtual void finalize() = 0;

		/// @brief ウィンドウ名取得
		/// @return ウィンドウ名
		[[nodiscard]] CoreString getWindowName() const noexcept { return m_windowName; }

		/// @brief ウィンドウの幅取得
		/// @return ウィンドウの幅(整数)
		[[nodiscard]] int getWindowWidth() const noexcept { return m_windowWidth; }

		/// @brief ウィンドウの高さ取得
		/// @return ウィンドウの高さ(整数)
		[[nodiscard]] int getWindowHeight() const noexcept { return m_windowHeight; }

		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		CoreEngine* getCoreEngine() const noexcept { return m_pCoreEngine; }

		/// @brief エンジンの設定
		/// @param pCoreEngine エンジンのポインタ
		void setCoreEngine(CoreEngine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief コピーコンストラクタ削除
		CoreWindow(const CoreWindow&) = delete;
		/// @brief ムーブコンストラクタ削除
		CoreWindow(CoreWindow&&) = delete;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		CoreEngine*		m_pCoreEngine;			///< エンジンのポインタ
		CoreString		m_windowName;		///< ウィンドウ名
		int				m_windowWidth;		///< ウィンドウの幅
		int				m_windowHeight;		///< ウィンドウの高さ
	};
}

#endif // !_CORE_WINDOW_
