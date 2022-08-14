/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/parse.h>

namespace dfm::pt::parse
{
    size_t consume_whitespace(dfm::pt::node& n, const std::vector< dfm::lexer::token_type >& tokens, const size_t pos);
    size_t consume_hwhitespace(dfm::pt::node& n, const std::vector< dfm::lexer::token_type >& tokens, const size_t pos);
    std::tuple< dfm::lexer::token_type, size_t > next_non_whitespace_token(
        const std::vector< dfm::lexer::token_type >& tokens, const size_t pos);
}
