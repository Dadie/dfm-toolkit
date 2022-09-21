/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <exception>
#include <sstream>
#include <stdexcept>
#include <string>

// Own
#include <dfm/ast/parse_error.h>
#include <dfm/pt/node.h>

dfm::ast::parse_error::parse_error(const dfm::pt::node& n)
{
    std::stringstream strstr;
    {
        n.pp(0, strstr);
    }
    __what = strstr.str();
}

dfm::ast::parse_error::parse_error(const dfm::pt::node& n, const std::string& comment)
{
    std::stringstream strstr;
    {
        strstr << " " << comment;
        strstr << "\n";
        n.pp(0, strstr);
    }
    __what = strstr.str();
}

dfm::ast::parse_error::parse_error(const dfm::pt::node& n, const std::string& comment, const size_t line)
{
    std::stringstream strstr;
    {
        strstr << " " << comment;
        strstr << " LINE:" << line;
        strstr << "\n";
        n.pp(0, strstr);
    }
    __what = strstr.str();
}

const char* dfm::ast::parse_error::what() const noexcept
{
    return __what.c_str();
}
