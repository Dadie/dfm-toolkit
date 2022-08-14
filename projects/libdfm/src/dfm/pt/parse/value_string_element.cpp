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

static dfm::pt::node value_string_element_1(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE_STRING_ELEMENT := <EPSILON>";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_STRING_ELEMENT;
        n.rule = RULE;
    }
    return n;
}

static dfm::pt::node value_string_element_2(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE_STRING_ELEMENT := <HWS>* <VALUE_STRING_ELEMENT_STRING> <HWS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_STRING_ELEMENT;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::value_string_element_string(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
    }
    return n;
}

static dfm::pt::node value_string_element_3(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE_STRING_ELEMENT := <HWS>* <VALUE_STRING_ELEMENT_STRING> <HWS>* "
                                           "(<VALUE_STRING_ELEMENT_CHAR> <HWS>* <VALUE_STRING_ELEMENT> <HWS>*)?";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_STRING_ELEMENT;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::value_string_element_string(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        if (tokens.at(i).starts_with("#"))
        {
            n.children.push_back(dfm::pt::parse::value_string_element_char(tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

            n.children.push_back(dfm::pt::parse::value_string_element(tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
        }
    }
    return n;
}

static dfm::pt::node value_string_element_4(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE =
        "VALUE_STRING_ELEMENT := <HWS>* (<VALUE_STRING_ELEMENT_CHAR> <HWS>*)+ (<VALUE_STRING_ELEMENT> <HWS>*)?";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_STRING_ELEMENT;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::value_string_element_char(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        while (tokens.at(i).starts_with("#"))
        {
            n.children.push_back(dfm::pt::parse::value_string_element_char(tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
        }

        try
        {
            n.children.push_back(dfm::pt::parse::value_string_element(tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
        }
        catch (const std::exception&)
        {
            // probably no <VALUE_STRING_ELEMENT<
        }
    }
    return n;
}

static dfm::pt::node value_string_element_5(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE =
        "VALUE_STRING_ELEMENT := <HWS>* <VALUE_STRING_ELEMENT_STRING> <WS>* '+' <WS>* <VALUE_STRING_ELEMENT> <HWS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_STRING_ELEMENT;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::value_string_element_string(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
        {
            const auto [ t, p ] = dfm::pt::parse::next_non_whitespace_token(tokens, i);
            if (t == dfm::lexer::token::PLUS)
            {
                i += dfm::pt::parse::consume_whitespace(n, tokens, i);
            }
        }

        n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::PLUS, tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::value_string_element(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
    }
    return n;
}

static dfm::pt::node value_string_element_6(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "VALUE_STRING_ELEMENT := <HWS>* (<VALUE_STRING_ELEMENT_CHAR> <HWS>*)+ <WS>* "
                                           "'+' <WS>* <VALUE_STRING_ELEMENT> <HWS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::VALUE_STRING_ELEMENT;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::value_string_element_char(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);

        while (tokens.at(i).starts_with("#"))
        {
            n.children.push_back(dfm::pt::parse::value_string_element_char(tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
        }

        {
            const auto [ t, p ] = dfm::pt::parse::next_non_whitespace_token(tokens, i);
            if (t == dfm::lexer::token::PLUS)
            {
                i += dfm::pt::parse::consume_whitespace(n, tokens, i);
            }
        }

        n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::PLUS, tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::value_string_element(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_hwhitespace(n, tokens, i);
    }
    return n;
}

dfm::pt::node dfm::pt::parse::value_string_element(
    const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    std::vector< dfm::pt::node > results;
    std::vector< std::string > whats;
    std::vector< std::function< dfm::pt::node(const std::vector< dfm::lexer::token_type >, const size_t) > > fns;
    {
        fns.push_back(value_string_element_1);
        fns.push_back(value_string_element_2);
        fns.push_back(value_string_element_3);
        fns.push_back(value_string_element_4);
        fns.push_back(value_string_element_5);
        fns.push_back(value_string_element_6);
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
