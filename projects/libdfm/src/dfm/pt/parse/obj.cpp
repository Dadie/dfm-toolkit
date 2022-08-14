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

static dfm::pt::node obj_1(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE =
        "OBJ := <WS>* ('object'|'inherited'|'inline') <WS>* (<OBJ_NAME> <WS>*  ':')? <WS>*  <OBJ_TYPE> <WS>*  ('[' "
        "<WS>*  <VALUE_INTEGER> <WS>*  ']' <WS>* )? <OBJ_PARAMS> <WS>* 'end' <WS>*";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::OBJ;
        n.rule = RULE;

        auto i = pos;
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        if (tokens.at(i) == dfm::lexer::token::INHERITED)
        {
            n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::INHERITED, tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);
        }
        else if (tokens.at(i) == dfm::lexer::token::INLINE)
        {
            n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::INLINE, tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);
        }
        else if (tokens.at(i) == dfm::lexer::token::OBJECT)
        {
            n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::OBJECT, tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);
        }
        else
        {
            throw dfm::pt::parse_error(RULE, tokens.at(i), i);
        }

        const auto delphi_name = dfm::pt::parse::delphi_name(tokens, i);
        if (std::get< dfm::lexer::token_type >(dfm::pt::parse::next_non_whitespace_token(
                tokens, i + delphi_name.offset())) == dfm::lexer::token::COLON)
        {
            n.children.push_back(dfm::pt::parse::obj_name(tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);

            n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::COLON, tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);
        }

        n.children.push_back(dfm::pt::parse::obj_type(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        if (tokens.at(i) == dfm::lexer::token::SQUARE_BRACKET_LEFT)
        {
            // Note: Dadie@2022-08-24: I have no idea what this syntax means but I found it in some files online, so I
            // assume some version of rad studio is generating them for some reason.
            n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::SQUARE_BRACKET_LEFT, tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);

            n.children.push_back(dfm::pt::parse::value_integer(tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);

            n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::SQUARE_BRACKET_RIGHT, tokens, i));
            i += n.children.back().offset();
            i += dfm::pt::parse::consume_whitespace(n, tokens, i);
        }

        n.children.push_back(dfm::pt::parse::obj_params(tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);

        n.children.push_back(dfm::pt::parse::token(RULE, dfm::lexer::token::END, tokens, i));
        i += n.children.back().offset();
        i += dfm::pt::parse::consume_whitespace(n, tokens, i);
    }
    return n;
}

dfm::pt::node dfm::pt::parse::obj(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    std::vector< dfm::pt::node > results;
    std::vector< std::string > whats;
    std::vector< std::function< dfm::pt::node(const std::vector< dfm::lexer::token_type >, const size_t) > > fns;
    {
        fns.push_back(obj_1);
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
