/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std

// Own
#include <dfm/ast/node.h>
#include <dfm/ast/node_dfm.h>
#include <dfm/ast/parse.h>
#include <dfm/ast/parse/helper.h>
#include <dfm/pt/node.h>

dfm::ast::node_dfm dfm::ast::parse::dfm(const dfm::pt::node& n)
{
    if (n.type != dfm::pt::ntypes::DFM)
    {
        throw dfm::ast::parse_error(n, __PRETTY_FUNCTION__);
    }

    if (n.children.empty())
    {
        throw dfm::ast::parse_error(n, "DFM Node does not contain any children");
    }

    if (n.children.size() != 1)
    {
        throw dfm::ast::parse_error(n, "DFM Node does contain more than one children");
    }

    dfm::ast::node_dfm dfm_obj;
    {
        for (const auto& child : n.children)
        {
            if (child.type == dfm::pt::ntypes::NL)
            {
                continue;
            }
            if (child.type == dfm::pt::ntypes::WS)
            {
                continue;
            }

            if (child.type == dfm::pt::ntypes::OBJ)
            {
                dfm_obj.obj = dfm::ast::parse::obj(child);
            }
            else
            {
                throw dfm::ast::parse_error(n, "Unexpected Note Type (Expected OBJ)");
            }
        }
    }
    return dfm_obj;
}
