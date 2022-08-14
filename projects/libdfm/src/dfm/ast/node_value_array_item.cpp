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
#include <dfm/ast/node_value_array_item.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_array_item::dfm(const size_t lvl, const size_t pad) const noexcept
{
    const auto padding = std::string(lvl * pad, ' ');

    std::stringstream strstr;
    {
        strstr << "\n";
        strstr << padding;
        strstr << dfm::lexer::token::ITEM;
        strstr << "\n";
        for (const auto& param : this->params)
        {
            strstr << param.dfm(lvl + 1, pad);
        }
        strstr << padding;
        strstr << dfm::lexer::token::END;
    }
    return strstr.str();
}

std::string dfm::ast::node_value_array_item::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
