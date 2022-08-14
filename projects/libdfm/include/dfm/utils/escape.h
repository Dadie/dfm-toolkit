/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cstdint>
#include <locale>
#include <string>
#include <string_view>

// Own
#include <dfm/utils/iconv.h>
#include <dfm/utils/replace.h>

namespace dfm::utils
{
    template < typename CharT, typename Traits, typename Allocator >
    std::basic_string< CharT, Traits, Allocator > escape(const std::basic_string< CharT, Traits, Allocator >& str)
    {
        using StrType = std::basic_string< CharT, Traits, Allocator >;
        using StrViewType = std::basic_string_view< CharT, Traits >;

        if (str.empty())
        {
            return StrType("''");
        }
        const auto str0 = dfm::utils::replace_all(str, StrViewType("'"), StrViewType("''"));
        const auto u16_str1 = dfm::utils::iconv::u8_to_u16le(str0);
        std::u16string u16_str2;
        {
            bool str_mode = false;
            for (const auto& c : u16_str1)
            {
                if (std::isprint(c, std::locale()))
                {
                    if (!str_mode)
                    {
                        u16_str2 += '\'';
                    }
                    str_mode = true;
                    u16_str2 += c;
                }
                else
                {
                    if (str_mode)
                    {
                        u16_str2 += '\'';
                    }
                    str_mode = false;
                    const auto num_str = std::to_string(+c);
                    u16_str2 += '#';
                    u16_str2 += dfm::utils::iconv::u8_to_u16le(num_str);
                }
            }
            if (str_mode)
            {
                u16_str2 += '\'';
            }
        }
        const auto str3 = dfm::utils::iconv::u16le_to_u8(u16_str2);
        return str3.c_str();
    }
}
