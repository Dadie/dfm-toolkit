/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <memory>
#include <string>
#include <string_view>

// Own

namespace dfm::utils
{
    template < typename CharT, typename Traits, typename Allocator >
    std::basic_string< CharT, Traits, Allocator > replace_all(const std::basic_string< CharT, Traits, Allocator >& str,
        const std::basic_string_view< CharT, Traits >& needle,
        const std::basic_string_view< CharT, Traits >& replacement);

    template < typename CharT,
        typename Traits = std::char_traits< CharT >,
        typename Allocator = std::allocator< CharT > >
    std::basic_string< CharT, Traits, Allocator > replace_all(const std::basic_string< CharT, Traits, Allocator >& str,
        const std::basic_string< CharT, Traits >& needle,
        const std::basic_string< CharT, Traits >& replacement);
}

template < typename CharT, typename Traits, typename Allocator >
std::basic_string< CharT, Traits, Allocator > dfm::utils::replace_all(
    const std::basic_string< CharT, Traits, Allocator >& str,
    const std::basic_string_view< CharT, Traits >& needle,
    const std::basic_string_view< CharT, Traits >& replacement)
{
    const auto npos = std::basic_string< CharT, Traits, Allocator >::npos;
    auto out = str;
    size_t pos = 0;
    while ((pos = out.find(needle, pos)) != npos)
    {
        out.replace(pos, needle.size(), replacement);
        pos += replacement.size();
    }
    return out;
}

template < typename CharT, typename Traits = std::char_traits< CharT >, typename Allocator = std::allocator< CharT > >
std::basic_string< CharT, Traits, Allocator > dfm::utils::replace_all(
    const std::basic_string< CharT, Traits, Allocator >& str,
    const std::basic_string< CharT, Traits >& needle,
    const std::basic_string< CharT, Traits >& replacement)
{
    const auto npos = std::basic_string< CharT, Traits, Allocator >::npos;
    auto out = str;
    size_t pos = 0;
    while ((pos = out.find(needle, pos)) != npos)
    {
        out.replace(pos, needle.size(), replacement);
        pos += replacement.size();
    }
    return out;
}
