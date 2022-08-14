/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <algorithm>
#include <array>
#include <locale>
#include <string>
#include <vector>

// Own
#include <dfm/utils/ci_string.h>
#include <dfm/utils/form/identifier.h>

bool dfm::utils::form::identifier::is_valid(const dfm::utils::ci_string& str)
{
    using namespace std::string_literals;
    constexpr auto illegal_printable_chars = std::to_array({
        ' ',
        '\t',
        '\v',
        '\r',
        '\n',
        '!',
        '"',
        '#',
        '$',
        '%',
        '&',
        '\'',
        '(',
        ')',
        '*',
        '+',
        ',',
        '-',
        '/',
        ':',
        ';',
        '<',
        '=',
        '>',
        '?',
        '@',
        '[',
        '\\',
        ']',
        '^',
        '`',
        '{',
        '|',
        '}',
        '~',
    });
    constexpr auto illegal_substrs = std::to_array({
        "..",
    });

    if (str.empty())
    {
        return false;
    }

    if (str[ 0 ] >= '0' && str[ 0 ] <= '9')
    {
        // Identifiert is invalid as it starts with a number
        return false;
    }

    if (str[ 0 ] == '.')
    {
        // Identifiert is invalid as it starts with a dot
        return false;
    }

    for (const auto& illegal_substr : illegal_substrs)
    {
        if (str.find(illegal_substr) != str.npos)
        {
            // Contain illegal substring
            return false;
        }
    }

    for (const auto& c : str)
    {
        if (c < 0)
        {
            // MSB is 1, hence the value is > 0x8f and a non-ascii character
            // and most likely valid or at least illegal
            continue;
        }
        if (std::isprint(c, std::locale()) == 0)
        {
            // Non printable character found
            return false;
        }
        for (const auto& illegal_printable_char : illegal_printable_chars)
        {
            if (c == illegal_printable_char)
            {
                return false;
            }
        }
    }

    return true;
}

bool dfm::utils::form::identifier::is_keyword(const dfm::utils::ci_string& str)
{
    const std::vector< dfm::utils::ci_string > keywords = {
        "And",
        "Array",
        "As",
        "Begin",
        "Bool",
        "Case",
        "Class",
        "Const",
        "Constructor",
        "Destructor",
        "Div",
        "Do",
        "DownTo",
        "Else",
        "End",
        "Except",
        "False",
        "File",
        "Finally",
        "For",
        "Function",
        "Goto",
        "If",
        "Implementation",
        "In",
        "Inherited",
        "Integer",
        "Interface",
        "Is",
        "Mod",
        "Not",
        "Object",
        "Of",
        "On",
        "Or",
        "Packed",
        "Procedure",
        "Program",
        "Property",
        "Raise",
        "Record",
        "Repeat",
        "Set",
        "Shl",
        "Shr",
        "String",
        "Then",
        "ThreadVar",
        "To",
        "True",
        "Try",
        "Type",
        "Unit",
        "Until",
        "Uses",
        "Var",
        "While",
        "With",
        "Xor",
    };
    return std::find(keywords.begin(), keywords.end(), str) != keywords.end();
}
