/*****************************************************************//**
 * \file   Core_String.h
 * \brief  ������^
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
	/// @brief Unicode������^
	class CoreString : public std::wstring
#elif
	/// @brief �}���`�o�C�g������^
	class CoreString : public std::string
#endif // !_UNICODE
	{

	};
}

#endif // !_CORE_STRING_
