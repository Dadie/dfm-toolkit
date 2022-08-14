/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <string>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>

namespace dfm::ast::parse
{
    dfm::lexer::token_type glue_delphi_name(const dfm::pt::node& n);
    std::vector< std::string > extract_string_elements(const dfm::pt::node& n);
}
