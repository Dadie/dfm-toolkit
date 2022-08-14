/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cstddef>
#include <cstdint>
#include <exception>
#include <tuple>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/parse.h>
#include <dfm/pt/parse/helper.h>

size_t dfm::pt::parse::consume_whitespace(
    dfm::pt::node& n, const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    auto i = pos;
    try
    {
        do
        {
            const auto child = dfm::pt::parse::ws(tokens, i);
            if (child.offset() == 0)
            {
                break;
            }
            n.children.push_back(child);
            i += n.children.back().offset();
        } while (i < tokens.size());
    }
    catch (const std::exception&)
    {
        // out of white space tokens
    }
    return i - pos;
}

size_t dfm::pt::parse::consume_hwhitespace(
    dfm::pt::node& n, const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    auto i = pos;
    try
    {
        do
        {
            const auto child = dfm::pt::parse::hws(tokens, i);
            if (child.offset() == 0)
            {
                break;
            }
            n.children.push_back(child);
            i += n.children.back().offset();
        } while (i < tokens.size());
    }
    catch (const std::exception&)
    {
        // out of white space tokens
    }
    return i - pos;
}

std::tuple< dfm::lexer::token_type, size_t > dfm::pt::parse::next_non_whitespace_token(
    const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    dfm::pt::node n;
    auto i = pos;
    i += dfm::pt::parse::consume_whitespace(n, tokens, pos);
    return { tokens.at(i), i };
}
