/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <memory>
#include <string>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_object.h>
#include <dfm/ast/node_value_array.h>
#include <dfm/ast/node_value_array_item.h>
#include <dfm/ast/node_value_binary.h>
#include <dfm/ast/node_value_bit.h>
#include <dfm/ast/node_value_constant.h>
#include <dfm/ast/node_value_float.h>
#include <dfm/ast/node_value_integer.h>
#include <dfm/ast/node_value_set.h>
#include <dfm/ast/node_value_string.h>
#include <dfm/ast/parse.h>
#include <dfm/ast/parse/helper.h>
#include <dfm/pt/node.h>

dfm::ast::node_parameter dfm::ast::parse::parameter(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::OBJ_PARAM && n.type != dfm::pt::ntypes::VALUE_ARRAY_ITEM_PARAM)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_parameter parameter_obj;
    {
        for (const auto& child : n.children)
        {
            if (child.type == dfm::pt::ntypes::OBJ_PARAM_NAME ||
                child.type == dfm::pt::ntypes::VALUE_ARRAY_ITEM_PARAM_NAME)
            {
                assert(parameter_obj.param_name.empty());
                for (const auto& inner : child.children)
                {
                    if (inner.type != dfm::pt::ntypes::DELPHI_NAME)
                    {
                        continue;
                    }
                    parameter_obj.param_name = dfm::ast::parse::glue_delphi_name(inner);
                    break;
                }
            }

            if (child.type == dfm::pt::ntypes::VALUE)
            {
                assert(!parameter_obj.param_value);
                parameter_obj.param_value = dfm::ast::parse::value(child);
            }
        }
    }
    return parameter_obj;
}
