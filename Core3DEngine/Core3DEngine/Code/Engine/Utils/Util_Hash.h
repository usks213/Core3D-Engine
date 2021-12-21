/*****************************************************************//**
 * \file   Util_Hash.h
 * \brief  ハッシュ関数
 * 
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/
#ifndef _UTIL_HASH_
#define _UTIL_HASH_

#include <cstdint>
#include <string_view>

 /// @brief 型の文字列
#define TYPE_STRING(T) #T

namespace Util
{
    /// @brief 文字列のハッシュ値
    constexpr std::uint32_t stringHash(std::string_view string)
    {
        auto fnvOffSetBasis = 14695981039346656037ULL;
        constexpr auto cFnvPrime = 1099511628211ULL;

        for (auto idx : string)
        {
            fnvOffSetBasis ^= static_cast<std::uint32_t>(idx);
            fnvOffSetBasis *= cFnvPrime;
        }
        return static_cast<std::uint32_t>(fnvOffSetBasis);
    }

    /// @brief 型のハッシュ値
    template<class T>
    constexpr std::uint32_t typeHash()
    {
        return stringHash(TYPE_STRING(T));
    }
}

#endif // !_UTIL_HASH_

