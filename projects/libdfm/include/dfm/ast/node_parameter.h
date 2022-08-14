/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <memory>
#include <string>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_value.h>
#include <dfm/lexer/token.h>

namespace dfm::ast
{
    class node_parameter : public dfm::ast::node
    {
        public:
        dfm::lexer::token_type param_name;
        std::shared_ptr< dfm::ast::node_value > param_value;

        public:
        virtual std::string dfm(const size_t lvl, const size_t pad = 4) const noexcept override;
        virtual std::string pp(const size_t lvl, const size_t pad = 4) const noexcept override;
    };
}
