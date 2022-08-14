/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <string_view>

// Own

namespace dfm::utils
{
    template < typename CharT >
    struct char_ci_traits : public std::char_traits< CharT >
    {
        static CharT to_upper(CharT ch);
        static bool eq(CharT c1, CharT c2);
        static bool lt(CharT c1, CharT c2);
        static int compare(const CharT* s1, const CharT* s2, std::size_t n);
        static const CharT* find(const CharT* s, std::size_t n, CharT a);
    };

    using ci_string = std::basic_string< char, char_ci_traits< char > >;
    using ci_string_view = std::basic_string_view< char, char_ci_traits< char > >;
}

template < typename CharT >
CharT dfm::utils::char_ci_traits< CharT >::to_upper(CharT ch)
{
    return std::toupper(ch, std::locale());
}

template < typename CharT >
bool dfm::utils::char_ci_traits< CharT >::eq(CharT c1, CharT c2)
{
    return to_upper(c1) == to_upper(c2);
}

template < typename CharT >
bool dfm::utils::char_ci_traits< CharT >::lt(CharT c1, CharT c2)
{
    return to_upper(c1) < to_upper(c2);
}

template < typename CharT >
int dfm::utils::char_ci_traits< CharT >::compare(const CharT* s1, const CharT* s2, std::size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (lt(s1[ i ], s2[ i ]))
        {
            return -1;
        }
        if (lt(s2[ i ], s1[ i ]))
        {
            return 1;
        }
    }
    return 0;
}

template < typename CharT >
const CharT* dfm::utils::char_ci_traits< CharT >::find(const CharT* s, std::size_t n, CharT a)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (eq(s[ i ], a))
        {
            return s + i;
        }
    }
    return nullptr;
}

inline std::ostream& operator<<(std::ostream& os, const dfm::utils::ci_string& str)
{
    os << str.c_str();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const dfm::utils::ci_string_view& sv)
{
    os.write(sv.data(), sv.size());
    return os;
}
