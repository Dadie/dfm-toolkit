/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <string>
#include <tuple>
#include <vector>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_dfm.h>
#include <dfm/ast/node_object.h>
#include <dfm/utils/ci_string.h>

namespace dfm::utils::form
{
    using find_match = std::tuple< std::string, const dfm::ast::node* >;
    std::vector< dfm::utils::form::find_match > find_types(
        const dfm::ast::node_dfm& dfm, const std::vector< dfm::utils::ci_string >& names);
    std::vector< dfm::utils::form::find_match > find_fields(
        const dfm::ast::node_dfm& dfm, const std::vector< dfm::utils::ci_string >& names);

    template < typename... T >
    std::vector< dfm::utils::form::find_match > find_type(const dfm::ast::node_dfm& dfm, T... types);
    template < typename... T >
    std::vector< dfm::utils::form::find_match > find_field(const dfm::ast::node_dfm& dfm, T... names);

}

template < typename... T >
std::vector< dfm::utils::form::find_match > dfm::utils::form::find_type(const dfm::ast::node_dfm& dfm, T... types)
{
    return find_types(dfm, { types... });
}

template < typename... T >
std::vector< dfm::utils::form::find_match > dfm::utils::form::find_field(const dfm::ast::node_dfm& dfm, T... names)
{
    return find_fields(dfm, { names... });
}
