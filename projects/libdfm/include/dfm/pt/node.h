/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/rule.h>

namespace dfm::pt
{
    using node_type = std::string;

    namespace ntypes
    {
        // RULE (LEFT SIDE)
        const dfm::pt::node_type DFM = "<DFM>";
        const dfm::pt::node_type OBJ = "<OBJ>";
        const dfm::pt::node_type OBJ_NAME = "<OBJ_NAME>";
        const dfm::pt::node_type OBJ_TYPE = "<OBJ_TYPE>";
        const dfm::pt::node_type OBJ_PARAMS = "<OBJ_PARAMS>";
        const dfm::pt::node_type OBJ_PARAM = "<OBJ_PARAM>";
        const dfm::pt::node_type OBJ_PARAM_NAME = "<OBJ_PARAM_NAME>";
        const dfm::pt::node_type VALUE = "<VALUE>";
        const dfm::pt::node_type VALUE_INTEGER = "<VALUE_INTEGER>";
        const dfm::pt::node_type VALUE_FLOAT = "<VALUE_FLOAT>";
        const dfm::pt::node_type VALUE_BIT = "<VALUE_BIT>";
        const dfm::pt::node_type VALUE_CONSTANT = "<VALUE_CONSTANT>";
        const dfm::pt::node_type VALUE_STRING = "<VALUE_STRING>";
        const dfm::pt::node_type VALUE_STRING_ELEMENT = "<VALUE_STRING_ELEMENT>";
        const dfm::pt::node_type VALUE_STRING_ELEMENT_CHAR = "<VALUE_STRING_ELEMENT_CHAR>";
        const dfm::pt::node_type VALUE_STRING_ELEMENT_STRING = "<VALUE_STRING_ELEMENT_STRING>";
        const dfm::pt::node_type VALUE_BINARY = "<VALUE_BINARY>";
        const dfm::pt::node_type VALUE_SET = "<VALUE_SET>";
        const dfm::pt::node_type VALUE_ARRAY = "<VALUE_ARRAY>";
        const dfm::pt::node_type VALUE_INLINE_OBJECT = "<VALUE_INLINE_OBJECT>";
        const dfm::pt::node_type VALUE_DATETIME = "<VALUE_DATETIME>";
        const dfm::pt::node_type HEX_CODE_STRING = "<HEX_CODE_STRING>";
        const dfm::pt::node_type VALUE_SET_VALUES = "<VALUE_SET_VALUES>";
        const dfm::pt::node_type VALUE_SET_VALUE = "<VALUE_SET_VALUE>";
        const dfm::pt::node_type VALUE_ARRAY_ITEMS = "<VALUE_ARRAY_ITEMS>";
        const dfm::pt::node_type VALUE_ARRAY_ITEM = "<VALUE_ARRAY_ITEM>";
        const dfm::pt::node_type VALUE_ARRAY_ITEM_PARAM = "<VALUE_ARRAY_ITEM_PARAM>";
        const dfm::pt::node_type VALUE_ARRAY_ITEM_PARAM_NAME = "<VALUE_ARRAY_ITEM_PARAM_NAME>";
        const dfm::pt::node_type ANY_CHARS = "<ANY_CHARS>";
        const dfm::pt::node_type NL = "<NL>";
        const dfm::pt::node_type WS = "<WS>";
        const dfm::pt::node_type HWS = "<HWS>";
        const dfm::pt::node_type DELPHI_IDENTIFIER = "<DELPHI_IDENTIFIER>";
        const dfm::pt::node_type DELPHI_NAME = "<DELPHI_NAME>";

        // META SYMBOLS
        const dfm::pt::node_type ROOT = "<ROOT>";
        const dfm::pt::node_type TOKEN = "<TOKEN>";
        const dfm::pt::node_type EOF_ = "<EOF>";
    }

    struct node
    {
        node_type type;
        rule_type rule;
        dfm::lexer::token_type token;
        std::vector< dfm::pt::node > children;

        dfm::pt::node& operator[](size_t pos)
        {
            return children[ pos ];
        }

        const dfm::pt::node& operator[](size_t pos) const
        {
            return children[ pos ];
        }

        size_t size() const noexcept
        {
            return children.size();
        }
        size_t offset() const noexcept;
        bool is_leaf() const noexcept;
        void pp(const size_t lvl = 0, std::ostream& ostr = std::cout) const noexcept;
    };
}
