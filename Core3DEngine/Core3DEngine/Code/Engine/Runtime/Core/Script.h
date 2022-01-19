/*****************************************************************//**
 * \file   Script.h
 * \brief  スクリプト
 *
 * \author USAMI KOSHI
 * \date   2021/11/15
 *********************************************************************/
#ifndef _SCRIPT_
#define _SCRIPT_

#include "Component.h"

 /// @brief 型情報付加
#define DECLARE_SCRIPT_INFO(T) 										\
public:																\
	static constexpr std::string_view GetScriptTypeString()			\
	{																\
		return #T;													\
	}																\
	static constexpr TypeHash GetScriptTypeHash()					\
	{																\
		return static_cast<TypeHash>(Util::stringHash(#T));			\
	}																\
[[nodiscard]] ScriptTypeID GetScriptTypeID() noexcept override {	\
	return static_cast<ScriptTypeID>(GetScriptTypeHash());			\
}																	\
[[nodiscard]] std::string_view GetScriptName() noexcept override {	\
	return GetScriptTypeString();									\
}																	\
using T##ID = Component::ID


namespace Core
{
	/// @brief スクリプトクラス
	class Script : public Component
	{
		friend class Entity;
	public:
		/// @brief オブジェクト情報
		DECLARE_OBJECT_INFO(Script);
	public:

		/// @brief コンストラクタ
		explicit Script() noexcept :
			Component()
		{
		}

		/// @brief デストラクタ
		virtual ~Script() noexcept = default;

		/// @brief スクリプトタイプの取得
		[[nodiscard]] virtual ScriptTypeID GetScriptTypeID() noexcept = 0;

		/// @brief スクリプト名の取得
		[[nodiscard]] virtual std::string_view GetScriptName() noexcept = 0;

	private:

		/// @brief コンポーネント名の取得(スクリプト継承先も)
		/// @return コンポーネント名
		std::string_view GetComponentName() noexcept override
		{
			return GetScriptName();
		}

	public:
		//--- コールバック関数

		virtual void OnCreate() override {}		///< 生成リスト格納時
		virtual void OnDestroy() override {}	///< 削除リスト格納時

		virtual void OnEnable() override {}		///< 有効時
		virtual void OnDisable() override {}	///< 無効時

		virtual void OnStart() override {}		///< 初回更新前に一度

		/// @brief インスペクター表示
		virtual void OnInspectorGUI() override {}

	private:

	};
}


#endif // !_SCRIPT_


