/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

// libdfm
#include <dfm/utils/form/envelope.h>
#include <dfm/utils/image/bmp32.h>
#include <dfm/utils/io.h>

// Own

namespace exp
{
    void timage(const std::string& nspath, const std::string& outpath, const dfm::ast::node* node, const bool out_raw);
}
