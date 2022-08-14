/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cstdlib>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_object.h>
#include <dfm/ast/parse.h>
#include <dfm/ast/parse/helper.h>
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>

dfm::ast::node_object dfm::ast::parse::obj(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::OBJ)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }
    dfm::ast::node_object obj_obj;
    {
        size_t obj_decl_idx = 0;
        size_t obj_name_idx = 1;
        size_t obj_type_idx = 3;
        size_t obj_idx_op_idx = 5;
        size_t obj_params_idx = 7;

        // Is Anonym Object
        if (n.children.at(obj_name_idx + 1).token != dfm::lexer::token::COLON)
        {
            obj_name_idx = 0;
            obj_type_idx -= 2;
            obj_idx_op_idx -= 2;
            obj_params_idx -= 2;
        }

        // Has NO Index Operator
        if (n.children.at(obj_idx_op_idx - 1).token != dfm::lexer::token::SQUARE_BRACKET_LEFT)
        {
            obj_idx_op_idx = 0;
            obj_params_idx -= 3;
        }

        // Object Declarion
        const auto& obj_decl_node = n.children.at(obj_decl_idx);
        if (obj_decl_node.token == dfm::lexer::token::INHERITED)
        {
            obj_obj.obj_decl = dfm::lexer::token::INHERITED;
        }
        else if (obj_decl_node.token == dfm::lexer::token::INLINE)
        {
            obj_obj.obj_decl = dfm::lexer::token::INLINE;
        }
        else if (obj_decl_node.token == dfm::lexer::token::OBJECT)
        {
            obj_obj.obj_decl = dfm::lexer::token::OBJECT;
        }
        else
        {
            throw dfm::ast::parse_error(obj_decl_node, "Unexpected Object Declartion (Expected OBJ or OBJ_PARAM_NAME)");
        }

        // Object Name
        if (obj_name_idx > 0)
        {
            const auto& obj_name_node = n.children.at(obj_name_idx);
            for (const auto& child : obj_name_node.children)
            {
                if (child.type != dfm::pt::ntypes::DELPHI_NAME)
                {
                    continue;
                }
                obj_obj.obj_name = dfm::ast::parse::glue_delphi_name(child);
                break;
            }
        }

        // Object Type
        {
            const auto& obj_type_node = n.children.at(obj_type_idx);
            for (const auto& child : obj_type_node.children)
            {
                if (child.type != dfm::pt::ntypes::DELPHI_NAME)
                {
                    continue;
                }
                obj_obj.obj_type = dfm::ast::parse::glue_delphi_name(child);
                break;
            }
        }

        // Objext Idx Operator
        if (obj_idx_op_idx > 0)
        {
            obj_obj.obj_idx_operator = ::atoll(n.children.at(obj_idx_op_idx).token.c_str());
        }

        // Object Params
        const auto& obj_params_node = n.children.at(obj_params_idx);
        for (const auto& obj_param_node : obj_params_node.children)
        {
            const auto& first_child = obj_param_node.children.at(0);
            if (first_child.type == dfm::pt::ntypes::OBJ)
            {
                obj_obj.objs.push_back(dfm::ast::parse::obj(first_child));
            }
            else if (first_child.type == dfm::pt::ntypes::OBJ_PARAM_NAME)
            {
                obj_obj.params.push_back(dfm::ast::parse::parameter(obj_param_node));
            }
            else
            {
                throw dfm::ast::parse_error(first_child, "Unexpected Node Type (Expected OBJ or OBJ_PARAM_NAME)");
            }
        }
    }
    return obj_obj;
}
