/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <istream>
#include <set>
#include <vector>

// Own
#include <dfm/lexer/lex.h>
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/weed.h>

dfm::pt::node dfm::pt::weed(const dfm::pt::node& n)
{
    auto weeded_n = n;
    if (weeded_n.is_leaf())
    {
        return weeded_n;
    }

    const struct
    {
        bool remove_ws = true;
        bool remove_empty_children = true;
        bool merge_binary = true;
    } cfg;

    if (cfg.remove_ws)
    {
        // Remove <WS> tokens
        std::erase_if(weeded_n.children, [](auto& x) { return x.type == dfm::pt::ntypes::WS; });
        // Remove <HWS> tokens
        std::erase_if(weeded_n.children, [](auto& x) { return x.type == dfm::pt::ntypes::HWS; });
    }

    if (cfg.remove_empty_children)
    {
        // Remove Empty Children
        std::erase_if(weeded_n.children, [](auto& x) { return x.offset() == 0; });
    }

    if (cfg.merge_binary)
    {
        // Merge Binary
        if (weeded_n.type == dfm::pt::ntypes::VALUE_BINARY)
        {
            assert(weeded_n.children.size() >= 2);
            assert(weeded_n.children.front().token == dfm::lexer::token::CURLY_BRACKET_LEFT);
            assert(weeded_n.children.back().token == dfm::lexer::token::CURLY_BRACKET_RIGHT);
            while (weeded_n.children.size() > 3)
            {
                weeded_n.children[ 1 ].token += weeded_n.children[ 2 ].token;
                weeded_n.children.erase(weeded_n.children.begin() + 2);
            }
            assert(weeded_n.children.front().token == dfm::lexer::token::CURLY_BRACKET_LEFT);
            assert(weeded_n.children.back().token == dfm::lexer::token::CURLY_BRACKET_RIGHT);
        }
    }

    auto it = weeded_n.children.begin();
    while (it != weeded_n.children.end())
    {
        *it = weed(*it);
        if (it->type == dfm::pt::ntypes::NL)
        {
            it = weeded_n.children.erase(it);
        }
        else
        {
            ++it;
        }
    }

    return weeded_n;
}
