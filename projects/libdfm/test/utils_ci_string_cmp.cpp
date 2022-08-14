/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cstdlib>
#include <tuple>
#include <vector>

// Own
#include <dfm/utils/ci_string.h>

int utils_ci_string_cmp(int argc, char** argv)
{
    const std::vector< std::tuple< dfm::utils::ci_string, dfm::utils::ci_string, int > > values {
        { "true", "true", 0 },
        { "TRUE", "true", 0 },
        { "true", "TRUE", 0 },
        { "True", "true", 0 },
        { "true", "True", 0 },
        { "tRuE", "true", 0 },
        { "true", "tRuE", 0 },
        { "TRue", "true", 0 },
        { "TRUE", "TRue", 0 },
        { "true", "TRue", 0 },
        { "tRuE", "TrUE", 0 },
        { "TrUE", "tRuE", 0 },
        { "TRue", "TrUE", 0 },
        { "TRUE", "tRUE", 0 },
        { "true", "tRUE", 0 },
        { "tRUE", "TRue", 0 },
        { "tRuE", "tRUE", 0 },
        { "TrUE", "tRUE", 0 },
        { "a", "A", 0 },
        { "a", "B", -1 },
        { "A", "B", -1 },
        { "a", "b", -1 },
        { "A", "b", -1 },
        { "B", "A", 1 },
        { "B", "a", 1 },
        { "b", "A", 1 },
        { "b", "a", 1 },
        { "9", "9", 0 },
        { "0", "9", -1 },
        { "9", "0", 1 },
        { "=", "=", 0 },
        { "!", "!", 0 },
        { "a", "Z", -1 },
        { "a", "z", -1 },
        { "A", "Z", -1 },
        { "A", "z", -1 },
    };
    for (const auto& [ lhs, rhs, cmp_result ] : values)
    {
        if (cmp_result < 0)
        {
            if (!(lhs < rhs))
            {
                return EXIT_FAILURE;
            }
            if (!(lhs.compare(rhs) < 0))
            {
                return EXIT_FAILURE;
            }
        }
        else if (cmp_result == 0)
        {
            if (!(lhs == rhs))
            {
                return EXIT_FAILURE;
            }
            if (!(lhs.compare(rhs) == 0))
            {
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (!(lhs > rhs))
            {
                return EXIT_FAILURE;
            }
            if (!(lhs.compare(rhs) > 0))
            {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}
