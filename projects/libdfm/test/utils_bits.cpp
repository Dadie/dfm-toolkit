/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <tuple>
#include <vector>

// Own
#include <dfm/utils/bits.h>

template < typename ValueType, size_t N >
std::array< ValueType, N > gen_random_array()
{
    std::random_device rd;
    std::default_random_engine re(rd());
    auto dist = std::uniform_int_distribution< ValueType >(
        std::numeric_limits< ValueType >::min(), std::numeric_limits< ValueType >::max());
    std::array< ValueType, N > values;
    for (auto& value : values)
    {
        value = dist(re);
    }
    return values;
}

int utils_bits(int argc, char** argv)
{
    constexpr size_t N = 1024;

    const auto u32_in_values = gen_random_array< uint32_t, N >();
    const auto u16_in_values = gen_random_array< uint16_t, N >();
    const auto u8_in_values = gen_random_array< uint8_t, N >();
    const auto i8_in_values = gen_random_array< char, N >();

    std::array< uint32_t, N > u32_out_values;
    std::array< uint16_t, N > u16_out_values;
    std::array< uint8_t, N > u8_out_values;
    std::array< char, N > i8_out_values;

    for (size_t i = 0; i < N; ++i)
    {
        // Read without size calls
        char i8v = dfm::utils::bits::p2i8(reinterpret_cast< const uint8_t* >(i8_in_values.data() + i));
        if (i8v != i8_in_values[ i ])
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }

        uint8_t u8v = dfm::utils::bits::p2u8(u8_in_values.data() + i);
        if (u8v != u8_in_values[ i ])
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }

        uint16_t u16v = dfm::utils::bits::p2u16(reinterpret_cast< const uint8_t* >(u16_in_values.data() + i));
        if (u16v != u16_in_values[ i ])
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }

        uint32_t u32v = dfm::utils::bits::p2u32(reinterpret_cast< const uint8_t* >(u32_in_values.data() + i));
        if (u32v != u32_in_values[ i ])
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }

        // Read with size calls
        size_t s = 0;
        char i8v2 = dfm::utils::bits::p2i8(reinterpret_cast< const uint8_t* >(i8_in_values.data() + i), s);
        if (i8v2 != i8_in_values[ i ] || s != 1)
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }
        s = 0;

        uint8_t u8v2 = dfm::utils::bits::p2u8(u8_in_values.data() + i, s);
        if (u8v2 != u8_in_values[ i ] || s != 1)
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }
        s = 0;

        uint16_t u16v2 = dfm::utils::bits::p2u16(reinterpret_cast< const uint8_t* >(u16_in_values.data() + i), s);
        if (u16v2 != u16_in_values[ i ] || s != 2)
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }
        s = 0;

        uint32_t u32v2 = dfm::utils::bits::p2u32(reinterpret_cast< const uint8_t* >(u32_in_values.data() + i), s);
        if (u32v2 != u32_in_values[ i ] || s != 4)
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }
        s = 0;

        // Write calls
        s = dfm::utils::bits::i8w2p(i8v, reinterpret_cast< uint8_t* >(i8_out_values.data() + i));
        if (i8_out_values[ i ] != i8v || s != 1)
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }
        s = 0;

        s = dfm::utils::bits::u8w2p(u8v, reinterpret_cast< uint8_t* >(u8_out_values.data() + i));
        if (u8_out_values[ i ] != u8v || s != 1)
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }
        s = 0;

        s = dfm::utils::bits::u16w2p(u16v, reinterpret_cast< uint8_t* >(u16_out_values.data() + i));
        if (u16_out_values[ i ] != u16v || s != 2)
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }
        s = 0;

        s = dfm::utils::bits::u32w2p(u32v, reinterpret_cast< uint8_t* >(u32_out_values.data() + i));
        if (u32_out_values[ i ] != u32v || s != 4)
        {
            std::cout << "Fail in " << __FILE__ << ":" << __LINE__ << std::endl;
            return EXIT_FAILURE;
        }
        s = 0;
    }
    return EXIT_SUCCESS;
}
