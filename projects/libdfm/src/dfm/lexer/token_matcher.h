/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <memory>
#include <string>
#include <string_view>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/utils/simple_nfa.h>

namespace dfm::lexer
{
    class token_matcher
    {
        public:
        virtual ~token_matcher() = default;
        virtual bool accept(const dfm::lexer::token_view_type& sv) const = 0;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const = 0;
    };

    class token_matcher_token : public token_matcher
    {
        private:
        dfm::lexer::token_type m_token;

        public:
        token_matcher_token() = default;
        token_matcher_token(const token_matcher_token&) = default;
        token_matcher_token(token_matcher_token&&) = default;
        token_matcher_token(const dfm::lexer::token_type& t)
            : m_token { t }
        {
        }
        virtual ~token_matcher_token() = default;
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_comment : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_integer_datetime : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_float_datetime : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_float : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_integer : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_hex : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_non_special : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_string : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_string_char : public token_matcher
    {
        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
    };

    class token_matcher_composition : public token_matcher
    {
        private:
        std::vector< std::shared_ptr< token_matcher > > m_automata;

        public:
        virtual bool accept(const dfm::lexer::token_view_type& sv) const;
        virtual bool ok(const dfm::lexer::token_view_type& sv) const;
        template < typename Automaton, typename... Args >
        void add(Args... args)
        {
            m_automata.push_back(std::make_shared< Automaton >(args...));
        }
    };

}
