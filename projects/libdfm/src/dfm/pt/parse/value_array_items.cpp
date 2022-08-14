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

dfm::pt::node dfm::pt::parse::value_array_items(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE_ARRAY_ITEMS := <WS>* <VALUE_ARRAY_ITEM>* <WS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_ARRAY_ITEMS;
        n.rule = RULE;

        try
        {
            auto i = pos;
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);

            do
            {
                n.children.push_back(dfm::pt::parse::value_array_item(tokens, i));
                i += n.children.back().offset();
                i += dfm::pt::parse::consume_whitespace(n, tokens, i);
            } while (true);
        }
        catch (const std::exception&)
        {
            // End of Params found (most likely)
        }
    }
    return n;
}
