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
        parse_error(const std::string& what)
        {
            __what = what;
        }
        parse_error(const std::vector< std::string >& whats)
        {
            for (const auto& what_ : whats)
            {
                __what += what_ + "\n";
            }
        }
        parse_error(const dfm::pt::rule_type& rule, const dfm::lexer::token_type& got, const size_t at)
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
        parse_error(const dfm::pt::rule_type& rule,
            const dfm::lexer::token_type& got,
            const size_t at,
            const std::runtime_error& ex)
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
        parse_error(const std::string& source,
            const dfm::pt::rule_type& rule,
            const dfm::lexer::token_type& got,
            const size_t at)
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
        parse_error(const std::string& source,
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
        parse_error(const dfm::pt::rule_type& rule,
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
        parse_error(const std::string& source,
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
        parse_error(const dfm::pt::rule_type& rule,
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
        virtual ~parse_error() override = default;
        virtual const char* what() const noexcept override
        {
            return __what.c_str();
        }
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
