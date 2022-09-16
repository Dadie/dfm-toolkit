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

dfm::pt::node dfm::pt::parse::obj_params(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "OBJ_PARAMS := <WS>* <OBJ_PARAM>* <WS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::OBJ_PARAMS;
        n.rule = RULE;

        try
        {
            auto i = pos;
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);
            do
            {
                n.children.push_back(dfm::pt::parse::obj_param(tokens, i));
                i += n.children.back().offset();
                i += dfm::pt::parse::consume_whitespace(n, tokens, i);
            } while (true);
        }
        catch (const std::exception& ex)
        {
            // End of Params found (most likely)
        }
    }
    return n;
}
