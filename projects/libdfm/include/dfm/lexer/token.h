/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <string_view>

// Own
#include <dfm/utils/ci_string.h>

namespace dfm::lexer
{
    using token_type = dfm::utils::ci_string;
    using token_view_type = dfm::utils::ci_string_view;

    namespace token
    {
        const token_type OBJECT = "object";
        const token_type INHERITED = "inherited";
        const token_type INLINE = "inline";
        const token_type COLON = ":";
        const token_type END = "end";
        const token_type TRUE_ = "True";
        const token_type FALSE_ = "False";
        const token_type ITEM = "item";
        const token_type EQUAL = "=";
        const token_type COMMA = ",";
        const token_type DOT = ".";
        const token_type AT = "@";
        const token_type CARET = "^";
        const token_type HASH = "#";
        const token_type PLUS = "+";
        const token_type MINUS = "+";
        const token_type SPACE = " ";
        const token_type NB_SPACE = "\xA0";
        const token_type TABULATOR = "\t";
        const token_type VERTICAL_TABULATOR = "\v";
        const token_type HEX = "$";
        const token_type SLASH = "/";
        const token_type CURLY_BRACKET_LEFT = "{";
        const token_type CURLY_BRACKET_RIGHT = "}";
        const token_type ROUND_BRACKET_LEFT = "(";
        const token_type ROUND_BRACKET_RIGHT = ")";
        const token_type SQUARE_BRACKET_LEFT = "[";
        const token_type SQUARE_BRACKET_RIGHT = "]";
        const token_type ANGLE_BRACKET_LEFT = "<";
        const token_type ANGLE_BRACKET_RIGHT = ">";
        const token_type SINGLE_QUOTATION_MARK = "'";
        const token_type DOUBLE_QUOTATION_MARK = "\"";
        const token_type NEWLINE = "\\n";
        const token_type LF_ = "\n";
        const token_type CR_ = "\r";
        const token_type CRLF_ = "\r\n";
        const token_type FORM_FEED = "\f";
        const token_type NEL_ = "\x85";

    }
}
