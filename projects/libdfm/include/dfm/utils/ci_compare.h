/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <string>

// Own
#include <dfm/lexer/token.h>

namespace dfm::utils
{
    inline int ci_compare(const dfm::lexer::token_type& str1, const dfm::lexer::token_type& str2)
    {
        return str1.compare(str2);
    }
    inline bool ci_eq(const dfm::lexer::token_type& str1, const dfm::lexer::token_type& str2)
    {
        return ci_compare(str1, str2) == 0;
    }
    inline bool ci_lt(const dfm::lexer::token_type& str1, const dfm::lexer::token_type& str2)
    {
        return ci_compare(str1, str2) < 0;
    }
    inline bool ci_gt(const dfm::lexer::token_type& str1, const dfm::lexer::token_type& str2)
    {
        return ci_compare(str1, str2) > 0;
    }
    inline bool ci_ltoe(const dfm::lexer::token_type& str1, const dfm::lexer::token_type& str2)
    {
        return ci_compare(str1, str2) <= 0;
    }
    inline bool ci_gtoe(const dfm::lexer::token_type& str1, const dfm::lexer::token_type& str2)
    {
        return ci_compare(str1, str2) >= 0;
    }

    int ci_compare(const std::string& str1, const std::string& str2);
    inline bool ci_eq(const std::string& str1, const std::string& str2)
    {
        return ci_compare(str1, str2) == 0;
    }
    inline bool ci_lt(const std::string& str1, const std::string& str2)
    {
        return ci_compare(str1, str2) < 0;
    }
    inline bool ci_gt(const std::string& str1, const std::string& str2)
    {
        return ci_compare(str1, str2) > 0;
    }
    inline bool ci_ltoe(const std::string& str1, const std::string& str2)
    {
        return ci_compare(str1, str2) <= 0;
    }
    inline bool ci_gtoe(const std::string& str1, const std::string& str2)
    {
        return ci_compare(str1, str2) >= 0;
    }
}
