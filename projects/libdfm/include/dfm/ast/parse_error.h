/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <exception>
#include <stdexcept>
#include <string>

// Own
#include <dfm/pt/node.h>

namespace dfm::ast
{
    class parse_error : public std::exception
    {
        private:
        std::string __what;

        public:
        parse_error() = default;
        parse_error(const dfm::pt::node& n);
        parse_error(const dfm::pt::node& n, const std::string& comment);
        parse_error(const dfm::pt::node& n, const std::string& comment, const size_t line);
        virtual ~parse_error() override = default;
        virtual const char* what() const noexcept override;
    };
}
