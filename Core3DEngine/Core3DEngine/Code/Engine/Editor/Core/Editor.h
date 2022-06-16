/*****************************************************************//**
 * \file   Editor.h
 * \brief  コアエディター
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _CORE_EDITOR_
#define _CORE_EDITOR_

#include "EditorWindowManager.h"

namespace Core
{
	class Engine;
	namespace RHI
	{
		class CommandList;
	}

	/// @brief コアエディタークラス
	class Editor
	{
	public:
		/// @brief コンストラクタ
		/// @param pEngine エンジンポインタ
		explicit Editor() noexcept :
			m_pEngine(nullptr)
		{
			m_pEditorWindowManager = std::make_unique<EditorWindowManager>(this);
		}

		/// @brief デストラクタ
		virtual ~Editor() noexcept = default;

		/// @brief 更新処理
		void DispEditor()
		{
			/// @brief ウィンドウの表示
			m_pEditorWindowManager->DispWindow();
		}

		/// @brief 終了処理
		virtual void finalize() = 0;

		/// @brief 新しい描画フレーム作成
		virtual void NewFrame() = 0;

		/// @brief 描画
		/// @param cmdList コマンドリスト
		virtual void Render(RHI::CommandList* cmdList) = 0;

		//--- ゲッター ---

		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		Engine* GetEngine() const noexcept { return m_pEngine; }

		/// @brief エンジンの設定
		/// @param pEngine エンジンのポインタ
		void SetEngine(Engine* pEngine) noexcept { m_pEngine = pEngine; }

		/// @brief エディターウィンドウマネージャー取得
		/// @return エディターウィンドウマネージャーポインタ
		EditorWindowManager* GetEditorWindowManager() 
		{
			return m_pEditorWindowManager.get();
		}

	private:
		/// @brief エンジンポインタ
		Engine* m_pEngine;

		/// @brief エディターウィンドウマネージャー
		std::unique_ptr<EditorWindowManager> m_pEditorWindowManager;

	};
}

#endif // !_CORE_EDITOR_
