/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Own
#include <dfm/ast/node_value_array.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_array::dfm(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    {
        strstr << dfm::lexer::token::ANGLE_BRACKET_LEFT;
        for (const auto& item : this->items)
        {
            strstr << item.dfm(lvl + 1, pad);
        }
        strstr << dfm::lexer::token::ANGLE_BRACKET_RIGHT;
    }
    return strstr.str();
}

std::string dfm::ast::node_value_array::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
