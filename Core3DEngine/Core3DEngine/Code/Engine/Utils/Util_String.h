/*****************************************************************//**
 * \file   Util_String.h
 * \brief  ������^
 * 
 * \author USAMI KOSHI
 * \date   2021/11/04
 *********************************************************************/
#ifndef _UTIL_STRING_
#define _UTIL_STRING_

#include <string>

namespace Util
{
#ifdef _UNICODE
	/// @brief Unicode������^
	using String = std::wstring;
#else
	/// @brief �}���`�o�C�g������^
	using String = std::string;
#endif // !_UNICODE
}

#endif // !_UTIL_STRING_
