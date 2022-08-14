/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <string>
#include <variant>
#include <vector>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_value.h>

namespace dfm::ast
{
    class node_value_set : public dfm::ast::node_value
    {
        public:
        std::vector< std::shared_ptr< dfm::ast::node_value > > values;

        public:
        virtual std::string dfm(const size_t lvl, const size_t pad = 4) const noexcept override;
        virtual std::string pp(const size_t lvl, const size_t pad = 4) const noexcept override;
    };
}
