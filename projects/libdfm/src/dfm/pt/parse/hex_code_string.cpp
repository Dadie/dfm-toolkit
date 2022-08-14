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

dfm::pt::node dfm::pt::parse::hex_code_string(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "HEX_CODE_STRING := [0-9A-Fa-f]+";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::HEX_CODE_STRING;
        n.rule = RULE;

        for (const auto& c : tokens.at(pos))
        {
            // HOTFIX: Using RegEx here seems to crash on long strings
            if (c >= '0' && c <= '9')
            {
                continue;
            }
            if (c >= 'A' && c <= 'F')
            {
                continue;
            }
            if (c >= 'a' && c <= 'f')
            {
                continue;
            }
            throw dfm::pt::parse_error(RULE, tokens.at(pos), pos, dfm::pt::ntypes::HEX_CODE_STRING);
        }
        n.token = tokens.at(pos);
    }
    return n;
}
