/*****************************************************************//**
 * \file   Script.h
 * \brief  �X�N���v�g
 *
 * \author USAMI KOSHI
 * \date   2021/11/15
 *********************************************************************/
#ifndef _SCRIPT_
#define _SCRIPT_

#include "Component.h"

 /// @brief �X�N���v�gID
enum class ScriptID : std::uint32_t{};
/// @brief �ő�X�N���v�gID
constexpr ScriptID MAX_SCRIPT_ID = std::numeric_limits<ScriptID>::max();


 /// @brief �^���t��
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


/// @brief �X�N���v�g�N���X
class Script : public Component
{
	friend class Entity;
public:
	/// @brief �I�u�W�F�N�g���
	DECLARE_OBJECT_INFO(Script);
public:

	/// @brief �R���X�g���N�^
	explicit Script() noexcept :
		Component("Script"), m_scriptID(MAX_SCRIPT_ID)
	{
	}

	/// @brief �f�X�g���N�^
	virtual ~Script() noexcept = default;

private:

	/// @brief �X�N���v�g�^�C�vID
	ScriptID m_scriptID;

};



#endif // !_SCRIPT_


