/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Own
#include <dfm/ast/node_object.h>
#include <dfm/lexer/token.h>

const dfm::ast::node_parameter& dfm::ast::node_object_parameter_helper::operator[](const size_t idx) const
{
    return __obj.params[ idx ];
}

const dfm::ast::node_parameter& dfm::ast::node_object_parameter_helper::operator[](
    const dfm::lexer::token_type& name) const
{
    using namespace std::literals::string_literals;
    for (const auto& param : __obj.params)
    {
        if (param.param_name == name)
        {
            return param;
        }
    }
    throw std::range_error("Could not find parameter '"s + name.c_str() + "'"s);
}

bool dfm::ast::node_object_parameter_helper::has(const size_t idx) const
{
    return __obj.params.size() > idx;
}

bool dfm::ast::node_object_parameter_helper::has(const dfm::lexer::token_type& name) const
{
    for (const auto& param : __obj.params)
    {
        if (param.param_name == name)
        {
            return true;
        }
    }
    return false;
}

const dfm::ast::node_object& dfm::ast::node_object_obj_helper::operator[](const size_t idx) const
{
    return __obj.objs[ idx ];
}

const dfm::ast::node_object& dfm::ast::node_object_obj_helper::operator[](const dfm::lexer::token_type& name) const
{
    using namespace std::literals::string_literals;
    for (const auto& obj : __obj.objs)
    {
        if (obj.obj_name == name)
        {
            return obj;
        }
    }
    throw std::range_error("Could not find object '"s + name.c_str() + "'"s);
}

bool dfm::ast::node_object_obj_helper::has(const size_t idx) const
{
    return __obj.objs.size() > idx;
}

bool dfm::ast::node_object_obj_helper::has(const dfm::lexer::token_type& name) const
{
    for (const auto& obj : __obj.objs)
    {
        if (obj.obj_name == name)
        {
            return true;
        }
    }
    return false;
}

std::string dfm::ast::node_object::dfm(const size_t lvl, const size_t pad) const noexcept
{
    const auto padding = std::string(lvl * pad, ' ');

    std::stringstream strstr;
    strstr << padding;
    strstr << this->obj_decl;
    strstr << dfm::lexer::token::SPACE;
    if (!this->obj_name.empty())
    {
        strstr << this->obj_name;
        strstr << dfm::lexer::token::COLON;
        strstr << dfm::lexer::token::SPACE;
    }
    strstr << this->obj_type;
    if (this->obj_idx_operator)
    {
        strstr << dfm::lexer::token::SPACE;
        strstr << dfm::lexer::token::SQUARE_BRACKET_LEFT;
        strstr << *(this->obj_idx_operator);
        strstr << dfm::lexer::token::SQUARE_BRACKET_RIGHT;
    }
    strstr << "\n";

    for (const auto& n : this->params)
    {
        strstr << n.dfm(lvl + 1, pad);
    }

    for (const auto& n : this->objs)
    {
        strstr << n.dfm(lvl + 1, pad);
    }

    strstr << padding;
    strstr << dfm::lexer::token::END;
    strstr << "\n";
    return strstr.str();
}

std::string dfm::ast::node_object::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
