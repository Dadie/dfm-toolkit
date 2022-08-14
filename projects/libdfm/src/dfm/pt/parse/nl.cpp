/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <exception>
#include <functional>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

// Own
#include <dfm/lexer/token.h>
#include <dfm/pt/node.h>
#include <dfm/pt/parse.h>
#include <dfm/pt/parse/helper.h>
#include <dfm/pt/parse_error.h>
#include <dfm/utils/debug.h>

dfm::pt::node dfm::pt::parse::nl(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "NL := '\\r'|'\\n'|'\\r\\n'|'\\v|'\\f'|'%x85'";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::NL;
        n.rule = RULE;

        auto i = pos;
        do
        {
            if (tokens.at(i) == dfm::lexer::token::LF_)
            {
                n.token = tokens.at(i);
                break;
            }
            if (tokens.at(i) == dfm::lexer::token::CR_)
            {
                n.token = tokens.at(i);
                break;
            }
            if (tokens.at(i) == dfm::lexer::token::CRLF_)
            {
                n.token = tokens.at(i);
                break;
            }
            if (tokens.at(i) == dfm::lexer::token::NEWLINE)
            {
                n.token = tokens.at(i);
                break;
            }
            if (tokens.at(i) == dfm::lexer::token::VERTICAL_TABULATOR)
            {
                n.token = tokens.at(i);
                break;
            }
            if (tokens.at(i) == dfm::lexer::token::FORM_FEED)
            {
                n.token = tokens.at(i);
                break;
            }
            if (tokens.at(i) == dfm::lexer::token::NEL_)
            {
                n.token = tokens.at(i);
                break;
            }

            throw dfm::pt::parse_error(RULE, tokens.at(i), i);
        } while (false);
    }
    return n;
}
