/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <string>
#include <vector>

// Own
#include <dfm/ast/parse/helper.h>
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>

dfm::lexer::token_type dfm::ast::parse::glue_delphi_name(const dfm::pt::node& n)
{
    assert(n.type == dfm::pt::ntypes::DELPHI_NAME);

    dfm::lexer::token_type token;
    {
        for (const auto& name_part : n.children)
        {
            if (name_part.type == dfm::pt::ntypes::DELPHI_IDENTIFIER)
            {
                token += name_part.token;
            }
            else if (name_part.type == dfm::pt::ntypes::TOKEN)
            {
                token += name_part.token;
            }
        }
    }
    return token;
}

std::vector< std::string > dfm::ast::parse::extract_string_elements(const dfm::pt::node& n)
{
    std::vector< std::string > parts;

    if (n.type == dfm::pt::ntypes::VALUE_STRING || n.type == dfm::pt::ntypes::VALUE_STRING_ELEMENT ||
        n.type == dfm::pt::ntypes::VALUE_STRING_ELEMENT_STRING)
    {
        for (const auto& child : n.children)
        {
            const auto child_parts = extract_string_elements(child);
            for (const auto& p : child_parts)
            {
                parts.push_back(p);
            }
        }
    }
    else if (n.type == dfm::pt::ntypes::TOKEN)
    {
        parts.push_back(n.token.c_str());
    }
    else if (n.type == dfm::pt::ntypes::ANY_CHARS)
    {
        parts.push_back(n.token.c_str());
    }
    else if (n.type == dfm::pt::ntypes::VALUE_STRING_ELEMENT_CHAR)
    {
        parts.push_back(n.token.c_str());
    }

    return parts;
}
