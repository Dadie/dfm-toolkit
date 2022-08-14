/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cstddef>
#include <cstdint>
#include <iostream>

// Own

bool SHOW_DEBUG();

template < typename __FuncType, typename __TokenType, typename __PosType, typename __RuleType >
constexpr void __TOKEN_DEBUG(
    const __FuncType& __FUNC, const __TokenType& __TOKENS, const __PosType& __POS, const __RuleType& __RULE)
{
    if (!SHOW_DEBUG())
    {
        return;
    }

    constexpr size_t debug_context = 10;
    auto& debug_ostream = std::clog;
    debug_ostream << "In:" << __FUNC << std::endl;
    debug_ostream << "Rule:" << (__RULE) << std::endl;
    debug_ostream << "Pos:" << (__POS) << std::endl;
    if (__POS < __TOKENS.size())
    {
        debug_ostream << "Curr Token:" << (__TOKENS).at(__POS) << std::endl;
        debug_ostream << "Env Tokens:";

        const size_t fst_debug_idx = ((__POS) < debug_context) ? 0 : ((__POS) - (debug_context / 2));
        for (size_t t_la = 0; (t_la < debug_context) && ((fst_debug_idx + t_la) < (__TOKENS).size()); ++t_la)
        {
            if (t_la != 0)
            {
                debug_ostream << " -> ";
            }
            if (fst_debug_idx + t_la == (__POS))
            {
                debug_ostream << "[";
            }
            debug_ostream << (__TOKENS).at(fst_debug_idx + t_la);
            if (fst_debug_idx + t_la == (__POS))
            {
                debug_ostream << "]";
            }
        }
    }
    else
    {
        debug_ostream << "Curr Token:"
                      << "Out-Of-Tokens" << std::endl;
        debug_ostream << "Env Tokens:"
                      << "Out-Of-Tokens";
    }
    debug_ostream << std::endl;
    debug_ostream << std::endl;
}

#define __DEBUG_VALUE(a)                                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        std::cout << #a << ":" << a << " "                                                                             \
                  << "in " << __FILE__ << ":" << __LINE__ << std::endl;                                                \
    } while (false)
