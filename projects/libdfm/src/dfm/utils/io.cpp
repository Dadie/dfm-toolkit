/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <string>

// POSIX

// Own
#include <dfm/utils/io.h>
#include <dfm/utils/replace.h>

std::string dfm::utils::io::sanitize_filename(const std::string& fname)
{
    auto out = fname;
    {
        using namespace std::string_literals;
        out = dfm::utils::replace_all(out, ":"s, "_"s);
        out = dfm::utils::replace_all(out, ";"s, "_"s);
        out = dfm::utils::replace_all(out, "?"s, "_"s);
        out = dfm::utils::replace_all(out, "@"s, "_"s);
        out = dfm::utils::replace_all(out, ","s, "_"s);
        out = dfm::utils::replace_all(out, "~"s, "_"s);
        out = dfm::utils::replace_all(out, "*"s, "_"s);
        out = dfm::utils::replace_all(out, "^"s, "_"s);
        out = dfm::utils::replace_all(out, "/"s, "_"s);
        out = dfm::utils::replace_all(out, "\\"s, "_"s);
        out = dfm::utils::replace_all(out, "\""s, "_"s);
        out = dfm::utils::replace_all(out, "'"s, "_"s);
        out = dfm::utils::replace_all(out, "#"s, "_"s);
    }
    return out;
}
