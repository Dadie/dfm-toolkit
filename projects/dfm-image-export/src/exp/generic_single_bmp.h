/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// libdfm
#include <dfm/utils/form/envelope.h>
#include <dfm/utils/image/bmp32.h>
#include <dfm/utils/io.h>

// Own

namespace exp
{
    template < typename HeaderType >
    static void generic_single_bmp(const std::string& nspath,
        const std::string& outpath,
        const std::vector< uint8_t >& data,
        const bool out_raw_parts = false)
    {
        if (data.size() < sizeof(HeaderType))
        {
            std::cout << "Info: Given data (size:" << data.size()
                      << ") is probably too small to hold the given header type (sizeof:" << sizeof(HeaderType) << ")"
                      << std::endl;
            return;
        }

        if (std::find_if_not(data.begin(), data.end(), [](auto a) { return a == 0; }) == data.end())
        {
            // data is full of zeros.
            std::cout << "Info: Given data (size:" << data.size() << ") only contains zeros" << std::endl;
            return;
        }

        // Make sure the out path exists
        std::filesystem::create_directories(outpath);

        // Sanitize nspath
        const auto filename_prefix = dfm::utils::io::sanitize_filename(nspath);

        // Part, Raw, Icons, BMP Path Prefix
        const std::string prefix = outpath + "/" + filename_prefix;

        // Data position
        size_t s = 0;
        auto* p = data.data();

        // Full Raw
        if (out_raw_parts)
        {
            dfm::utils::io::save_to_file(p, p + data.size(), prefix + ".raw");
        }

        // Load/Save Part 0 : Generic Header
        HeaderType p0_header;
        const auto start_p0 = s;
        s += p0_header.load(p + s);
        if (out_raw_parts)
        {
            dfm::utils::io::save_to_file(p + start_p0, p + s, prefix + ".raw.p0");
        }

        // Load/Save Part 1 : Bitmap (Picture)
        if (p0_header)
        {
            dfm::utils::image::bmp p1_bmp;
            const auto start_p1 = s;
            s += p1_bmp.load(p + s);
            if (out_raw_parts)
            {
                dfm::utils::io::save_to_file(p + start_p1, p + s, prefix + ".raw.p1");
            }
            dfm::utils::io::save_to_file(p1_bmp, prefix + ".bmp");
        }
        else
        {
            assert(s <= data.size());
            // invalid TImage header
            std::cout << "Info: Invalid header" << std::endl;
            if (out_raw_parts)
            {
                dfm::utils::io::save_to_file(p + s, p + data.size(), prefix + ".raw.p1");
            }
            s = data.size();
        }

        assert(s == data.size());
    }
}
