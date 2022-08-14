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
#include <dfm/utils/form/identifier.h>

dfm::pt::node dfm::pt::parse::delphi_name(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "DELPHI_NAME := <WS>* <DELPHI_IDENTIFIER>('.' <DELPHI_IDENTIFIER>)* <WS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::DELPHI_NAME;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::delphi_identifier(tokens, i));
        i += n.children.back().offset();
        while (true)
        {
            if (tokens.at(i) != dfm::lexer::token::DOT)
            {
                break;
            }
            n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::DOT, tokens, i));
            i += n.children.back().offset();

            n.children.push_back(dfm::pt::parse::delphi_identifier(tokens, i));
            i += n.children.back().offset();
        }
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);
    }
    return n;
}
