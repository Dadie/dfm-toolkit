/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>

// Own
#include <dfm/utils/bits.h>

char dfm::utils::bits::p2i8(const uint8_t* p)
{
    assert(p != nullptr);
    return static_cast< char >(p[ 0 ]);
}

char dfm::utils::bits::p2i8(const uint8_t* p, size_t& s)
{
    s += 1;
    if (p == nullptr)
    {
        return {};
    }
    return dfm::utils::bits::p2i8(p);
}

uint8_t dfm::utils::bits::p2u8(const uint8_t* p)
{
    assert(p != nullptr);
    return p[ 0 ];
}

uint8_t dfm::utils::bits::p2u8(const uint8_t* p, size_t& s)
{
    s += 1;
    if (p == nullptr)
    {
        return {};
    }
    return dfm::utils::bits::p2u8(p);
}

uint16_t dfm::utils::bits::p2u16(const uint8_t* p)
{
    assert(p != nullptr);
    return (p[ 0 ] << 0) | (p[ 1 ] << 8);
}

uint16_t dfm::utils::bits::p2u16(const uint8_t* p, size_t& s)
{
    s += 2;
    if (p == nullptr)
    {
        return {};
    }
    return dfm::utils::bits::p2u16(p);
}

uint32_t dfm::utils::bits::p2u32(const uint8_t* p)
{
    assert(p != nullptr);
    return (p[ 0 ] << 0) | (p[ 1 ] << 8) | (p[ 2 ] << 16) | (p[ 3 ] << 24);
}

uint32_t dfm::utils::bits::p2u32(const uint8_t* p, size_t& s)
{
    s += 4;
    if (p == nullptr)
    {
        return {};
    }
    return dfm::utils::bits::p2u32(p);
}

size_t dfm::utils::bits::i8w2p(const char v, uint8_t* p)
{
    if (p != nullptr)
    {
        p[ 0 ] = static_cast< uint8_t >(v);
    }
    return 1;
}

size_t dfm::utils::bits::u8w2p(const uint8_t v, uint8_t* p)
{
    if (p != nullptr)
    {
        p[ 0 ] = v;
    }
    return 1;
}

size_t dfm::utils::bits::u16w2p(const uint16_t v, uint8_t* p)
{
    if (p != nullptr)
    {
        p[ 0 ] = static_cast< uint8_t >(0xff & (v >> 0));
        p[ 1 ] = static_cast< uint8_t >(0xff & (v >> 8));
    }
    return 2;
}

size_t dfm::utils::bits::u32w2p(const uint32_t v, uint8_t* p)
{
    if (p != nullptr)
    {
        p[ 0 ] = static_cast< uint8_t >(0xff & (v >> 0));
        p[ 1 ] = static_cast< uint8_t >(0xff & (v >> 8));
        p[ 2 ] = static_cast< uint8_t >(0xff & (v >> 16));
        p[ 3 ] = static_cast< uint8_t >(0xff & (v >> 24));
    }
    return 4;
}

size_t dfm::utils::bits::pad2p(const size_t n, uint8_t* p, const uint8_t pad_v)
{
    if (p != nullptr)
    {
        std::fill(p, p + n, pad_v);
    }
    return n;
}
