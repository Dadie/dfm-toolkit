/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once

// Ext

// Std
#include <bitset>
#include <cassert>
#include <functional>

// Own

namespace dfm::utils
{
    template < size_t N >
    struct simple_nfa
    {
        static_assert(N > 0, "simple_nfa needs at least one state");
        std::bitset< N + 1 > __states;

        simple_nfa& operator|=(const simple_nfa& nfa)
        {
            __states |= nfa.__states;
            return *this;
        }

        bool ok() const
        {
            return __states.any();
        }

        bool accept() const
        {
            return __states[ N ];
        }

        constexpr std::size_t size() const noexcept
        {
            return __states.size();
        }
        constexpr bool operator[](std::size_t pos) const
        {
            return __states[ pos ];
        }
        typename std::bitset< N + 1 >::reference operator[](std::size_t pos)
        {
            return __states[ pos ];
        }
    };

    template < size_t N, typename UnaryPredicate >
    simple_nfa< N > simple_nfa_delta(
        const char c, const simple_nfa< N >& nfa, const size_t from, const size_t to, UnaryPredicate pred)
    {
        assert(from < nfa.size());
        assert(to < nfa.size());
        simple_nfa< N > next;
        if (!nfa[ from ])
        {
            return next;
        }
        if (!pred(c))
        {
            return next;
        }
        next[ to ] = true;
        return next;
    }

    inline constexpr size_t simple_nfa_state(const size_t i)
    {
        return i;
    }

    inline std::function< bool(const char) > simple_nfa_match_chars(const std::string& chars)
    {
        return [ = ](const char c) -> bool { return chars.find(c) != chars.npos; };
    }

    inline std::function< bool(const char) > simple_nfa_match_not_chars(const std::string& chars)
    {
        return [ = ](const char c) -> bool { return chars.find(c) == chars.npos; };
    }

}
