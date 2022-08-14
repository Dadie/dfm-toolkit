/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// Own
#include <dfm/ast/node_dfm.h>
#include <dfm/utils/ci_string.h>
#include <dfm/utils/form/find.h>

namespace dfm::utils
{
    static std::vector< dfm::utils::form::find_match > __find_types(
        const dfm::ast::node_object& obj, const std::vector< dfm::utils::ci_string >& types, const std::string& path)
    {
        std::vector< dfm::utils::form::find_match > node_match_vec;
        {
            for (const auto& type_ : types)
            {
                const std::string obj_path = path + (path.empty() ? "" : "::") + obj.obj_name.c_str();
                if (type_ == obj.obj_type)
                {
                    node_match_vec.push_back({ obj_path, &(obj) });
                }
                for (const auto& obj_node : obj.objs)
                {
                    const auto obj_node_match_vec = dfm::utils::__find_types(obj_node, { type_ }, obj_path);
                    node_match_vec.insert(node_match_vec.end(), obj_node_match_vec.begin(), obj_node_match_vec.end());
                }
            }
        }
        return node_match_vec;
    }

    static std::vector< dfm::utils::form::find_match > __find_fields(
        const dfm::ast::node_object& obj, const std::vector< dfm::utils::ci_string >& names, const std::string& path)
    {
        std::vector< dfm::utils::form::find_match > node_match_vec;
        {
            for (const auto& name : names)
            {
                const std::string obj_path = path + (path.empty() ? "" : "::") + obj.obj_name.c_str();
                if (name == obj.obj_name)
                {
                    node_match_vec.push_back({ obj_path, &(obj) });
                }
                for (const auto& param_node : obj.params)
                {
                    if (name == param_node.param_name)
                    {
                        node_match_vec.push_back({ obj_path, &(param_node) });
                    }
                }
                for (const auto& obj_node : obj.objs)
                {
                    const auto obj_node_match_vec = dfm::utils::__find_fields(obj_node, { name }, obj_path);
                    node_match_vec.insert(node_match_vec.end(), obj_node_match_vec.begin(), obj_node_match_vec.end());
                }
            }
        }
        return node_match_vec;
    }
}

std::vector< dfm::utils::form::find_match > dfm::utils::form::find_types(
    const dfm::ast::node_dfm& dfm, const std::vector< dfm::utils::ci_string >& types)
{
    return dfm::utils::__find_types(dfm.obj, types, "");
}

std::vector< dfm::utils::form::find_match > dfm::utils::form::find_fields(
    const dfm::ast::node_dfm& dfm, const std::vector< dfm::utils::ci_string >& names)
{
    return dfm::utils::__find_fields(dfm.obj, names, "");
}
