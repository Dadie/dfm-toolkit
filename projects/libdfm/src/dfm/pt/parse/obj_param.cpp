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

static dfm::pt::node obj_param_1(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "OBJ_PARAM := <WS>* <OBJ> <WS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::OBJ_PARAM;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::obj(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);
    }
    return n;
}

static dfm::pt::node obj_param_2(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "OBJ_PARAM := <WS>* <OBJ_PARAM_NAME> <WS>* '=' <WS>* <VALUE> <WS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::OBJ_PARAM;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::obj_param_name(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::EQUAL, tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::value(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);
    }
    return n;
}

dfm::pt::node dfm::pt::parse::obj_param(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    std::vector< dfm::pt::node > results;
    std::vector< std::string > whats;
    std::vector< std::function< dfm::pt::node(const std::vector< dfm::lexer::token_type >, const size_t) > > fns;
    {
        fns.push_back(obj_param_1);
        fns.push_back(obj_param_2);
    }

    for (const auto& fn : fns)
    {
        try
        {
            results.push_back(fn(tokens, pos));
        }
        catch (const std::exception& x)
        {
            whats.push_back(x.what());
        }
    }

    std::sort(results.begin(), results.end(), [](auto a, auto b) { return a.offset() < b.offset(); });

    if (!results.empty())
    {
        return results.back();
    }

    assert(!whats.empty());
    throw dfm::pt::parse_error(whats);
}
