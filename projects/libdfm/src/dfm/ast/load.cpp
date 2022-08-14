/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <filesystem>
#include <fstream>
#include <vector>

// Own
#include <dfm/ast/load.h>
#include <dfm/ast/node_dfm.h>
#include <dfm/ast/parse.h>
#include <dfm/lexer/lex.h>
#include <dfm/lexer/token.h>
#include <dfm/lexer/weed.h>
#include <dfm/pt/node.h>
#include <dfm/pt/parse.h>
#include <dfm/pt/parse_error.h>
#include <dfm/pt/weed.h>

dfm::ast::node_dfm dfm::ast::load(const std::filesystem::path& path)
{
    // Simple Lexer
    const std::vector< dfm::lexer::token_type > tokens = [ & ]()
    {
        auto ifs = std::ifstream(path);
        return dfm::lexer::weed(dfm::lexer::lex(ifs));
    }();

    // Simple PTfy
    const auto root_pt = dfm::pt::parse::dfm(tokens, 0);
    if (root_pt.offset() != tokens.size())
    {
        throw dfm::pt::parse_error(
            dfm::pt::ntypes::ROOT, tokens.at(root_pt.offset()), root_pt.offset(), dfm::pt::ntypes::EOF_);
    }
    const auto root_weed_pt = dfm::pt::weed(root_pt);

    // AST
    return dfm::ast::parse::dfm(root_weed_pt);
}
