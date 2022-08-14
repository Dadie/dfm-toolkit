/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
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
#include <exp/data.h>

void exp::data(const std::string& ext,
    const std::string& nspath,
    const std::string outpath,
    const std::vector< uint8_t >& data,
    const bool out_raw_parts)
{
    // Make sure the out path exists
    std::filesystem::create_directories(outpath);

    // Sanitize nspath
    const auto filename_prefix = dfm::utils::io::sanitize_filename(nspath);

    // Part, Raw, Icons, BMP Path Prefix
    const std::string prefix = outpath + "/" + filename_prefix;

    // Data position
    auto* p = data.data();

    // Full Raw
    if (out_raw_parts)
    {
        dfm::utils::io::save_to_file(p, p + data.size(), prefix + ".raw");
    }
    dfm::utils::io::save_to_file(p, p + data.size(), prefix + "." + ext);
}
