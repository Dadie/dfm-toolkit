/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <algorithm>
#include <array>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>

// Own

namespace dfm::utils::form
{
    struct dfm_timage_header
    {
        uint8_t size {};
        std::string id {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void pp(std::ostream& out = std::cout) const;
        operator bool() const;

        auto operator<=>(const dfm_timage_header&) const = default;
    };

    template < size_t Size >
    struct dfm_generic_header
    {
        std::array< uint8_t, Size > __data {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void pp(std::ostream& out = std::cout) const;
        operator bool() const;

        auto operator<=>(const dfm_generic_header&) const = default;
    };

    template < size_t Size >
    struct dfm_generic_data
    {
        std::array< uint8_t, Size > __data {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void pp(std::ostream& out = std::cout) const;

        auto operator<=>(const dfm_generic_data&) const = default;
    };

    struct __attribute__((__packed__)) dfm_timagelist_header
    {
        char id[ 2 ] {};
        uint16_t unknown_0;
        uint16_t number_of_images;
        uint16_t unknown_2;
        uint16_t unknown_3;
        uint16_t image_width;
        uint16_t image_height;
        uint16_t unknown_4;
        uint16_t unknown_5;
        uint16_t unknown_6;
        uint16_t unknown_7;
        uint16_t unknown_8;
        uint16_t unknown_9;
        uint16_t unknown_a;

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void pp(std::ostream& out = std::cout) const;
        operator bool() const;

        auto operator<=>(const dfm_timagelist_header&) const = default;
    };
    static_assert(sizeof(dfm_timagelist_header) == 28, "Bad DFM Header Struct Size");

    struct __attribute__((__packed__)) dfm_timagelist_footer
    {
        uint16_t unknown_0;
        uint16_t unknown_1;
        uint16_t unknown_2;
        uint16_t unknown_3;
        uint16_t unknown_4;
        uint16_t unknown_5;
        uint16_t unknown_6;
        uint16_t unknown_7;
        uint16_t unknown_8;
        uint16_t unknown_9;
        uint16_t unknown_a;

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        operator bool() const;

        auto operator<=>(const dfm_timagelist_footer&) const = default;
    };
    static_assert(sizeof(dfm_timagelist_footer) == 22, "Bad DFM Footer Struct Size");

}

template < size_t Size >
size_t dfm::utils::form::dfm_generic_header< Size >::load(const uint8_t* p)
{
    std::copy(p, p + __data.size(), __data.begin());
    return __data.size();
}

template < size_t Size >
size_t dfm::utils::form::dfm_generic_header< Size >::save(uint8_t* p) const
{
    std::copy(__data.begin(), __data.end(), p);
    return __data.size();
}

template < size_t Size >
void dfm::utils::form::dfm_generic_header< Size >::pp(std::ostream& out) const
{
    for (size_t i = 0; i < __data.size(); ++i)
    {
        out << "generic_" << i << ": 0x" << std::hex << __data[ i ] << std::dec << std::endl;
    }
}

template < size_t Size >
dfm::utils::form::dfm_generic_header< Size >::operator bool() const
{
    for (const auto& b : __data)
    {
        if (b != 0)
        {
            return true;
        }
    }
    return false;
}

template < size_t Size >
size_t dfm::utils::form::dfm_generic_data< Size >::load(const uint8_t* p)
{
    std::copy(p, p + __data.size(), __data.begin());
    return __data.size();
}

template < size_t Size >
size_t dfm::utils::form::dfm_generic_data< Size >::save(uint8_t* p) const
{
    std::copy(__data.begin(), __data.end(), p);
    return __data.size();
}

template < size_t Size >
void dfm::utils::form::dfm_generic_data< Size >::pp(std::ostream& out) const
{
    for (size_t i = 0; i < __data.size(); ++i)
    {
        out << "generic_" << i << ": 0x" << std::hex << __data[ i ] << std::dec << std::endl;
    }
}
