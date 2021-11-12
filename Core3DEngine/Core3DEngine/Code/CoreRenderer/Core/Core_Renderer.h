/*****************************************************************//**
 * \file   Core_Renderer.h
 * \brief  レンダラークラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_RENDERER_
#define _CORE_RENDERER_

#include <memory>

namespace core
{
	// 前宣言
	class CoreEngine;
	class CoreDevice;
	class CoreCommandList;

	/// @brief レンダラーのベースクラス
	/// @class CoreRenderer
	class CoreRenderer
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit CoreRenderer() :
			m_pCoreEngine(nullptr)
		{
		}

		/// @brief デストラクタ
		virtual ~CoreRenderer() noexcept = default;

		/// @brief 終了処理
		virtual void finalize() = 0;

		/// @brief フレーム開始
		virtual void beginFrame() = 0;
		/// @brief フレーム終了
		virtual void endFrame() = 0;


		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		CoreEngine* getCoreEngine() const noexcept { return m_pCoreEngine; }

		/// @brief エンジンの設定
		/// @param pCoreEngine エンジンのポインタ
		void setCoreEngine(CoreEngine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief デバイスの取得
		/// @return デバイスのポインタ
		virtual CoreDevice* getDevice() = 0;

		/// @brief コマンドリストの取得
		/// @return コマンドリストのポインタ
		virtual CoreCommandList* getCommandList() = 0;

		/// @brief コピーコンストラクタ削除
		CoreRenderer(const CoreRenderer&) = delete;
		/// @brief ムーブコンストラクタ削除
		CoreRenderer(CoreRenderer&&) = delete;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		CoreEngine* m_pCoreEngine;	///< エンジンのポインタ

		///< デバイスクラス

		///< コンテストクラス

	};
}

#endif // !_CORE_RENDERER_
