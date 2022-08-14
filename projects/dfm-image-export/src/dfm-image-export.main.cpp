/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext
#include <docopt/docopt.h>

// Std
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// libdfm
#include <dfm/ast/load.h>
#include <dfm/ast/parse.h>
#include <dfm/lexer/lex.h>
#include <dfm/lexer/token.h>
#include <dfm/lexer/weed.h>
#include <dfm/license.h>
#include <dfm/pt/node.h>
#include <dfm/pt/parse.h>
#include <dfm/pt/parse_error.h>
#include <dfm/pt/weed.h>
#include <dfm/utils/ci_string.h>
#include <dfm/utils/form/envelope.h>
#include <dfm/utils/form/find.h>
#include <dfm/utils/image/bmp32.h>
#include <dfm/utils/io.h>
#include <dfm/utils/replace.h>

// Own
#include <exp/data.h>
#include <exp/generic_single_bmp.h>
#include <exp/timage.h>
#include <exp/timagelist.h>

static constexpr std::string_view DFM_PROJECTS_TOOL_NAME = "dfm-image-export";
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
    R"(dfm-image-export

    Usage:
      dfm-image-export [options] <DFM-PATH> <OUT-PATH>
      dfm-image-export -h | --help
      dfm-image-export --version
      dfm-image-export --license

    Options:
      --raw                        Output raw images. [default: false]
      -h --help                    Show this screen.
      -v --version                 Show version.
      --license                    Show licenses. [default: false]
)";

enum class expr_filter_type : uint64_t
{
    TYPE = 1,
    FIELD = 2,
};
inline expr_filter_type operator||(const expr_filter_type& lhs, const expr_filter_type& rhs)
{
    return expr_filter_type((uint64_t(lhs) | uint64_t(rhs)));
}
inline expr_filter_type operator&&(const expr_filter_type& lhs, const expr_filter_type& rhs)
{
    return expr_filter_type((uint64_t(lhs) & uint64_t(rhs)));
}

struct exporter
{
    bool enabled {};
    expr_filter_type ftype;
    dfm::utils::ci_string ffield_name {};
    dfm::utils::ci_string ftype_name {};
    std::function< void(const dfm::ast::node_dfm&,
        const std::string& /* nspath */,
        const std::string& /* outpath */,
        const dfm::ast::node* /* node */,
        const bool /* out_raw */) >
        func;
};

template < size_t Size >
static void export_generic_single_bmp(const dfm::ast::node_dfm&,
    const std::string& nspath,
    const std::string& outpath,
    const dfm::ast::node* node,
    const bool out_raw)
{
    const auto* node_param = dynamic_cast< const dfm::ast::node_parameter* >(node);
    const auto node_binary = std::dynamic_pointer_cast< dfm::ast::node_value_binary >(node_param->param_value);
    exp::generic_single_bmp< dfm::utils::form::dfm_generic_header< 4 > >(nspath, outpath, node_binary->value, out_raw);
}

static void export_timage(const dfm::ast::node_dfm&,
    const std::string& nspath,
    const std::string& outpath,
    const dfm::ast::node* node,
    const bool out_raw)
{
    exp::timage(nspath, outpath, node, out_raw);
}

static void export_timagelist(const dfm::ast::node_dfm&,
    const std::string& nspath,
    const std::string& outpath,
    const dfm::ast::node* node,
    const bool out_raw)
{
    exp::timagelist(nspath, outpath, node, out_raw);
}

static void export_raw_icon(const dfm::ast::node_dfm&,
    const std::string& nspath,
    const std::string& outpath,
    const dfm::ast::node* node,
    const bool out_raw)
{
    const auto* node_param = dynamic_cast< const dfm::ast::node_parameter* >(node);
    const auto node_binary = std::dynamic_pointer_cast< dfm::ast::node_value_binary >(node_param->param_value);
    exp::data("ico", nspath, outpath, node_binary->value, out_raw);
}

int main(int argc, const char** argv)
{

    // Read CLI Config
    std::map< std::string, docopt::value > args;
    {
        args = docopt::docopt(USAGE,
            { argv + 1, argv + argc },
            true,                       // show help if requested
            "dfm-image-export  0.1.0"); // version string
    }

    // Set Config
    const auto filename = args[ "<DFM-PATH>" ].isString() ? args[ "<DFM-PATH>" ].asString() : "";
    const auto outpath =
        (args[ "<OUT-PATH>" ].isString() ? args[ "<OUT-PATH>" ].asString() : "") + "/" + filename + "/";
    const bool show_license = args[ "--license" ].asBool();
    const bool out_raw = args[ "--raw" ].asBool();

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

    // Info
    std::cout << "Process file: " << filename << std::endl;
    // Load DFM File to AST
    const auto root_ast = dfm::ast::load(filename);

    const std::vector< exporter > exprs {
        {
            .enabled = true,
            .ftype = expr_filter_type::FIELD,
            .ffield_name = "Bitmap.Data",
            .func = &export_generic_single_bmp< 4 >,
        },
        {
            .enabled = true,
            .ftype = expr_filter_type::FIELD,
            .ffield_name = "Glyph.Data",
            .func = &export_generic_single_bmp< 4 >,
        },
        {
            .enabled = true,
            .ftype = expr_filter_type::FIELD,
            .ffield_name = "Icon.Data",
            .func = &export_raw_icon,
        },
        {
            .enabled = true,
            .ftype = expr_filter_type::TYPE,
            .ftype_name = "TImage",
            .func = &export_timage,
        },
        {
            .enabled = true,
            .ftype = expr_filter_type::TYPE,
            .ftype_name = "TImageList",
            .func = &export_timagelist,
        },
    };

    for (const auto& expr : exprs)
    {
        if (!expr.enabled)
        {
            continue;
        }
        std::vector< dfm::utils::form::find_match > matches;
        if ((expr.ftype && expr_filter_type::FIELD) == expr_filter_type::FIELD)
        {
            assert(matches.empty()); // Currently not supported dual filtering
            matches = dfm::utils::form::find_field(root_ast, expr.ffield_name);
        }
        if ((expr.ftype && expr_filter_type::TYPE) == expr_filter_type::TYPE)
        {
            assert(matches.empty()); // Currently not supported dual filtering
            matches = dfm::utils::form::find_type(root_ast, expr.ftype_name);
        }
        for (const auto& [ nspath, node ] : matches)
        {
            std::cout << "    "
                      << "Process Node: " << nspath << std::endl;
            expr.func(root_ast, nspath, outpath, node, out_raw);
        }
    }

    return EXIT_SUCCESS;
}
