/*****************************************************************//**
 * \file   Engine.h
 * \brief  エンジンクラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_ENGINE_
#define _CORE_ENGINE_

#include <memory>
#include <chrono>

#include <Utils\Util_Singleton.h>
#include <Window\Core\Window.h>
#include <RHI\Core\RHI_Renderer.h>
#include <Editor\Core\Editor.h>
#include <Runtime\Core\SceneManager.h>

#ifdef CreateWindow
#undef CreateWindow
#endif // CreateWindow

namespace Core
{
	/// @class Engine
	/// @brief エンジン
	class Engine final : public Util::Singleton<Engine>
	{
	private:
		friend Util::Singleton<Engine>;

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
		/// @tparam Window継承型のみ
		/// @return ウィンドウのポインタ
		template<class T, typename = std::enable_if_t<std::is_base_of_v<Window, T>>>
		T* CreateWindow(Util::String windowName, std::uint32_t windowWidth, std::uint32_t windowHeight)
		{
			m_pWindow = std::make_unique<T>(windowName, windowWidth, windowHeight);
			m_pWindow->SetEngine(this);
			return static_cast<T*>(m_pWindow.get());
		}

		/// @brief レンダラーの生成
		/// @tparam T レンダラータイプ
		/// @tparam RHI::Renderer継承型のみ
		/// @return レンダラーのポインタ
		template<class T, typename = std::enable_if_t<std::is_base_of_v<RHI::Renderer, T>>>
		T* CreateRenderer() {
			m_pRenderer = std::make_unique<T>();
			m_pRenderer->SetEngine(this);
			return static_cast<T*>(m_pRenderer.get());
		}

		/// @brief エディターの生成
		/// @tparam T エディタータイプ
		/// @tparam Editor継承型のみ
		/// @return エディターのポインタ
		template<class T, typename = std::enable_if_t<std::is_base_of_v<Editor, T>>>
		T* CreateEditor() {
			m_pEditor = std::make_unique<T>();
			m_pEditor->SetEngine(this);
			return static_cast<T*>(m_pEditor.get());
		}

		/// @brief ウィンドウの取得
		/// @return ウィンドウのポインタ
		[[nodiscard]] Window* GetWindow() const noexcept { return m_pWindow.get(); }

		/// @brief レンダラー取得
		/// @return レンダラーのポインタ
		[[nodiscard]] RHI::Renderer* GetRenderer() const noexcept { return m_pRenderer.get(); }

		/// @brief エディター取得
		/// @return エディターのポインタ
		[[nodiscard]] Editor* GetEditor() const noexcept { return m_pEditor.get(); }

		/// @brief シーンマネージャーの取得
		/// @return シーンマネージャーのポインタ
		[[nodiscard]] SceneManager* GetSceneManager() const noexcept { return m_pSceneManager.get(); }

		/// @brief ウィンドウ名取得
		/// @return ウィンドウ名
		[[nodiscard]] Util::String GetWindowName() const noexcept { return m_pWindow->GetWindowName(); }

		/// @brief ウィンドウの幅取得
		/// @return ウィンドウの幅(整数)
		[[nodiscard]] int GetWindowWidth() const noexcept { return m_pWindow->GetWindowWidth(); }

		/// @brief ウィンドウの高さ取得
		/// @return ウィンドウの高さ(整数)
		[[nodiscard]] int GetWindowHeight() const noexcept { return m_pWindow->GetWindowHeight(); }

		/// @brief 現在のフレームレート取得
		/// @return フレームレート(整数)
		[[nodiscard]] std::uint32_t GetCurrentFPS() const noexcept { return m_nCurrentFPS; }

	private:
		//------------------------------------------------------------------------------
		// private methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		Engine();

		/// @brief デストラクタ
		~Engine() = default;

	private:
		//------------------------------------------------------------------------------
		// private variables
		//------------------------------------------------------------------------------

		std::unique_ptr<Window>					m_pWindow;				///< ウィンドウ
		std::unique_ptr<RHI::Renderer>			m_pRenderer;			///< レンダラー
		std::unique_ptr<Editor>					m_pEditor;				///< エディター

		std::unique_ptr<SceneManager>			m_pSceneManager;		///< シーンマネージャー
		///< リソースマネージャー
		///< エディタマネージャー

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
