/*****************************************************************//**
 * \file   RHI_Renderer.h
 * \brief  レンダラークラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/
#ifndef _RHI_RENDERER_
#define _RHI_RENDERER_

#include <memory>

namespace Core::RHI
{
	// 前宣言
	class Engine;
	class Device;
	class CommandList;

	/// @brief レンダラーのベースクラス
	/// @class Renderer
	class Renderer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit Renderer() :
			m_pEngine(nullptr)
		{
		}

		/// @brief デストラクタ
		virtual ~Renderer() noexcept = default;

		/// @brief 終了処理
		virtual void finalize() = 0;

		/// @brief フレーム開始
		virtual void beginFrame() = 0;
		/// @brief フレーム終了
		virtual void endFrame() = 0;


		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		Engine* GetEngine() const noexcept { return m_pEngine; }

		/// @brief エンジンの設定
		/// @param pEngine エンジンのポインタ
		void SetEngine(Engine* pEngine) noexcept { m_pEngine = pEngine; }

		/// @brief デバイスの取得
		/// @return デバイスのポインタ
		virtual Device* GetDevice() = 0;

		/// @brief コマンドリストの取得
		/// @return コマンドリストのポインタ
		virtual CommandList* GetCommandList() = 0;

		/// @brief コピーコンストラクタ削除
		Renderer(const Renderer&) = delete;
		/// @brief ムーブコンストラクタ削除
		Renderer(Renderer&&) = delete;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		Engine* m_pEngine;	///< エンジンのポインタ

		///< デバイスクラス

		///< コンテストクラス

	};
}

#endif // !_RHI_RENDERER_
