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
#include <dfm/utils/debug.h>

dfm::pt::node dfm::pt::parse::any_chars(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "ANY_CHARS := ...";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::ANY_CHARS;
        n.rule = RULE;

        n.token = tokens.at(pos);
    }
    return n;
}
