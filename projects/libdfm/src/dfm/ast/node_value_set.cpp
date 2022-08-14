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
#include <dfm/ast/node_value_set.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_set::dfm(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    {
        strstr << dfm::lexer::token::SQUARE_BRACKET_LEFT;
        for (size_t i = 0; i < this->values.size(); ++i)
        {
            const auto& value = this->values[ i ];
            if (i > 0)
            {
                strstr << dfm::lexer::token::COMMA;
                strstr << dfm::lexer::token::SPACE;
            }

            strstr << value->dfm(lvl);
        }
        strstr << dfm::lexer::token::SQUARE_BRACKET_RIGHT;
    }
    return strstr.str();
}

std::string dfm::ast::node_value_set::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
