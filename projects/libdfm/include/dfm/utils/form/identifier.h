/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <string>

// Own
#include <dfm/lexer/token.h>

namespace dfm::utils::form::identifier
{
    bool is_valid(const dfm::lexer::token_type& str);
    bool is_keyword(const dfm::lexer::token_type& str);
}
