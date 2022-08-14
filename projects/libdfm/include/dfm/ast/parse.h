/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <memory>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_dfm.h>
#include <dfm/ast/node_object.h>
#include <dfm/ast/node_parameter.h>
#include <dfm/ast/node_value.h>
#include <dfm/ast/node_value_array.h>
#include <dfm/ast/node_value_array_item.h>
#include <dfm/ast/node_value_binary.h>
#include <dfm/ast/node_value_bit.h>
#include <dfm/ast/node_value_constant.h>
#include <dfm/ast/node_value_datetime.h>
#include <dfm/ast/node_value_float.h>
#include <dfm/ast/node_value_inline_object.h>
#include <dfm/ast/node_value_integer.h>
#include <dfm/ast/node_value_set.h>
#include <dfm/ast/node_value_string.h>
#include <dfm/ast/parse_error.h>
#include <dfm/pt/node.h>

namespace dfm::ast::parse
{
    dfm::ast::node_dfm dfm(const dfm::pt::node&);
    dfm::ast::node_object obj(const dfm::pt::node&);
    dfm::ast::node_parameter parameter(const dfm::pt::node&);

    std::shared_ptr< dfm::ast::node_value > value(const dfm::pt::node&);
    dfm::ast::node_value_integer value_integer(const dfm::pt::node&);
    dfm::ast::node_value_bit value_bit(const dfm::pt::node&);
    dfm::ast::node_value_float value_float(const dfm::pt::node&);
    dfm::ast::node_value_constant value_constant(const dfm::pt::node&);
    dfm::ast::node_value_array value_array(const dfm::pt::node&);
    dfm::ast::node_value_array_item value_array_item(const dfm::pt::node&);
    dfm::ast::node_value_binary value_binary(const dfm::pt::node&);
    dfm::ast::node_value_set value_set(const dfm::pt::node&);
    dfm::ast::node_value_string value_string(const dfm::pt::node&);
    dfm::ast::node_value_datetime value_datetime(const dfm::pt::node&);
    dfm::ast::node_value_inline_object value_inline_object(const dfm::pt::node&);

}
