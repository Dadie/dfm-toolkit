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
#include <dfm/ast/node_value_constant.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_constant::dfm(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    {
        strstr << value;
    }
    return strstr.str();
}

std::string dfm::ast::node_value_constant::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
