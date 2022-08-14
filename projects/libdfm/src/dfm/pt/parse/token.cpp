/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
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
#include <dfm/pt/rule.h>
#include <dfm/utils/debug.h>

dfm::pt::node dfm::pt::parse::token(const dfm::pt::rule_type& rule,
    const dfm::lexer::token_type& token,
    const std::vector< dfm::lexer::token_type >& tokens,
    const size_t pos)
{
    using namespace std::string_literals;
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, ("TOKEN := "s + token.c_str()));
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, ("TOKEN := "s + token.c_str()));

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::TOKEN;
        if (tokens.at(pos) != token)
        {
            throw dfm::pt::parse_error(rule, tokens.at(pos), pos, token);
        }
        n.token = token;
    }
    return n;
}
