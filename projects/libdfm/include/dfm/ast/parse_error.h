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
#include <dfm/pt/node.h>

namespace dfm::ast
{
    class parse_error : public std::exception
    {
        private:
        std::string __what;

        public:
        parse_error() = default;
        parse_error(const dfm::pt::node& n)
        {
            std::stringstream strstr;
            {
                n.pp(0, strstr);
            }
            __what = strstr.str();
        }

        parse_error(const dfm::pt::node& n, const std::string& comment)
        {
            std::stringstream strstr;
            {
                strstr << " " << comment;
                strstr << "\n";
                n.pp(0, strstr);
            }
            __what = strstr.str();
        }

        parse_error(const dfm::pt::node& n, const std::string& comment, const size_t line)
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
        virtual ~parse_error() override = default;
        virtual const char* what() const noexcept override
        {
            return __what.c_str();
        }
    };

}
