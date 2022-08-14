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
#include <dfm/ast/node_value_string.h>
#include <dfm/lexer/token.h>
#include <dfm/utils/escape.h>

std::string dfm::ast::node_value_string::dfm(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    {
        for (size_t i = 0; i < parts.size(); ++i)
        {
            if (i > 0)
            {
                strstr << ' ';
            }
            strstr << parts[ i ];
        }
    }
    return strstr.str();
}

std::string dfm::ast::node_value_string::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
