/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <string>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_object.h>

namespace dfm::ast
{

    class node_dfm : public dfm::ast::node
    {
        public:
        dfm::ast::node_object obj;

        virtual std::string dfm(const size_t lvl, const size_t pad = 4) const noexcept override;
        virtual std::string pp(const size_t lvl, const size_t pad = 4) const noexcept override;
    };
}
