/*****************************************************************//**
 * \file   Core_Editor.h
 * \brief  コアエディター
 *
 * \author USAMI KOSHI
 * \date   2021/11/23
 *********************************************************************/
#ifndef _CORE_EDITOR_
#define _CORE_EDITOR_

#include "Core/EditorWindowManager.h"
#include <CoreEngine\Core\TypeID.h>

namespace core
{
	class CoreEngine;
	class CoreCommandList;

	/// @brief コアエディタークラス
	class CoreEditor
	{
	public:
		/// @brief 選択中のオブジェクト
		struct SelectObject
		{
			enum class ObjectType
			{
				Entity,
				Resource,
				MaxType,
			};
			InstanceID	instanceID = NONE_INSTANCE_ID;
			ObjectType	objectType = ObjectType::MaxType;
		};
	public:
		/// @brief コンストラクタ
		/// @param pEngine エンジンポインタ
		explicit CoreEditor() noexcept :
			m_pCoreEngine(nullptr)
		{
			m_pEditorWindowManager = std::make_unique<EditorWindowManager>(this);
		}

		/// @brief デストラクタ
		virtual ~CoreEditor() noexcept = default;

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
		virtual void Render(CoreCommandList* cmdList) = 0;

		//--- ゲッター ---

		/// @brief エンジンの取得
		/// @return エンジンのポインタ
		CoreEngine* getCoreEngine() const noexcept { return m_pCoreEngine; }

		/// @brief エンジンの設定
		/// @param pCoreEngine エンジンのポインタ
		void setCoreEngine(CoreEngine* pCoreEngine) noexcept { m_pCoreEngine = pCoreEngine; }

		/// @brief エディターウィンドウマネージャー取得
		/// @return エディターウィンドウマネージャーポインタ
		EditorWindowManager* GetEditorWindowManager() 
		{
			return m_pEditorWindowManager.get();
		}

		/// @brief 現在選択中のオブジェクトを取得
		/// @return 選択中のオブジェクト情報
		SelectObject GetSelectObject() { return m_selectObject; }

		/// @brief 選択のオブジェクトの指定
		/// @param objectType オブジェクトタイプ
		/// @param instanceID インスタンスID
		void SetSelectObject(SelectObject::ObjectType objectType, const InstanceID& instanceID)
		{
			m_selectObject.objectType = objectType;
			m_selectObject.instanceID = instanceID;
		}

	private:
		/// @brief エンジンポインタ
		CoreEngine* m_pCoreEngine;

		/// @brief エディターウィンドウマネージャー
		std::unique_ptr<EditorWindowManager> m_pEditorWindowManager;

		/// @brief 現在選択中のオブジェクト
		SelectObject	m_selectObject;
	};
}

#endif // !_CORE_EDITOR_
