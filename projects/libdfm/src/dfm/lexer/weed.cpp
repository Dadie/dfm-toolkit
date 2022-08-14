/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <algorithm>
#include <cassert>
#include <istream>
#include <set>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/lexer/weed.h>

namespace dfm::lexer
{
    std::vector< dfm::lexer::token_type > weed(
        const std::vector< dfm::lexer::token_type >& tokens, const bool remove_comments)
    {
        const struct
        {
            bool remove_empty_tokens = true;
            bool remove_horizontal_whitespace = true;
            bool normalize_newline = true;
            bool remove_adjacent_newline = true;
            bool remove_trailing_newline = true;
        } cfg;

        std::vector< dfm::lexer::token_type > wtokens { tokens.begin(), tokens.end() };

        // Remove empty tokens
        if (cfg.remove_empty_tokens)
        {
            std::erase_if(wtokens, [](const auto t) { return t.empty(); });
        }

        // Remove pure horizontal white space tokens
        if (cfg.remove_horizontal_whitespace)
        {
            std::vector< dfm::lexer::token_type > wcopy;
            for (const auto& token : wtokens)
            {
                if (token.find_first_not_of(" \t\v\xA0") == token.npos)
                {
                    continue;
                }
                wcopy.push_back(token);
            }
            wtokens = wcopy;
        }

        // Normalize newline
        if (cfg.normalize_newline)
        {
            std::replace(wtokens.begin(), wtokens.end(), dfm::lexer::token_type("\n"), dfm::lexer::token::NEWLINE);
            std::replace(wtokens.begin(), wtokens.end(), dfm::lexer::token_type("\r"), dfm::lexer::token::NEWLINE);
            std::replace(wtokens.begin(), wtokens.end(), dfm::lexer::token_type("\n\r"), dfm::lexer::token::NEWLINE);
            std::replace(wtokens.begin(), wtokens.end(), dfm::lexer::token_type("\v"), dfm::lexer::token::NEWLINE);
            std::replace(wtokens.begin(), wtokens.end(), dfm::lexer::token_type("\f"), dfm::lexer::token::NEWLINE);
            std::replace(wtokens.begin(), wtokens.end(), dfm::lexer::token_type("\x85"), dfm::lexer::token::NEWLINE);
        }

        // Remove adjacent new lines
        if (cfg.remove_adjacent_newline)
        {
            std::vector< dfm::lexer::token_type > wcopy;
            for (const auto& token : wtokens)
            {
                if (!wcopy.empty() && token == dfm::lexer::token::NEWLINE && wcopy.back() == dfm::lexer::token::NEWLINE)
                {
                    // SKIP
                    continue;
                }
                wcopy.push_back(token);
            }
            wtokens = wcopy;
        }

        // Remove comments
        {
            if (remove_comments)
            {
                const auto comment_prefix = dfm::lexer::token::SLASH + dfm::lexer::token::SLASH;
                std::erase_if(wtokens, [ & ](const auto t) { return t.starts_with(comment_prefix); });
            }
        }

        // Remove trailing newline
        if (cfg.remove_trailing_newline)
        {
            while (!wtokens.empty() && wtokens.back() == dfm::lexer::token::NEWLINE)
            {
                wtokens.pop_back();
            }
        }

        // Remove empty tokens again (as some weedning might have introduced empty tokens)
        if (cfg.remove_empty_tokens)
        {
            std::erase_if(wtokens, [](const auto t) { return t.empty(); });
        }

        return wtokens;
    }
}
