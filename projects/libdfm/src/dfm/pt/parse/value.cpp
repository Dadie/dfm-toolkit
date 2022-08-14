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

static dfm::pt::node value_1(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_INTEGER>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_integer(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_2(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_FLOAT>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_float(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_3(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_BIT>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_bit(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_4(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_CONSTANT>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_constant(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_5(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_STRING>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_string(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_7(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_BINARY>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_binary(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_8(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_SET>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_set(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_9(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_ARRAY>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_array(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_10(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_DATETIME>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_datetime(tokens, pos));
    }
    return n;
}

static dfm::pt::node value_11(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE := <VALUE_INLINE_OBJECT>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE;
        n.rule = RULE;

        n.children.push_back(dfm::pt::parse::value_inline_object(tokens, pos));
    }
    return n;
}

dfm::pt::node dfm::pt::parse::value(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    std::vector< dfm::pt::node > results;
    std::vector< std::string > whats;
    std::vector< std::function< dfm::pt::node(const std::vector< dfm::lexer::token_type >, const size_t) > > fns;
    {
        fns.push_back(value_1);
        fns.push_back(value_2);
        fns.push_back(value_3);
        fns.push_back(value_4);
        fns.push_back(value_5);
        fns.push_back(value_7);
        fns.push_back(value_8);
        fns.push_back(value_9);
        fns.push_back(value_10);
        fns.push_back(value_11);
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
