/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <memory>
#include <string>
#include <vector>

// Own

namespace dfm::ast
{
    class node
    {
        public:
        virtual ~node() = default;

        virtual std::string dfm(const size_t lvl, const size_t pad = 4) const noexcept = 0;
        virtual std::string pp(const size_t lvl, const size_t pad = 4) const noexcept = 0;
    };

}
