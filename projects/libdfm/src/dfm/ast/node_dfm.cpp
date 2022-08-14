/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Own
#include <dfm/ast/node_dfm.h>

std::string dfm::ast::node_dfm::dfm(const size_t lvl, const size_t pad) const noexcept
{
    const auto padding = std::string(lvl * pad, ' ');

    std::stringstream strstr;
    {
        strstr << padding;
        strstr << this->obj.dfm(lvl, pad);
    }
    return strstr.str();
}

std::string dfm::ast::node_dfm::pp(const size_t lvl, const size_t pad) const noexcept
{
    std::stringstream strstr;
    // TODO
    return strstr.str();
}
