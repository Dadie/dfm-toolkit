/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_value.h>

namespace dfm::ast
{
    class node_value_binary : public dfm::ast::node_value
    {
        public:
        std::vector< uint8_t > value;

        public:
        virtual std::string dfm(const size_t lvl, const size_t pad = 4) const noexcept override;
        virtual std::string pp(const size_t lvl, const size_t pad = 4) const noexcept override;
    };
}
