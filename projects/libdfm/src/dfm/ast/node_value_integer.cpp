/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <iomanip>
#include <ios>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Own
#include <dfm/ast/node_value_integer.h>
#include <dfm/lexer/token.h>

std::string dfm::ast::node_value_integer::dfm(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    {
        switch (base)
        {
            case 16:
            {
                strstr << "$" << std::hex << value;
            }
            break;
            case 10:
            {
                if (sign)
                {
                    strstr << std::showpos;
                }
                strstr << std::dec << value;
            }
            break;
            default:
            {
                assert(false);
            }
        }
    }
    return strstr.str();
}

std::string dfm::ast::node_value_integer::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
