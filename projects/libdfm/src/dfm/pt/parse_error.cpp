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
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/parse_error.h>
#include <dfm/pt/rule.h>

dfm::pt::parse_error::parse_error(const std::string& what)
{
    __what = what;
}

dfm::pt::parse_error::parse_error(const std::vector< std::string >& whats)
{
    for (const auto& what_ : whats)
    {
        __what += what_ + "\n";
    }
}

dfm::pt::parse_error::parse_error(const dfm::pt::rule_type& rule, const dfm::lexer::token_type& got, const size_t at)
{
    std::stringstream strstr;
    {
        strstr << "In '";
        strstr << rule;
        strstr << "' got the token '";
        strstr << got;
        strstr << "' at position '";
        strstr << at;
        strstr << "'";
    }
    __what = strstr.str();
}

dfm::pt::parse_error::parse_error(
    const dfm::pt::rule_type& rule, const dfm::lexer::token_type& got, const size_t at, const std::runtime_error& ex)
{
    std::stringstream strstr;
    {
        strstr << "In '";
        strstr << rule;
        strstr << "' got the token '";
        strstr << got;
        strstr << "' at position '";
        strstr << at;
        strstr << "' and the exception ";
        strstr << ex.what();
    }
    __what = strstr.str();
}

dfm::pt::parse_error::parse_error(
    const std::string& source, const dfm::pt::rule_type& rule, const dfm::lexer::token_type& got, const size_t at)
{
    std::stringstream strstr;
    {
        strstr << "In '";
        strstr << rule;
        strstr << "' got the token '";
        strstr << got;
        strstr << "' at position '";
        strstr << at;
        strstr << "' source: ";
        strstr << source;
    }
    __what = strstr.str();
}

dfm::pt::parse_error::parse_error(const std::string& source,
    const dfm::pt::rule_type& rule,
    const dfm::lexer::token_type& got,
    const size_t at,
    const dfm::lexer::token_type& expected)
{
    std::stringstream strstr;
    {
        strstr << "In '";
        strstr << rule;
        strstr << "' got the token '";
        strstr << got;
        strstr << "' at position '";
        strstr << at;
        strstr << "' but expected token '";
        strstr << expected;
        strstr << "' source: ";
        strstr << source;
    }
    __what = strstr.str();
}

dfm::pt::parse_error::parse_error(const dfm::pt::rule_type& rule,
    const dfm::lexer::token_type& got,
    const size_t at,
    const dfm::lexer::token_type& expected)
{
    std::stringstream strstr;
    {
        strstr << "In '";
        strstr << rule;
        strstr << "' got the token '";
        strstr << got;
        strstr << "' at position '";
        strstr << at;
        strstr << "' but expected token '";
        strstr << expected;
        strstr << "'";
    }
    __what = strstr.str();
}

dfm::pt::parse_error::parse_error(const std::string& source,
    const dfm::pt::rule_type& rule,
    const dfm::lexer::token_type& got,
    const size_t at,
    const dfm::pt::node_type& expected_node)
{
    std::stringstream strstr;
    {
        strstr << "In '";
        strstr << rule;
        strstr << "' got the token '";
        strstr << got;
        strstr << "' at position '";
        strstr << at;
        strstr << "' but expected node '";
        strstr << expected_node;
        strstr << "' source: ";
        strstr << source;
    }
    __what = strstr.str();
}

dfm::pt::parse_error::parse_error(const dfm::pt::rule_type& rule,
    const dfm::lexer::token_type& got,
    const size_t at,
    const dfm::pt::node_type& expected_node)
{
    std::stringstream strstr;
    {
        strstr << "In '";
        strstr << rule;
        strstr << "' got the token '";
        strstr << got;
        strstr << "' at position '";
        strstr << at;
        strstr << "' but expected node '";
        strstr << expected_node;
        strstr << "'";
    }
    __what = strstr.str();
}

const char* dfm::pt::parse_error::what() const noexcept
{
    return __what.c_str();
}
