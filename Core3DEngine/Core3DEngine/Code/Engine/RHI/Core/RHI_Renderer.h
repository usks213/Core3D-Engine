/*****************************************************************//**
 * \file   RHI_Renderer.h
 * \brief  レンダラークラス
 * 
 * \author USAMI KOSHI
 * \date   2021/10/01
 *********************************************************************/

#ifndef _CORE_RENDERER_
#define _CORE_RENDERER_

#include <memory>

namespace Core::RHI
{
	// 前宣言
	class Engine;
	class Device;
	class CommandList;

	/// @brief レンダラーのベースクラス
	/// @class RHI
	class RHI
	{
	public:
		//------------------------------------------------------------------------------
		// public methods
		//------------------------------------------------------------------------------

		/// @brief コンストラクタ
		explicit RHI() :
			m_pCoreEngine(nullptr)
		{
		}

		/// @brief デストラクタ
		virtual ~RHI() noexcept = default;

		/// @brief 終了処理
		virtual void finalize() = 0;

		/// @brief フレーム開始
		virtual void beginFrame() = 0;
		/// @brief フレーム終了
		virtual void endFrame() = 0;


		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		Engine* GetEngine() const noexcept { return m_pCoreEngine; }

		/// @brief エンジンの設定
		/// @param pCoreEngine エンジンのポインタ
		void SetEngine(Engine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief デバイスの取得
		/// @return デバイスのポインタ
		virtual Device* getDevice() = 0;

		/// @brief コマンドリストの取得
		/// @return コマンドリストのポインタ
		virtual CommandList* getCommandList() = 0;

		/// @brief コピーコンストラクタ削除
		RHI(const RHI&) = delete;
		/// @brief ムーブコンストラクタ削除
		RHI(RHI&&) = delete;

	protected:
		//------------------------------------------------------------------------------
		// protected variables
		//------------------------------------------------------------------------------

		Engine* m_pCoreEngine;	///< エンジンのポインタ

		///< デバイスクラス

		///< コンテストクラス

	};
}

#endif // !_CORE_RENDERER_
