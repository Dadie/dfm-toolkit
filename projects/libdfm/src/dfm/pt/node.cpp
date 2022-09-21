/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <iostream>
#include <string>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/rule.h>

dfm::pt::node& dfm::pt::node::operator[](const size_t pos)
{
    return children[ pos ];
}

const dfm::pt::node& dfm::pt::node::operator[](const size_t pos) const
{
    return children[ pos ];
}

size_t dfm::pt::node::size() const noexcept
{
    return children.size();
}

size_t dfm::pt::node::offset() const noexcept
{
    size_t i = token.empty() ? 0 : 1;
    for (const auto& child : children)
    {
        i += child.offset();
    }
    return i;
}

bool dfm::pt::node::is_leaf() const noexcept
{
    return children.empty();
}

void dfm::pt::node::pp(const size_t lvl, std::ostream& ostr) const noexcept
{
    const std::string pad = std::string(lvl * 4u, ' ');
    ostr << pad << "type:" << type;
    if (!token.empty())
    {
        ostr << " value:" << token;
    }
    ostr << std::endl;
    for (const auto& child : children)
    {
        child.pp(lvl + 1, ostr);
    }
}
