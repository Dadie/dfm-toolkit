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
#include <dfm/ast/node_parameter.h>
#include <dfm/ast/node_value_array.h>
#include <dfm/ast/node_value_binary.h>
#include <dfm/ast/node_value_constant.h>
#include <dfm/ast/node_value_float.h>
#include <dfm/ast/node_value_integer.h>
#include <dfm/ast/node_value_set.h>
#include <dfm/ast/node_value_string.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_parameter::dfm(const size_t lvl, const size_t pad) const noexcept
{
    const auto padding = std::string(lvl * pad, ' ');

    std::stringstream strstr;
    strstr << padding;
    strstr << this->param_name;
    strstr << dfm::lexer::token::SPACE;
    strstr << dfm::lexer::token::EQUAL;
    strstr << dfm::lexer::token::SPACE;

    strstr << this->param_value->dfm(lvl + 1, pad);
    strstr << "\n";
    return strstr.str();
}

std::string dfm::ast::node_parameter::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
