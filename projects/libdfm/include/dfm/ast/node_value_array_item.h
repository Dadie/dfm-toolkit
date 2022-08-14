/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <string>
#include <vector>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_parameter.h>

namespace dfm::ast
{
    class node_value_array_item : public dfm::ast::node
    {
        public:
        std::vector< dfm::ast::node_parameter > params;

        public:
        virtual std::string dfm(const size_t lvl, const size_t pad = 4) const noexcept override;
        virtual std::string pp(const size_t lvl, const size_t pad = 4) const noexcept override;
    };
}
