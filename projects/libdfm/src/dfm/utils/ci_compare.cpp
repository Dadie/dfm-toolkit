/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <algorithm>
#include <cctype>
#include <string>

// Own
#include <dfm/utils/ci_compare.h>

namespace dfm::utils
{
    int ci_compare(const std::string& str1, const std::string& str2)
    {
        const size_t str1_size = str1.size();
        const size_t str2_size = str2.size();
        const size_t n = std::min(str1_size, str2_size);
        for (size_t i = 0; i < n; ++i)
        {
            if (str1[ i ] == str2[ i ])
            {
                continue;
            }
            const auto c1 = std::toupper(static_cast< unsigned char >(str1[ i ]));
            const auto c2 = std::toupper(static_cast< unsigned char >(str2[ i ]));
            if (c1 < c2)
            {
                return -1;
            }
            if (c1 > c2)
            {
                return 1;
            }
        }
        if (str1_size > str2_size)
        {
            return -1;
        }
        if (str1_size < str2_size)
        {
            return -1;
        }
        return 0;
    }
}
