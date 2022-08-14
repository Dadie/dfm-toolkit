/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext
#include <docopt/docopt.h>

// Std
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// Own
#include <dfm/ast/parse.h>
#include <dfm/lexer/lex.h>
#include <dfm/lexer/token.h>
#include <dfm/lexer/weed.h>
#include <dfm/license.h>
#include <dfm/pt/node.h>
#include <dfm/pt/parse.h>
#include <dfm/pt/parse_error.h>
#include <dfm/pt/weed.h>

static constexpr std::string_view DFM_PROJECTS_TOOL_NAME = "dfm-formatter";
static constexpr std::string_view DFM_PROJECTS_TOOL_URL = "https://github.com/Dadie/dfm-toolkit";
static constexpr std::string_view DFM_PROJECTS_LICENSE = R"(MIT License

Copyright (c) 2022 Daniel Korner

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.)";

static constexpr std::string_view DOCOPT_CPP_NAME = "docopt.cpp";
static constexpr std::string_view DOCOPT_CPP_URL = "https://github.com/docopt/docopt.cpp";
static constexpr std::string_view DOCOPT_CPP_LICENSE = R"(Copyright (c) 2012 Vladimir Keleshev, <vladimir@keleshev.com>

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to
whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall
be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.)";

const auto g_sep = std::string(80, '=');
const auto g_sep_gt = std::string(80, '>');
const auto g_sep_lt = std::string(80, '<');

static const std::string USAGE =
    R"(dfm-formatter

    Usage:
      dfm-formatter [options] <DFM-PATH>
      dfm-formatter -h | --help
      dfm-formatter --version
      dfm-formatter --license

    Options:
      -h --help                    Show this screen.
      -v --version                 Show version.
      -i --inplace                 Replace the DFM file. [default: false]
      -d <LVL> --debug=<LVL>       Enable debug output (0 = none, 1 = tokens, 2 = unweeded parse tree, 3 = weeded parse tree) [default: 0]
      -p <LVL> --padding=<LVL>     Number of spaces for padding. [default: 2]
      --license                    Show licenses. [default: false]
)";

int main(int argc, const char** argv)
{
    // Read CLI Config
    std::map< std::string, docopt::value > args;
    {
        args = docopt::docopt(USAGE,
            { argv + 1, argv + argc },
            true,                    // show help if requested
            "dfm-formatter  0.1.0"); // version string
    }

    // Set Config
    const auto filename = args[ "<DFM-PATH>" ].isString() ? args[ "<DFM-PATH>" ].asString() : "";
    const bool in_place = args[ "--inplace" ].asBool();
    const auto padding = static_cast< size_t >(std::max(0l, args[ "--padding" ].asLong()));
    const auto debug_lvl = static_cast< uint8_t >(std::max(0l, args[ "--debug" ].asLong()));
    const bool show_license = args[ "--license" ].asBool();

    if (show_license)
    {
        std::cout << g_sep << std::endl;
        std::cout << DFM_PROJECTS_TOOL_NAME << " " << DFM_PROJECTS_TOOL_URL << std::endl;
        std::cout << DFM_PROJECTS_LICENSE << std::endl;
        std::cout << g_sep << std::endl;
        std::cout << std::endl;

        std::cout << "Used Libraries:" << std::endl;
        std::cout << g_sep << std::endl;
        std::cout << dfm::LIBDFM_NAME() << " " << dfm::LIBDFM_URL() << std::endl;
        std::cout << dfm::LIBDFM_LICENSE() << std::endl;
        std::cout << g_sep << std::endl;

        std::cout << g_sep << std::endl;
        std::cout << DOCOPT_CPP_NAME << " " << DOCOPT_CPP_URL << std::endl;
        std::cout << DOCOPT_CPP_LICENSE << std::endl;
        std::cout << g_sep << std::endl;

        return EXIT_SUCCESS;
    }

    // Simple Lexer
    const std::vector< dfm::lexer::token_type > tokens = [ & ]()
    {
        auto ifs = std::ifstream(filename);
        return dfm::lexer::weed(dfm::lexer::lex(ifs));
    }();

    if (debug_lvl > 0)
    {
        std::cout << "TOKENS:" << std::endl;
        std::cout << g_sep << std::endl;
        for (const auto& t : tokens)
        {
            std::cout << t << std::endl;
        }
        std::cout << g_sep << std::endl;
        std::cout << std::endl;
    }

    // Simple PTfy
    const auto root_pt = dfm::pt::parse::dfm(tokens, 0);
    if (root_pt.offset() != tokens.size())
    {
        throw dfm::pt::parse_error(
            dfm::pt::ntypes::ROOT, tokens.at(root_pt.offset()), root_pt.offset(), dfm::pt::ntypes::EOF_);
    }
    const auto root_weed_pt = dfm::pt::weed(root_pt);

    if (debug_lvl > 1)
    {
        std::cout << "Unweeded Parse Tree:" << std::endl;
        std::cout << g_sep << std::endl;
        root_pt.pp();
        std::cout << g_sep << std::endl;
        std::cout << std::endl;
    }

    if (debug_lvl > 2)
    {
        std::cout << "Weeded Parse Tree:" << std::endl;
        std::cout << g_sep << std::endl;
        root_weed_pt.pp();
        std::cout << g_sep << std::endl;
        std::cout << std::endl;
    }

    // AST
    const auto root_ast = dfm::ast::parse::dfm(root_weed_pt);
    const auto dfm = root_ast.dfm(0, padding);
    if (in_place)
    {
        auto ofs = std::ofstream(filename);
        ofs << dfm;
    }
    else
    {
        std::cout << dfm;
    }

    return EXIT_SUCCESS;
}
