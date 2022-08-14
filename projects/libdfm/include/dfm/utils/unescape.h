/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <charconv>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>

// Own
#include <dfm/lexer/token.h>
#include <dfm/utils/replace.h>
#include <dfm/utils/unescape.h>

namespace dfm::utils
{
    template < typename CharT, typename Traits, typename Allocator >
    std::basic_string< CharT, Traits, Allocator > unescape(const std::basic_string< CharT, Traits, Allocator >& str)
    {

        return dfm::utils::replace_all(
            str, std::basic_string_view< CharT, Traits >("''"), std::basic_string_view< CharT, Traits >("'"));
    }

    template < typename CharT, typename Traits, typename Allocator >
    std::u16string unescape_control_string(const std::basic_string< CharT, Traits, Allocator >& ctl_str)
    {
        using namespace std::literals::string_literals;
        std::u16string out;
        auto* ctl_pos = ctl_str.c_str();
        const auto* ctl_end = ctl_pos + ctl_str.size();
        while (ctl_pos < ctl_end)
        {
            int c {};
            int base = 10;
            if (*ctl_pos == '#')
            {
                ++ctl_pos;
                if (ctl_pos >= ctl_end)
                {
                    throw std::runtime_error("Bad control string '"s + ctl_str.c_str() + "'"s);
                }
                if (*ctl_pos == '$')
                {
                    ++ctl_pos;
                    base = 16;
                }
                if (ctl_pos >= ctl_end)
                {
                    throw std::runtime_error("Bad control string '"s + ctl_str.c_str() + "'"s);
                }
                const auto r = std::from_chars(ctl_pos, ctl_end, c, base);
                if (r.ec == std::errc::invalid_argument)
                {
                    throw std::runtime_error("Bad control string '"s + ctl_str.c_str() + "'"s);
                }
                out += static_cast< char16_t >(c);
                ctl_pos = r.ptr;
            }
            else
            {
                ++ctl_pos;
            }
        }
        return out;
    }
}
