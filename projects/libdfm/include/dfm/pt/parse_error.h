/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <exception>
#include <sstream>
#include <stdexcept>
#include <string>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/rule.h>

namespace dfm::pt
{
    class parse_error : public std::exception
    {
        private:
        std::string __what;

        public:
        parse_error() = default;
        parse_error(const std::string& what);
        parse_error(const std::vector< std::string >& whats);
        parse_error(const dfm::pt::rule_type& rule, const dfm::lexer::token_type& got, const size_t at);
        parse_error(const dfm::pt::rule_type& rule,
            const dfm::lexer::token_type& got,
            const size_t at,
            const std::runtime_error& ex);
        parse_error(const std::string& source,
            const dfm::pt::rule_type& rule,
            const dfm::lexer::token_type& got,
            const size_t at);
        parse_error(const std::string& source,
            const dfm::pt::rule_type& rule,
            const dfm::lexer::token_type& got,
            const size_t at,
            const dfm::lexer::token_type& expected);
        parse_error(const dfm::pt::rule_type& rule,
            const dfm::lexer::token_type& got,
            const size_t at,
            const dfm::lexer::token_type& expected);
        parse_error(const std::string& source,
            const dfm::pt::rule_type& rule,
            const dfm::lexer::token_type& got,
            const size_t at,
            const dfm::pt::node_type& expected_node);
        parse_error(const dfm::pt::rule_type& rule,
            const dfm::lexer::token_type& got,
            const size_t at,
            const dfm::pt::node_type& expected_node);
        virtual ~parse_error() override = default;

        virtual const char* what() const noexcept override;
    };
}

template < typename __FuncType, typename __TokenType, typename __PosType, typename __RuleType >
void __TOKEN_RANGE_CHECK(
    const __FuncType& __FUNC, const __TokenType& __TOKENS, const __PosType& __POS, const __RuleType& __RULE)
{
    if (__POS < __TOKENS.size())
    {
        return;
    }

    std::string what;
    what += "Out of Range in ";
    what += __FUNC;
    what += " with Position ";
    what += std::to_string(__POS);
    what += " RULE: ";
    what += __RULE;

    throw dfm::pt::parse_error(what);
}
