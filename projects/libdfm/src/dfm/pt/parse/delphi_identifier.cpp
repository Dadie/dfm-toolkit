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
#include <dfm/utils/form/identifier.h>

dfm::pt::node dfm::pt::parse::delphi_identifier(const std::vector< dfm::lexer::token_type >& tokens, const size_t pos)
{
    static const dfm::pt::rule_type RULE = "DELPHI_IDENTIFIER := ...";
    __TOKEN_DEBUG(__PRETTY_FUNCTION__, tokens, pos, RULE);
    __TOKEN_RANGE_CHECK(__PRETTY_FUNCTION__, tokens, pos, RULE);

    dfm::pt::node n;
    {
        n.type = dfm::pt::ntypes::DELPHI_IDENTIFIER;
        n.rule = RULE;

        if (!dfm::utils::form::identifier::is_valid(tokens.at(pos)))
        {
            throw dfm::pt::parse_error(std::string("trigger: is_valid()"), RULE, tokens.at(pos), pos);
        }
        if (dfm::utils::form::identifier::is_keyword(tokens.at(pos)))
        {
            throw dfm::pt::parse_error(std::string("trigger: is_keyword()"), RULE, tokens.at(pos), pos);
        }
        n.token = tokens.at(pos);
    }
    return n;
}
