/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <iomanip>
#include <ios>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Own
#include <dfm/ast/node_value_float.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_float::dfm(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    {
        if (sign)
        {
            strstr << std::showpos;
        }
        strstr << std::setprecision(static_cast< int >(precision));
        strstr << std::showpoint << value;
    }
    return strstr.str();
}

std::string dfm::ast::node_value_float::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
