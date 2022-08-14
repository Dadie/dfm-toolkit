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
#include <dfm/ast/node_value_bit.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_bit::dfm(const size_t lvl, const size_t pad) const noexcept
{
    return this->value ? dfm::lexer::token::TRUE_.c_str() : dfm::lexer::token::FALSE_.c_str();
}

std::string dfm::ast::node_value_bit::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
