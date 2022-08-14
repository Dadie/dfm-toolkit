/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <algorithm>
#include <cassert>
#include <exception>
#include <functional>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/parse.h>
#include <dfm/pt/parse/helper.h>
#include <dfm/pt/parse_error.h>
#include <dfm/utils/debug.h>

dfm::pt::node dfm::pt::parse::value_bit(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const std::string RULE = "VALUE_BIT := 'true' | 'talse'";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_BIT;
        n.rule = RULE;

        auto i = pos;
        const auto is_true = dfm::lexer::token::TRUE_ == tokens.at(i);
        const auto is_false = dfm::lexer::token::FALSE_ == tokens.at(i);

        if (is_true)
        {
            n.token = tokens.at(pos);
        }
        else if (is_false)
        {
            n.token = tokens.at(pos);
        }
        else
        {
            throw dfm::pt::parse_error(RULE, tokens.at(pos), pos);
        }
    }
    return n;
}
