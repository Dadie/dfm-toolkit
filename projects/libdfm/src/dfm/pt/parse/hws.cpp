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
#include <dfm/pt/parse_error.h>
#include <dfm/utils/debug.h>

dfm::pt::node dfm::pt::parse::hws(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "HWS := (' '|'\\t')*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::HWS;
        n.rule = RULE;

        auto i = pos;

        do
        {
            if (tokens.at(i) == dfm::lexer::token::SPACE)
            {
                n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::SPACE, tokens, i));
                i += n.children.back().offset();
                break;
            }

            if (tokens.at(i) == dfm::lexer::token::TABULATOR)
            {
                n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::TABULATOR, tokens, i));
                i += n.children.back().offset();
                break;
            }

            break;
        } while (false);
    }
    return n;
}
