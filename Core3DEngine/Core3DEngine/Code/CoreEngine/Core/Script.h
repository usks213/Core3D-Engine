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
	static constexpr ScriptID GetScriptTypeID()						\
	{																\
		return static_cast<ScriptID>(util::stringHash(#T));			\
	}																\
[[nodiscard]] ScriptID GetScriptID() noexcept override {			\
	return static_cast<ScriptID>(GetScriptTypeID());				\
}																	\
[[nodiscard]] std::string_view GetScriptName() noexcept override {	\
	return GetScriptTypeString();									\
}																	\
	void _dumyFunction3() = delete


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

	/// @brief スクリプトIDの取得
	[[nodiscard]] virtual ScriptID GetScriptID() noexcept = 0;

	/// @brief スクリプト名の取得
	[[nodiscard]] virtual std::string_view GetScriptName() noexcept = 0;

public:
	//--- コールバック関数

	virtual void OnCreate() override {}		///< 生成リスト格納時
	virtual void OnDestroy() override {}	///< 削除リスト格納時

	virtual void OnEnable() override {}		///< 有効時
	virtual void OnDisable() override {}	///< 無効時

	virtual void OnStart() override {}		///< 初回更新前に一度

private:

};



#endif // !_SCRIPT_


