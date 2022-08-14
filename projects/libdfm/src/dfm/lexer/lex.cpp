/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <iostream>
#include <istream>
#include <vector>

// Own
#include <dfm/lexer/lex.h>
#include <dfm/lexer/token.h>
#include <dfm/lexer/token_matcher.h>
#include <dfm/utils/iconv.h>

std::vector< dfm::lexer::token_type > dfm::lexer::lex(std::istream& is)
{
    using namespace std::string_literals;

    // Matcher
    dfm::lexer::token_matcher_composition nfa;
    {
        nfa.add< dfm::lexer::token_matcher_comment >();
        nfa.add< dfm::lexer::token_matcher_integer_datetime >();
        nfa.add< dfm::lexer::token_matcher_float_datetime >();
        nfa.add< dfm::lexer::token_matcher_float >();
        nfa.add< dfm::lexer::token_matcher_integer >();

        nfa.add< dfm::lexer::token_matcher_hex >();
        nfa.add< dfm::lexer::token_matcher_non_special >();
        nfa.add< dfm::lexer::token_matcher_string >();
        nfa.add< dfm::lexer::token_matcher_string_char >();

        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::COLON);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::EQUAL);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::COMMA);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::DOT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::AT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::CARET);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::HASH);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::PLUS);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::MINUS);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::SPACE);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::TABULATOR);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::HEX);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::SLASH);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::CURLY_BRACKET_LEFT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::CURLY_BRACKET_RIGHT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::ROUND_BRACKET_LEFT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::ROUND_BRACKET_RIGHT);

        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::SQUARE_BRACKET_LEFT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::SQUARE_BRACKET_RIGHT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::ANGLE_BRACKET_LEFT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::ANGLE_BRACKET_RIGHT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::SINGLE_QUOTATION_MARK);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::DOUBLE_QUOTATION_MARK);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::ROUND_BRACKET_RIGHT);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::ROUND_BRACKET_RIGHT);

        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::CRLF_);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::CR_);
        nfa.add< dfm::lexer::token_matcher_token >(dfm::lexer::token::LF_);
    }

    // Load DFM file to buffer
    std::string buf;
    while (is.good())
    {
        char c;
        is.get(c);
        if (!is.good())
        {
            break;
        }
        buf.push_back(c);
    }

    // Copy buffer to content (might include recoding)
    std::string content;
    if (buf.starts_with("\x00\x00\xFE\xFF"s))
    {
        // UTF32 BE w. BOM
        content = dfm::utils::iconv::u32be_to_u8(buf.c_str() + 4, buf.size() - 4);
    }
    else if (buf.starts_with("\xFF\xFE\x00\x00"s))
    {
        // UTF32 LE w. BOM
        content = dfm::utils::iconv::u32le_to_u8(buf.c_str() + 4, buf.size() - 4);
    }
    else if (buf.starts_with("\xFF\xFE"s))
    {
        // UTF16 LE w. BOM
        content = dfm::utils::iconv::u16le_to_u8(buf.c_str() + 2, buf.size() - 2);
    }
    else if (buf.starts_with("\xFE\xFF"s))
    {
        // UTF16 BE w. BOM
        content = dfm::utils::iconv::u16be_to_u8(buf.c_str() + 2, buf.size() - 2);
    }
    else if (buf.starts_with("\xEF\xBB\xBF"s))
    {
        // UTF8 BOM w. BOM
        content = buf.substr(3);
    }
    else
    {
        size_t zero_p0 = 0;
        size_t zero_p1 = 0;
        size_t zero_p2 = 0;
        size_t zero_p3 = 0;

        size_t zero_total = 0;
        for (size_t i = 0; i < buf.size(); ++i)
        {
            if (buf[ i ] != '\0')
            {
                continue;
            }
            zero_p0 += ((i % 4) == 0) ? 1 : 0;
            zero_p1 += ((i % 4) == 1) ? 1 : 0;
            zero_p2 += ((i % 4) == 2) ? 1 : 0;
            zero_p3 += ((i % 4) == 3) ? 1 : 0;
            ++zero_total;
        }

        if ((zero_p2 + zero_p3) > (zero_p0 + zero_p1) && (zero_p2) > (zero_total / 4) && (zero_p3) > (zero_total / 4))
        {
            // More zeros on position 2,3 than on pos. 0,1 and more than 25% of the strings zeros are at pos. 2,3.
            // Assume UTF32LE
            content = dfm::utils::iconv::u32le_to_u8(buf.c_str(), buf.size());
        }
        else if ((zero_p0 + zero_p1) > (zero_p2 + zero_p3) && (zero_p0) > (zero_total / 4) &&
                 (zero_p1) > (zero_total / 4))
        {
            // More zeros on position 0,1 than on pos. 2,3 and more than 25% of the strings zeros are at pos. 0,1.
            // Assume UTF32BEE
            content = dfm::utils::iconv::u32be_to_u8(buf.c_str(), buf.size());
        }
        else if (zero_p0 > zero_p1 && zero_p0 > (zero_total / 4))
        {
            // More zeros on even than on odd position and more than 25% of the strings zeros are at even pos.
            // Assume UTF16BE
            content = dfm::utils::iconv::u16be_to_u8(buf.c_str(), buf.size());
        }
        else if (zero_p1 > zero_p0 && zero_p1 > (zero_total / 4))
        {
            // More zeros on odd than on even position and more than 25% of the strings zeros are at odd pos.
            // Assume UTF16LE
            content = dfm::utils::iconv::u16le_to_u8(buf.c_str(), buf.size());
        }
        else
        {
            // Unknown encoding, assume either ASCII, ISO8859 or UTF8
            content = buf;
        }
    }
    buf.clear();

    std::vector< dfm::lexer::token_type > tokens;
    size_t begin_sv = 0;
    size_t size_sv = 1;
    const auto* content_begin = content.c_str();
    while (begin_sv + size_sv <= content.size())
    {
        assert((begin_sv + size_sv) >= 1);
        const auto sv_prev =
            dfm::lexer::token_view_type(content_begin + begin_sv, content_begin + begin_sv + size_sv - 1);
        const auto sv = dfm::lexer::token_view_type(content_begin + begin_sv, content_begin + begin_sv + size_sv);

        if (nfa.ok(sv))
        {
            ++size_sv;
            continue;
        }
        const auto token = dfm::lexer::token_type(sv_prev);
        if (!nfa.ok(sv_prev))
        {
            std::cout << "[NFA:NOK] Found bad token '" << token << "'"
                      << " begin: " << begin_sv << " size: " << size_sv << std::endl;
            return {};
        }
        if (!nfa.accept(sv_prev))
        {
            std::cout << "[NFA:NAC] Found bad token '" << token << "'"
                      << " begin: " << begin_sv << " size: " << size_sv << std::endl;
            return {};
        }
        begin_sv += size_sv - 1;
        size_sv = 1;

        tokens.push_back(token);
    }

    return tokens;
}
