/* SPDX-License-Identifier: MIT */
/* Copyright © 2023 Daniel Korner */
/* {HEADER} */

// Ext
#include <docopt/docopt.h>
#include <nlohmann/json.hpp>

// Std
#include <cassert>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

// Own
#include <dfm/lexer/lex.h>
#include <dfm/lexer/token.h>
#include <dfm/lexer/weed.h>
#include <dfm/license.h>

static constexpr std::string_view DFM_PROJECTS_TOOL_NAME = "dfm-tokens";
static constexpr std::string_view DFM_PROJECTS_TOOL_URL = "https://github.com/Dadie/dfm-toolkit";
static constexpr std::string_view DFM_PROJECTS_LICENSE = R"(MIT License

Copyright (c) 2023 Daniel Korner

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

static constexpr std::string_view NLOHMANN_JSON_NAME = "nlohmann/json";
static constexpr std::string_view NLOHMANN_JSON_URL = "https://github.com/nlohmann/json/";
static constexpr std::string_view NLOHMANN_JSON_LICENSE = R"(MIT License 

Copyright (c) 2013-2022 Niels Lohmann

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

const auto g_sep = std::string(80, '=');
const auto g_sep_gt = std::string(80, '>');
const auto g_sep_lt = std::string(80, '<');

static const std::string USAGE =
    R"(dfm-tokens

    Usage:
      dfm-tokens <DFM-PATH>
      dfm-tokens -h | --help
      dfm-tokens --version
      dfm-tokens --license

    Options:
      -h --help                    Show this screen.
      -v --version                 Show version.
      --license                    Show licenses. [default: false]
)";

int main(int argc, const char** argv)
{
    // Read CLI Config
    std::map< std::string, docopt::value > args;
    {
        args = docopt::docopt(USAGE,
            { argv + 1, argv + argc },
            true,                 // show help if requested
            "dfm-tokens  0.1.0"); // version string
    }

    // Set Config
    const auto filename = args[ "<DFM-PATH>" ].isString() ? args[ "<DFM-PATH>" ].asString() : "";
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

        std::cout << g_sep << std::endl;
        std::cout << NLOHMANN_JSON_NAME << " " << NLOHMANN_JSON_URL << std::endl;
        std::cout << NLOHMANN_JSON_LICENSE << std::endl;
        std::cout << g_sep << std::endl;

        return EXIT_SUCCESS;
    }

    // Simple Lexer
    const std::vector< dfm::lexer::token_type > tokens = [ & ]()
    {
        auto ifs = std::ifstream(filename);
        return dfm::lexer::weed(dfm::lexer::lex(ifs),
            {
                .remove_empty_tokens = true,
                .remove_horizontal_whitespace = true,
                .normalize_newline = false,
                .remove_adjacent_newline = false,
                .remove_trailing_newline = false,
                .remove_comments = false,
            });
    }();

    // Output
    {
        nlohmann::json j;
        for (const auto& token : tokens)
        {
            j.push_back(token.c_str());
        }
        std::cout << j << std::endl;
    }

    return EXIT_SUCCESS;
}
