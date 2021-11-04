/*****************************************************************//**
 * \file   Core_String.h
 * \brief  •¶Žš—ñŒ^
 * 
 * \author USAMI KOSHI
 * \date   2021/11/04
 *********************************************************************/
#ifndef _CORE_STRING_
#define _CORE_STRING_

#include <string>

namespace core
{
#ifdef _UNICODE
	/// @brief Unicode•¶Žš—ñŒ^
	class CoreString : public std::wstring
#elif
	/// @brief ƒ}ƒ‹ƒ`ƒoƒCƒg•¶Žš—ñŒ^
	class CoreString : public std::string
#endif // !_UNICODE
	{

	};
}

#endif // !_CORE_STRING_
