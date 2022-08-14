/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cstdint>
#include <string>

// Own

namespace dfm::utils::iconv
{
    std::u16string u8_to_u16le(const std::string& str);
    std::u16string u8_to_u16be(const std::string& str);

    std::string u16le_to_u8(const std::u16string& str);
    std::string u16be_to_u8(const std::u16string& str);

    std::string u16be_to_u8(const char* s, const size_t len);
    std::string u16le_to_u8(const char* s, const size_t len);
    std::string u32be_to_u8(const char* s, const size_t len);
    std::string u32le_to_u8(const char* s, const size_t len);
}
