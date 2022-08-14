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

static dfm::pt::node value_string_element_string_1(
    const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE_STRING_ELEMENT_STRING := <HWS>* '\\'' [^']* '\\'' <HWS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        if (tokens.at(i).size() < 2)
        {
            throw dfm::pt::parse_error(RULE, tokens.at(i), i, dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING);
        }

        // TODO: Check if the string really only contains two single quotation marks
        if (!tokens.at(i).starts_with(dfm::lexer::token::SINGLE_QUOTATION_MARK))
        {
            throw dfm::pt::parse_error(
                "trigger: starts not with '", RULE, tokens.at(i), i, dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING);
        }
        if (!tokens.at(i).ends_with(dfm::lexer::token::SINGLE_QUOTATION_MARK))
        {
            throw dfm::pt::parse_error(
                "trigger: ends not with '", RULE, tokens.at(i), i, dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING);
        }

        n.children.push_back(dfm::pt::parse::any_chars(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
    }
    return n;
}

static dfm::pt::node value_string_element_string_2(
    const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE =
        "VALUE_STRING_ELEMENT_STRING := <HWS>* '\\'' ([^']* '\\'' '\\'')* '\\'' <HWS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        if (tokens.at(i).size() < 2)
        {
            throw dfm::pt::parse_error(RULE, tokens.at(i), i, dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING);
        }

        // TODO: Check if the string really contains only an even number of adjacent single qoutation marks
        if (!tokens.at(i).starts_with(dfm::lexer::token::SINGLE_QUOTATION_MARK))
        {
            throw dfm::pt::parse_error(
                "trigger: starts not with '", RULE, tokens.at(i), i, dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING);
        }
        if (!tokens.at(i).ends_with(dfm::lexer::token::SINGLE_QUOTATION_MARK))
        {
            throw dfm::pt::parse_error(
                "trigger: ends not with '", RULE, tokens.at(i), i, dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING);
        }

        n.children.push_back(dfm::pt::parse::any_chars(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
    }
    return n;
}

dfm::pt::node dfm::pt::parse::value_string_element_string(
    const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    std::vector< dfm::pt::node > results;
    std::vector< std::string > whats;
    std::vector< std::function< dfm::pt::node(const std::vector< dfm::lexer::token_type >, const size_t) > > fns;
    {
        fns.push_back(value_string_element_string_1);
        fns.push_back(value_string_element_string_2);
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
