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

    struct weed_cfg
    {
        bool remove_empty_tokens = true;
        bool remove_horizontal_whitespace = true;
        bool normalize_newline = true;
        bool remove_adjacent_newline = true;
        bool remove_trailing_newline = true;
        bool remove_comments = true;
    };

    std::vector< dfm::lexer::token_type > weed(
        const std::vector< dfm::lexer::token_type >& tokens, const dfm::lexer::weed_cfg& cfg = {});
}
