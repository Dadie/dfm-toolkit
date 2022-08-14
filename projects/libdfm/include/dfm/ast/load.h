/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <filesystem>

// Own
#include <dfm/ast/node_dfm.h>

namespace dfm::ast
{
    dfm::ast::node_dfm load(const std::filesystem::path& path);
}
