/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cstddef>
#include <cstdint>

// Own

namespace dfm::utils::bits
{
    char p2i8(const uint8_t* p);
    char p2i8(const uint8_t* p, size_t& s);
    uint8_t p2u8(const uint8_t* p);
    uint8_t p2u8(const uint8_t* p, size_t& s);
    uint16_t p2u16(const uint8_t* p);
    uint16_t p2u16(const uint8_t* p, size_t& s);
    uint32_t p2u32(const uint8_t* p);
    uint32_t p2u32(const uint8_t* p, size_t& s);

    size_t i8w2p(const char v, uint8_t* p);
    size_t u8w2p(const uint8_t v, uint8_t* p);
    size_t u16w2p(const uint16_t v, uint8_t* p);
    size_t u32w2p(const uint32_t v, uint8_t* p);

    size_t pad2p(const size_t n, uint8_t* p, const uint8_t pad_v = 0);
}
