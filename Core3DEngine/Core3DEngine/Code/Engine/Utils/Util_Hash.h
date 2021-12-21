/*****************************************************************//**
 * \file   Util_Hash.h
 * \brief  �n�b�V���֐�
 * 
 * \author USAMI KOSHI
 * \date   2021/10/06
 *********************************************************************/
#ifndef _UTIL_HASH_
#define _UTIL_HASH_

#include <cstdint>
#include <string_view>

 /// @brief �^�̕�����
#define TYPE_STRING(T) #T

namespace Util
{
    /// @brief ������̃n�b�V���l
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

    /// @brief �^�̃n�b�V���l
    template<class T>
    constexpr std::uint32_t typeHash()
    {
        return stringHash(TYPE_STRING(T));
    }
}

#endif // !_UTIL_HASH_

