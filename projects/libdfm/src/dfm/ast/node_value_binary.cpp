/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Own
#include <dfm/ast/node_value_binary.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_binary::dfm(const size_t lvl, const size_t pad) const noexcept
{
    const auto padding = std::string((lvl + 1) * pad, ' ');

    std::stringstream strstr;
    {
        strstr << dfm::lexer::token::CURLY_BRACKET_LEFT;
        if (!this->value.empty())
        {
            const auto def_flags = strstr.flags();
            for (size_t i = 0; i < this->value.size(); ++i)
            {
                strstr.flags(def_flags);
                if ((i % 32) == 0)
                {
                    strstr << "\n";
                    strstr << padding;
                }
                const auto& b = this->value[ i ];
                strstr << std::uppercase << std::left << std::setw(2) << std::setfill('0') << std::hex;
                strstr << +b;
            }
        }
        strstr << dfm::lexer::token::CURLY_BRACKET_RIGHT;
    }
    return strstr.str();
}

std::string dfm::ast::node_value_binary::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
