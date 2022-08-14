/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <exception>
#include <iostream>
#include <string>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/rule.h>

namespace dfm::pt::parse
{
    dfm::pt::node dfm(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node obj(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node obj_name(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node obj_type(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node obj_params(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node obj_param(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node obj_param_name(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_integer(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_float(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_string(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_string_element(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_string_element_string(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_string_element_char(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_bit(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_binary(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_constant(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_set(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_array(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_inline_object(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_datetime(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node hex_code_string(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_set_values(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_set_value(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_array_items(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_array_item(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_array_item_param(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node value_array_item_param_name(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node any_chars(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node nl(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node hws(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node ws(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node delphi_identifier(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node delphi_name(const std::vector< dfm::lexer::token_type >&, const size_t);
    dfm::pt::node token(const dfm::pt::rule_type&,
        const dfm::lexer::token_type&,
        const std::vector< dfm::lexer::token_type >&,
        const size_t);
}
