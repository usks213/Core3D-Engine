/*****************************************************************//**
 * \file   Util_String.h
 * \brief  Άρ^
 * 
 * \author USAMI KOSHI
 * \date   2021/11/04
 *********************************************************************/
#ifndef _UTIL_STRING_
#define _UTIL_STRING_

#include <string>

namespace util
{
#ifdef _UNICODE
	/// @brief UnicodeΆρ^
	using String = std::wstring;
#elif
	/// @brief }`oCgΆρ^
	using String = std::string;
#endif // !_UNICODE
}

#endif // !_UTIL_STRING_
