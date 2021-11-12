/*****************************************************************//**
 * \file   Core_Engine.h
 * \brief  エンジンクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_ENGINE_
#define _CORE_ENGINE_


#include <memory>
#include <chrono>

#include <CoreSystem\Utils\Util_Singleton.h>
#include <CoreSystem\Window\Core\Core_Window.h>
#include <CoreRenderer\Core\Core_Renderer.h>
#include <CoreEngine\Scene\Core_SceneManager.h>


namespace core
{

	/// @class CoreEngine
	/// @brief エンジン
	class CoreEngine final : public util::UtilSingleton<CoreEngine>
	{
	private:
		friend util::UtilSingleton<CoreEngine>;

	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief 初期化処理
		/// @return 初期化: 成功 true | 失敗 false
		[[nodiscard]] bool initialize();

		/// @brief 更新関数
		void tick();

		/// @brief 終了処理
		void finalize();

		/// @brief ウィンドウの生成
		/// @tparam T ウィンドウタイプ
		/// @tparam CoreWindow継承型のみ
		/// @return ウィンドウのポインタ
		template<class T, typename = std::enable_if_t<std::is_base_of_v<CoreWindow, T>>>
		T* createWindow(util::String windowName, int windowWidth, int windowHeight) {
			m_pWindow = std::make_unique<T>(windowName, windowWidth, windowHeight);
			m_pWindow->setCoreEngine(this);
			return static_cast<T*>(m_pWindow.get());
		}

		/// @brief レンダラーの生成
		/// @tparam T レンダラータイプ
		/// @tparam CoreRenderer継承型のみ
		/// @return レンダラーのポインタ
		template<class T, typename = std::enable_if_t<std::is_base_of_v<CoreRenderer, T>>>
		T* createRenderer() {
			m_pRenderer = std::make_unique<T>();
			m_pRenderer->setCoreEngine(this);
			return static_cast<T*>(m_pRenderer.get());
		}

		/// @brief ウィンドウの取得
		/// @return ウィンドウのポインタ
		[[nodiscard]] CoreWindow* getWindow() const noexcept { return m_pWindow.get(); }

		/// @brief レンダラー取得
		/// @return レンダラーのポインタ
		[[nodiscard]] CoreRenderer* getRenderer() const noexcept { return m_pRenderer.get(); }

		/// @brief シーンマネージャーの取得
		/// @return シーンマネージャーのポインタ
		[[nodiscard]] CoreSceneManager* getSceneManager() const noexcept { return m_pSceneManager.get(); }

		/// @brief ウィンドウ名取得
		/// @return ウィンドウ名
		[[nodiscard]] util::String getWindowName() const noexcept { return m_pWindow->getWindowName(); }

		/// @brief ウィンドウの幅取得
		/// @return ウィンドウの幅(整数)
		[[nodiscard]] int getWindowWidth() const noexcept { return m_pWindow->getWindowWidth(); }

		/// @brief ウィンドウの高さ取得
		/// @return ウィンドウの高さ(整数)
		[[nodiscard]] int getWindowHeight() const noexcept { return m_pWindow->getWindowHeight(); }

		/// @brief 現在のフレームレート取得
		/// @return フレームレート(整数)
		[[nodiscard]] std::uint32_t getCurrentFPS() const noexcept { return m_nCurrentFPS; }

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		CoreEngine();

		/// @brief デストラクタ
		~CoreEngine() = default;

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		std::unique_ptr<CoreWindow>				m_pWindow;			///< ウィンドウ
		std::unique_ptr<CoreRenderer>			m_pRenderer;			///< レンダラー
		std::unique_ptr<CoreSceneManager>		m_pSceneManager;		///< シーンマネージャー

		//--- タイマー 
		// ↓これがもっともいい精度
		// std::chrono::high_resolution_clock;

		std::uint32_t							m_nCurrentFPS;			///< 現在のFPS
		std::uint64_t							m_nFrameCount;			///< フレームレートカウンタ
		std::chrono::system_clock::time_point	m_FixedExecLastTime;	///< 一定更新の前時間 
		std::chrono::system_clock::time_point	m_ExecLastTime;			///< 通常更新の前時間
		std::chrono::system_clock::time_point	m_FPSLastTime;			///< FPS計測用の前時間
		std::chrono::system_clock::time_point	m_CurrentTime;			///< 現在の時間

		float									m_deltaTime;			///< 通常更新の単位時間
		float									m_fixedDeltaTime;		///< 一定更新の単位時間
		std::int32_t							m_nMaxFPS;				///< 最大FPS
		std::int64_t							m_nFixedTime;			///< 一定更新の時間
	};

}

#endif // !_CORE_ENGINE_
