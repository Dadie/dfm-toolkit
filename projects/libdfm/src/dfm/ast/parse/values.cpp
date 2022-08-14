/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <algorithm>
#include <cassert>
#include <charconv>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_object.h>
#include <dfm/ast/node_value.h>
#include <dfm/ast/node_value_array.h>
#include <dfm/ast/node_value_binary.h>
#include <dfm/ast/node_value_bit.h>
#include <dfm/ast/node_value_constant.h>
#include <dfm/ast/node_value_float.h>
#include <dfm/ast/node_value_inline_object.h>
#include <dfm/ast/node_value_integer.h>
#include <dfm/ast/node_value_set.h>
#include <dfm/ast/node_value_string.h>
#include <dfm/ast/parse.h>
#include <dfm/ast/parse/helper.h>
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/utils/iconv.h>
#include <dfm/utils/unescape.h>

std::shared_ptr< dfm::ast::node_value > dfm::ast::parse::value(const dfm::pt::node& n)
{
    if (n.type == dfm::pt::ntypes::VALUE)
    {
        assert(n.size() == 1);
        return dfm::ast::parse::value(n[ 0 ]);
    }
    else if (n.type == dfm::pt::ntypes::VALUE_INTEGER)
    {
        return std::make_shared< dfm::ast::node_value_integer >(dfm::ast::parse::value_integer(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_FLOAT)
    {
        return std::make_shared< dfm::ast::node_value_float >(dfm::ast::parse::value_float(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_BIT)
    {
        return std::make_shared< dfm::ast::node_value_bit >(dfm::ast::parse::value_bit(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_CONSTANT)
    {
        return std::make_shared< dfm::ast::node_value_constant >(dfm::ast::parse::value_constant(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_STRING)
    {
        return std::make_shared< dfm::ast::node_value_string >(dfm::ast::parse::value_string(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_BINARY)
    {
        return std::make_shared< dfm::ast::node_value_binary >(dfm::ast::parse::value_binary(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_SET)
    {
        return std::make_shared< dfm::ast::node_value_set >(dfm::ast::parse::value_set(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_ARRAY)
    {
        return std::make_shared< dfm::ast::node_value_array >(dfm::ast::parse::value_array(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_INLINE_OBJECT)
    {
        return std::make_shared< dfm::ast::node_value_inline_object >(dfm::ast::parse::value_inline_object(n));
    }
    else if (n.type == dfm::pt::ntypes::VALUE_DATETIME)
    {
        return std::make_shared< dfm::ast::node_value_datetime >(dfm::ast::parse::value_datetime(n));
    }
    else
    {
        throw dfm::ast::parse_error(n, "Unexpected Node Type (Expected VALUE_*)");
    }
}

dfm::ast::node_value_integer dfm::ast::parse::value_integer(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_INTEGER)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    assert(n.token.size() > 0);
    dfm::ast::node_value_integer v;
    {
        if (n.token[ 0 ] == '$')
        {
            v.value = std::stoll(n.token.substr(1).c_str(), nullptr, 16);
            v.base = 16;
        }
        else
        {
            v.sign = n.token[ 0 ] == '-' || n.token[ 0 ] == '+';
            v.value = std::stoll(n.token.c_str());
            v.base = 10;
        }
    }
    return v;
}

dfm::ast::node_value_float dfm::ast::parse::value_float(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_FLOAT)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    assert(n.token.size() > 0);
    dfm::ast::node_value_float v;
    {
        assert(n.token.find('.') != n.token.npos);
        v.precision = n.token.size() - n.token.find('.');
        v.sign = n.token[ 0 ] == '-' || n.token[ 0 ] == '+';
        v.value = std::stod(n.token.c_str());
    }
    return v;
}

dfm::ast::node_value_constant dfm::ast::parse::value_constant(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_CONSTANT)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_value_constant v;
    {
        for (const auto& child : n.children)
        {
            assert(v.value.empty());
            if (child.type != dfm::pt::ntypes::DELPHI_NAME)
            {
                continue;
            }
            v.value = dfm::ast::parse::glue_delphi_name(child);
            break;
        }
    }
    return v;
}

dfm::ast::node_value_array dfm::ast::parse::value_array(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_ARRAY)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_value_array v;
    {
        if (n[ 1 ].type == dfm::pt::ntypes::VALUE_ARRAY_ITEMS)
        {
            const auto& value_array_items = n[ 1 ];
            for (const auto& value_array_item : value_array_items.children)
            {
                v.items.push_back(dfm::ast::parse::value_array_item(value_array_item));
            }
        }
    }
    return v;
}

dfm::ast::node_value_array_item dfm::ast::parse::value_array_item(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_ARRAY_ITEM)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_value_array_item v;
    {
        for (const auto& node : n.children)
        {
            if (node.type != dfm::pt::ntypes::VALUE_ARRAY_ITEM_PARAM)
            {
                continue;
            }
            v.params.push_back(dfm::ast::parse::parameter(node));
        }
    }
    return v;
}

dfm::ast::node_value_binary dfm::ast::parse::value_binary(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_BINARY)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_value_binary v;
    for (const auto& node : n.children)
    {
        if (node.type == dfm::pt::ntypes::HEX_CODE_STRING)
        {
            const auto& hex_node = node;
            const auto& hex_str = hex_node.token;
            const auto* hex_c_str = hex_str.c_str();
            for (size_t i = 0; i < hex_str.size(); i += 2)
            {
                uint16_t b = 0;
                {
                    std::from_chars(hex_c_str + i, hex_c_str + i + 2, b, 16);
                }
                assert(b <= 0xFF);
                v.value.push_back(static_cast< uint8_t >(b & 0xFF));
            }
        }
    }
    return v;
}

dfm::ast::node_value_set dfm::ast::parse::value_set(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_SET)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_value_set v;
    {
        if (n[ 1 ].type == dfm::pt::ntypes::VALUE_SET_VALUES)
        {
            const auto& value_set_values = n[ 1 ];
            for (const auto& node : value_set_values.children)
            {
                if (node.type == dfm::pt::ntypes::TOKEN)
                {
                    continue;
                }
                const auto& value_set_value = node;
                const auto& value = value_set_value.children.at(0);
                if (value.type == dfm::pt::ntypes::VALUE_CONSTANT)
                {
                    v.values.push_back(
                        std::make_shared< dfm::ast::node_value_constant >(dfm::ast::parse::value_constant(value)));
                }
                else if (value.type == dfm::pt::ntypes::VALUE_INTEGER)
                {
                    v.values.push_back(
                        std::make_shared< dfm::ast::node_value_integer >(dfm::ast::parse::value_integer(value)));
                }
                else if (value.type == dfm::pt::ntypes::VALUE_FLOAT)
                {
                    v.values.push_back(
                        std::make_shared< dfm::ast::node_value_float >(dfm::ast::parse::value_float(value)));
                }
                else if (value.type == dfm::pt::ntypes::VALUE_DATETIME)
                {
                    v.values.push_back(
                        std::make_shared< dfm::ast::node_value_datetime >(dfm::ast::parse::value_datetime(value)));
                }
                else
                {
                    throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__, __LINE__);
                }
            }
        }
    }
    return v;
}

dfm::ast::node_value_string dfm::ast::parse::value_string(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_STRING)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_value_string v;
    {
        v.parts = extract_string_elements(n);
    }
    return v;
}

dfm::ast::node_value_bit dfm::ast::parse::value_bit(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_BIT)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    assert(dfm::lexer::token::TRUE_ == n.token || dfm::lexer::token::FALSE_ == n.token);
    dfm::ast::node_value_bit v;
    {
        v.value = dfm::lexer::token::TRUE_ == n.token;
    }
    return v;
}

dfm::ast::node_value_inline_object dfm::ast::parse::value_inline_object(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_INLINE_OBJECT)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_value_inline_object v;
    {
        for (size_t i = 1; i < (n.size() - 1); i++)
        {
            const auto inline_v = dfm::ast::parse::value(n[ i ]);
            v.values.push_back(inline_v);
        }
    }
    return v;
}

dfm::ast::node_value_datetime dfm::ast::parse::value_datetime(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::VALUE_DATETIME)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    dfm::ast::node_value_datetime v;
    {
        assert(n.token.size() > 1);
        v.precision = 0;
        if (n.token.find('.') != n.token.npos)
        {
            v.precision = n.token.size() - n.token.find('.') - 1;
        }
        v.sign = n.token[ 0 ] == '-' || n.token[ 0 ] == '+';
        v.value = std::stod(n.token.substr(0, n.token.size() - 1).c_str());
    }
    return v;
}
