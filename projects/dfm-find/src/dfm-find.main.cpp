/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext
#include <docopt/docopt.h>

// Std
#include <algorithm>
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
#include <dfm/utils/form/find.h>

static constexpr std::string_view DFM_PROJECTS_TOOL_NAME = "dfm-find";
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
    R"(dfm-find

    Usage:
      dfm-find [options] <DFM-PATH>
      dfm-find -h | --help
      dfm-find --version
      dfm-find --license

    Options:
      -h --help                    Show this screen.
      -v --version                 Show version.
      --no-print-matches           Don't brint the matches found.
      -t <TYPE> --type=<TYPE>      Search for fields with this type.
      -n <NAME> --name=<NAME>      Search for fields with this name.
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
            true,               // show help if requested
            "dfm-find  0.1.0"); // version string
    }

    // Set Config
    const auto filename = args[ "<DFM-PATH>" ].isString() ? args[ "<DFM-PATH>" ].asString() : "";
    const auto print_matches = args.contains("--no-print-matches") && (!args[ "--no-print-matches" ].asBool());
    const auto search_type = args[ "--type" ].isString() ? args[ "--type" ].asString() : "";
    const auto search_name = args[ "--name" ].isString() ? args[ "--name" ].asString() : "";
    const auto padding = static_cast< size_t >(std::max(0l, args[ "--padding" ].asLong()));
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

    // Simple PTfy
    const auto root_pt = dfm::pt::parse::dfm(tokens, 0);
    if (root_pt.offset() != tokens.size())
    {
        throw dfm::pt::parse_error(
            dfm::pt::ntypes::ROOT, tokens.at(root_pt.offset()), root_pt.offset(), dfm::pt::ntypes::EOF_);
    }
    const auto root_weed_pt = dfm::pt::weed(root_pt);

    // AST
    const auto root_ast = dfm::ast::parse::dfm(root_weed_pt);

    // Find
    std::vector< dfm::utils::form::find_match > matches;
    {
        std::vector< dfm::utils::form::find_match > type_matches;
        std::vector< dfm::utils::form::find_match > name_matches;
        if (!search_type.empty())
        {
            type_matches = dfm::utils::form::find_type(root_ast, search_type.c_str());
        }
        if (!search_name.empty())
        {
            name_matches = dfm::utils::form::find_field(root_ast, search_name.c_str());
        }
        if (!search_type.empty() && search_name.empty())
        {
            // Pure Type Search
            matches = type_matches;
        }
        if (search_type.empty() && !search_name.empty())
        {
            // Pure Name Search
            matches = name_matches;
        }
        if (!search_type.empty() && !search_name.empty())
        {
            for (const auto& type_match : type_matches)
            {
                bool found = false;
                for (const auto& name_match : name_matches)
                {
                    if (type_match == name_match)
                    {
                        found = true;
                        break;
                    }
                }
                if (found)
                {
                    matches.push_back(type_match);
                }
            }
        }
    }

    // Print information about the found matches
    std::cout << std::string(80, '=') << std::endl;
    const auto cout_flags = std::cout.flags();

    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout.width(16);
    std::cout << ("DFM") << ':';
    std::cout.width(60);
    std::cout << (' ' + filename);
    std::cout << std::endl;

    if (!search_type.empty())
    {
        std::cout.width(16);
        std::cout << ("Search for type") << ':';
        std::cout.width(60);
        std::cout << (' ' + search_type);
        std::cout << std::endl;
    }

    if (!search_name.empty())
    {
        std::cout.width(16);
        std::cout << ("Search for name") << ':';
        std::cout.width(60);
        std::cout << (' ' + search_name);
        std::cout << std::endl;
    }

    std::cout.width(16);
    std::cout << ("Found Matches") << ':';
    std::cout.width(60);
    std::cout << (' ' + std::to_string(matches.size()));
    std::cout << std::endl;

    std::cout.flags(cout_flags);
    std::cout << std::string(80, '=') << std::endl;

    // Print the found matches
    size_t i = 0;
    for (const auto& match : matches)
    {
        std::cout << std::string(80, '<') << std::endl;
        std::cout << "Match : " << i << std::endl;
        std::cout << "Path  : " << std::get< std::string >(match) << std::endl;
        std::cout << "Node  : " << std::endl;
        std::cout << std::get< const dfm::ast::node* >(match)->dfm(0, padding);
        std::cout << std::string(80, '>') << std::endl;
        ++i;
    }

    return EXIT_SUCCESS;
}
