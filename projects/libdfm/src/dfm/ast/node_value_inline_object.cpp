/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

// Own
#include <dfm/ast/node_value_inline_object.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_inline_object::dfm(const size_t lvl, const size_t pad) const noexcept
{
    const auto padding = std::string(lvl * pad, ' ');

    std::stringstream strstr;
    {
        strstr << dfm::lexer::token::ROUND_BRACKET_LEFT;
        for (size_t i = 0; i < this->values.size(); ++i)
        {
            strstr << "\n";
            strstr << padding;
            const auto& value = this->values[ i ];
            strstr << value->dfm(lvl);
        }
        strstr << dfm::lexer::token::ROUND_BRACKET_RIGHT;
    }
    return strstr.str();
}

std::string dfm::ast::node_value_inline_object::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
