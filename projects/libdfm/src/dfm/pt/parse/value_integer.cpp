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

static dfm::pt::node value_integer_1(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE_INTEGER := ('-'|'+')? [0-9]+";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_INTEGER;
        n.rule = RULE;

        constexpr const char* regex_str = "(-|\\+)?[0-9]+";
        const std::regex regexpr { regex_str };
        if (!std::regex_match(tokens.at(pos), regexpr))
        {
            throw dfm::pt::parse_error(RULE, tokens.at(pos), pos, dfm::pt::ntypes::VALUE_INTEGER);
        }
        n.token = tokens.at(pos);
    }
    return n;
}

static dfm::pt::node value_integer_2(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE_INTEGER := '$' [a-fA-F0-9]+";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_INTEGER;
        n.rule = RULE;

        constexpr const char* regex_str = "\\$[a-fA-F0-9]+";
        const std::regex regexpr { regex_str };
        if (!std::regex_match(tokens.at(pos), regexpr))
        {
            throw dfm::pt::parse_error(RULE, tokens.at(pos), pos, dfm::pt::ntypes::VALUE_INTEGER);
        }
        n.token = tokens.at(pos);
    }
    return n;
}

dfm::pt::node dfm::pt::parse::value_integer(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    std::vector< dfm::pt::node > results;
    std::vector< std::string > whats;
    std::vector< std::function< dfm::pt::node(const std::vector< dfm::lexer::token_type >, const size_t) > > fns;
    {
        fns.push_back(&value_integer_1);
        fns.push_back(&value_integer_2);
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
