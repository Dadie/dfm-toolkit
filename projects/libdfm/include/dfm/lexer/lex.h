/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <istream>
#include <vector>

// Own
#include <dfm/lexer/token.h>

namespace dfm::lexer
{
    std::vector< dfm::lexer::token_type > lex(std::istream&);
}
