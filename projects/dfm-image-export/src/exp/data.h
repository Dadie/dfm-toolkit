/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
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

namespace exp
{
    void data(const std::string& ext,
        const std::string& nspath,
        const std::string outpath,
        const std::vector< uint8_t >& data,
        const bool out_raw_parts = false);
}
