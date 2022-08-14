/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cstddef>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_parameter.h>
#include <dfm/lexer/token.h>

namespace dfm::ast
{

    class node_object;
    class node_object_parameter_helper
    {
        private:
        node_object& __obj;

        public:
        node_object_parameter_helper(node_object& obj)
            : __obj { obj }
        {
        }
        const dfm::ast::node_parameter& operator[](const size_t idx) const;
        const dfm::ast::node_parameter& operator[](const dfm::lexer::token_type& name) const;
        bool has(const size_t idx) const;
        bool has(const dfm::lexer::token_type& name) const;
    };
    class node_object_obj_helper
    {
        private:
        node_object& __obj;

        public:
        node_object_obj_helper(node_object& obj)
            : __obj { obj }
        {
        }
        const dfm::ast::node_object& operator[](const size_t idx) const;
        const dfm::ast::node_object& operator[](const dfm::lexer::token_type& name) const;
        bool has(const size_t idx) const;
        bool has(const dfm::lexer::token_type& name) const;
    };

    class node_object : public dfm::ast::node
    {
        public:
        dfm::lexer::token_type obj_decl;
        dfm::lexer::token_type obj_name;
        dfm::lexer::token_type obj_type;
        std::optional< int64_t > obj_idx_operator;

        std::vector< dfm::ast::node_parameter > params;
        std::vector< dfm::ast::node_object > objs;

        dfm::ast::node_object_parameter_helper p;
        dfm::ast::node_object_obj_helper o;

        public:
        node_object()
            : p { *this }
            , o { *this }
        {
        }
        node_object(const node_object& obj)
            : p { *this }
            , o { *this }
        {
            obj_decl = obj.obj_decl;
            obj_name = obj.obj_name;
            obj_type = obj.obj_type;
            obj_idx_operator = obj.obj_idx_operator;
            params = obj.params;
            objs = obj.objs;
        }
        node_object(node_object&& obj)
            : p { *this }
            , o { *this }
        {
            obj_decl = std::move(obj.obj_decl);
            obj_name = std::move(obj.obj_name);
            obj_type = std::move(obj.obj_type);
            params = std::move(obj.params);
            obj_idx_operator = std::move(obj.obj_idx_operator);
            objs = std::move(obj.objs);
        }
        node_object& operator=(const node_object& obj)
        {
            obj_decl = obj.obj_decl;
            obj_name = obj.obj_name;
            obj_type = obj.obj_type;
            params = obj.params;
            objs = obj.objs;
            return *this;
        }
        virtual std::string dfm(const size_t lvl, const size_t pad = 4) const noexcept override;
        virtual std::string pp(const size_t lvl, const size_t pad = 4) const noexcept override;
    };

}
