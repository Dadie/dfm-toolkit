/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <regex>

// Own
#include <dfm/lexer/token.h>
#include <dfm/lexer/token_matcher.h>
#include <dfm/utils/simple_nfa.h>

static constexpr auto s0 = dfm::utils::simple_nfa_state(0);
static constexpr auto s1 = dfm::utils::simple_nfa_state(1);
static constexpr auto s2 = dfm::utils::simple_nfa_state(2);
static constexpr auto s3 = dfm::utils::simple_nfa_state(3);
static constexpr auto s4 = dfm::utils::simple_nfa_state(4);
static constexpr auto s5 = dfm::utils::simple_nfa_state(5);
static constexpr auto s6 = dfm::utils::simple_nfa_state(6);
static constexpr auto s7 = dfm::utils::simple_nfa_state(7);
static constexpr auto s8 = dfm::utils::simple_nfa_state(8);
static constexpr auto s9 = dfm::utils::simple_nfa_state(9);
static constexpr auto s10 = dfm::utils::simple_nfa_state(10);
static constexpr auto s11 = dfm::utils::simple_nfa_state(11);
static constexpr auto s12 = dfm::utils::simple_nfa_state(12);
static constexpr auto s13 = dfm::utils::simple_nfa_state(13);
static constexpr auto s14 = dfm::utils::simple_nfa_state(14);
static constexpr auto s15 = dfm::utils::simple_nfa_state(15);

static const auto nfa_match_hex_chars = dfm::utils::simple_nfa_match_chars("0123456789abcdefABCDEF");
static const auto nfa_match_dec_chars = dfm::utils::simple_nfa_match_chars("0123456789");

// #############################################################################
bool dfm::lexer::token_matcher_token::accept(const dfm::lexer::token_view_type& sv) const
{
    return m_token == sv;
}

bool dfm::lexer::token_matcher_token::ok(const dfm::lexer::token_view_type& sv) const
{
    if (sv.size() > m_token.size())
    {
        return false;
    }
    return m_token.starts_with(sv);
}

// #############################################################################
static dfm::utils::simple_nfa< 4 > token_matcher_comment_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 4 > s;
    {
        s[ s0 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s1, dfm::utils::simple_nfa_match_chars("/"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s2, dfm::utils::simple_nfa_match_chars("/"));
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s2, dfm::utils::simple_nfa_match_not_chars("\r\n"));
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s3, dfm::utils::simple_nfa_match_chars("\n"));
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s4, dfm::utils::simple_nfa_match_chars("\n"));
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s4, dfm::utils::simple_nfa_match_chars("\r"));
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s4, dfm::utils::simple_nfa_match_chars("\n"));

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_comment::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_comment_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_comment::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_comment_run(sv);
    return s.ok();
}

// #############################################################################
static dfm::utils::simple_nfa< 2 > token_matcher_integer_datetime_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 2 > s;
    {
        s[ s0 ] = true;
        s[ s1 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s1, dfm::utils::simple_nfa_match_chars("+-"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s1, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s2, dfm::utils::simple_nfa_match_chars("dD"));

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_integer_datetime::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_integer_datetime_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_integer_datetime::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_integer_datetime_run(sv);
    return s.ok();
}

// #############################################################################
static dfm::utils::simple_nfa< 6 > token_matcher_float_datetime_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 6 > s;
    {
        s[ s0 ] = true;
        s[ s1 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s1, dfm::utils::simple_nfa_match_chars("+-"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s2, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s2, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s3, dfm::utils::simple_nfa_match_chars("."));
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s3, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s6, dfm::utils::simple_nfa_match_chars("dD"));

        next |= dfm::utils::simple_nfa_delta(c, s, s1, s4, dfm::utils::simple_nfa_match_chars("."));
        next |= dfm::utils::simple_nfa_delta(c, s, s4, s5, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s5, s5, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s5, s6, dfm::utils::simple_nfa_match_chars("dD"));

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_float_datetime::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_float_datetime_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_float_datetime::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_float_datetime_run(sv);
    return s.ok();
}

// #############################################################################
static dfm::utils::simple_nfa< 6 > token_matcher_float_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 6 > s;
    {
        s[ s0 ] = true;
        s[ s1 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s1, dfm::utils::simple_nfa_match_chars("+-"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s2, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s4, dfm::utils::simple_nfa_match_chars("."));
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s2, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s3, dfm::utils::simple_nfa_match_chars("."));
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s6, dfm::utils::simple_nfa_match_chars("."));
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s3, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s6, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s4, s5, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s4, s6, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s5, s5, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s5, s6, nfa_match_dec_chars);

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_float::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_float_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_float::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_float_run(sv);
    return s.ok();
}

// #############################################################################
static dfm::utils::simple_nfa< 2 > token_matcher_integer_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 2 > s;
    {
        s[ s0 ] = true;
        s[ s1 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s1, dfm::utils::simple_nfa_match_chars("+-"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s1, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s2, nfa_match_dec_chars);

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_integer::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_integer_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_integer::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_integer_run(sv);
    return s.ok();
}

// #############################################################################
static dfm::utils::simple_nfa< 2 > token_matcher_hex_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 2 > s;
    {
        s[ s0 ] = true;
        s[ s1 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s1, dfm::utils::simple_nfa_match_chars("$"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s1, nfa_match_hex_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s2, nfa_match_hex_chars);

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_hex::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_hex_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_hex::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_hex_run(sv);
    return s.ok();
}

// #############################################################################
static dfm::utils::simple_nfa< 1 > token_matcher_non_special_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 1 > s;
    {
        s[ s0 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(
            c, s, s0, s0, dfm::utils::simple_nfa_match_not_chars("\"':=,.@^#+- \t${}()[]<>\r\n\v\f"));
        next |= dfm::utils::simple_nfa_delta(
            c, s, s0, s1, dfm::utils::simple_nfa_match_not_chars("\"':=,.@^#+- \t${}()[]<>\r\n\v\f"));

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_non_special::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_non_special_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_non_special::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_non_special_run(sv);
    return s.ok();
}

// #############################################################################
static dfm::utils::simple_nfa< 4 > token_matcher_string_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 4 > s;
    {
        s[ s0 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s1, dfm::utils::simple_nfa_match_chars("'"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s1, dfm::utils::simple_nfa_match_not_chars("'\n\r\f"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s2, dfm::utils::simple_nfa_match_chars("'"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s4, dfm::utils::simple_nfa_match_chars("'"));
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s3, dfm::utils::simple_nfa_match_chars("'"));
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s4, dfm::utils::simple_nfa_match_chars("'"));
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s1, dfm::utils::simple_nfa_match_not_chars("'\n\r\f"));

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_string::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_string_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_string::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_string_run(sv);
    return s.ok();
}

// #############################################################################
static dfm::utils::simple_nfa< 4 > token_matcher_string_char_run(const dfm::lexer::token_view_type& sv)
{
    dfm::utils::simple_nfa< 4 > s;
    {
        s[ s0 ] = true;
    }
    assert(s.ok());
    for (const auto& c : sv)
    {
        decltype(s) next;
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s1, dfm::utils::simple_nfa_match_chars("#"));
        next |= dfm::utils::simple_nfa_delta(c, s, s1, s2, dfm::utils::simple_nfa_match_chars("$"));
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s2, nfa_match_hex_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s2, s4, nfa_match_hex_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s0, s3, dfm::utils::simple_nfa_match_chars("#"));
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s3, nfa_match_dec_chars);
        next |= dfm::utils::simple_nfa_delta(c, s, s3, s4, nfa_match_dec_chars);

        if (!next.ok())
        {
            return next;
        }
        s = next;
    }
    return s;
}

bool dfm::lexer::token_matcher_string_char::accept(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_string_char_run(sv);
    return s.accept();
}

bool dfm::lexer::token_matcher_string_char::ok(const dfm::lexer::token_view_type& sv) const
{
    const auto s = token_matcher_string_char_run(sv);
    return s.ok();
}

// #############################################################################
bool dfm::lexer::token_matcher_composition::accept(const dfm::lexer::token_view_type& sv) const
{
    for (const auto& ptr : m_automata)
    {
        if (ptr->accept(sv))
        {
            return true;
        }
    }
    return false;
}
bool dfm::lexer::token_matcher_composition::ok(const dfm::lexer::token_view_type& sv) const
{
    for (const auto& ptr : m_automata)
    {
        if (ptr->ok(sv))
        {
            return true;
        }
    }
    return false;
}
