/*****************************************************************//**
 * \file   TypeHash.h
 * \brief  �^�n�b�V��
 * 
 * \author USAMI KOSHI
 * \date   2021/11/13
 *********************************************************************/
#ifndef _CORE_TYPEID_
#define _CORE_TYPEID_

#include <Utils/Util_Hash.h>

 /// @brief �^���t��
#define DECLARE_TYPE_INFO(T) 								\
public:														\
	static constexpr std::string_view getTypeString()		\
	{														\
		return #T;											\
	}														\
	static constexpr std::uint32_t getTypeHash()			\
	{														\
		return util::stringHash(#T);						\
	}														\
	void _dumyFunction() = delete



#endif // !_CORE_TYPEID_
