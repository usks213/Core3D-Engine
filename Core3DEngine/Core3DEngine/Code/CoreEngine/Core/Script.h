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
#define DECLARE_SCRIPT_INFO(T) 								\
public:														\
	static constexpr std::string_view GetScriptTypeString()	\
	{														\
		return #T;											\
	}														\
	static constexpr ScriptID GetScriptTypeID()				\
	{														\
		return static_cast<ScriptID>(util::stringHash(#T));	\
	}														\
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
		Component("Script"), m_scriptID(MAX_SCRIPT_ID)
	{
	}

	/// @brief デストラクタ
	virtual ~Script() noexcept = default;

private:

	/// @brief スクリプトタイプID
	ScriptID m_scriptID;

};



#endif // !_SCRIPT_


