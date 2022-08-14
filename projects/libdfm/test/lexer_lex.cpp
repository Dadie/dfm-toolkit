/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <tuple>
#include <vector>

// Own
#include <dfm/lexer/lex.h>
#include <dfm/lexer/token.h>
#include <dfm/lexer/weed.h>
#include <dfm/utils/ci_string.h>

int lexer_lex(int argc, char** argv)
{
    if (argc < 2)
    {
        return EXIT_FAILURE;
    }

    struct
    {
        bool generate_files = true;
        bool allow_overwrite = false;
    } cfg;

    const std::filesystem::path dfm_in_path = argv[ 1 ];
    const std::filesystem::path out_path =
        dfm_in_path.parent_path().parent_path() / "exp" / "lexer" / dfm_in_path.stem().replace_extension(".token");

    auto ifs = std::ifstream(dfm_in_path);
    const auto tokens = dfm::lexer::lex(ifs);

    if (cfg.generate_files)
    {
        if (cfg.allow_overwrite || !std::filesystem::exists(out_path))
        {
            auto ofs = std::ofstream(out_path);
            for (const auto& token : tokens)
            {
                ofs << token << std::endl;
            }
        }
    }

    std::stringstream sstr;
    for (const auto& token : tokens)
    {
        sstr << token << std::endl;
    }
    sstr.seekg(0, sstr.beg);
    auto efs = std::ifstream(out_path);

    const bool ok = std::equal(std::istreambuf_iterator< char >(sstr.rdbuf()),
        std::istreambuf_iterator< char >(),
        std::istreambuf_iterator< char >(efs.rdbuf()));

    if (ok)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
