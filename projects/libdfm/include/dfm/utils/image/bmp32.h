/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <cassert>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <variant>
#include <vector>

// Own
#include <dfm/utils/bits.h>

namespace dfm::utils::image
{
    struct __attribute__((__packed__)) bitmap_file_header
    {
        char id[ 2 ] {};
        uint32_t size {};
        uint16_t __reserved_0 {};
        uint16_t __reserved_1 {};
        uint32_t data_offset {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void pp(std::ostream& out = std::cout) const;

        auto operator<=>(const bitmap_file_header&) const = default;
    };
    static_assert(sizeof(bitmap_file_header) == 14, "Bad Struct Size");

    struct __attribute__((__packed__)) bitmap_core_header
    {
        uint32_t size {};
        uint16_t width {};
        uint16_t height {};
        uint16_t color_planes {};
        uint16_t bits_per_pixel {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void pp(std::ostream& out = std::cout) const;

        auto operator<=>(const bitmap_core_header&) const = default;
    };
    static_assert(sizeof(bitmap_core_header) == 12, "Bad Struct Size");

    struct __attribute__((__packed__)) bitmap_info_header
    {
        uint32_t size {};
        uint32_t width {};
        uint32_t height {};
        uint16_t color_planes {};
        uint16_t bits_per_pixel {};
        uint32_t compression {};
        uint32_t image_size {};
        uint32_t h_resolution {};
        uint32_t v_resolution {};
        uint32_t num_of_colors {};
        uint32_t num_of_important_colors {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void pp(std::ostream& out = std::cout) const;

        auto operator<=>(const bitmap_info_header&) const = default;
    };
    static_assert(sizeof(bitmap_info_header) == 40, "Bad Struct Size");

    struct __attribute__((__packed__)) bitmap_v4_header
    {
        uint32_t size {};
        uint32_t width {};
        uint32_t height {};
        uint16_t color_planes {};
        uint16_t bits_per_pixel {};
        uint32_t compression {};
        uint32_t image_size {};
        uint32_t h_resolution {};
        uint32_t v_resolution {};
        uint32_t num_of_colors {};
        uint32_t num_of_important_colors {};

        uint32_t r_bitmask {};
        uint32_t g_bitmask {};
        uint32_t b_bitmask {};
        uint32_t a_bitmask {};

        char color_space[ 4 ] {};
        char cie_xyz_triple[ 36 ] {};
        uint32_t r_gamma {};
        uint32_t g_gamma {};
        uint32_t b_gamma {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void pp(std::ostream& out = std::cout) const;
        bitmap_v4_header& operator=(const bitmap_core_header&);
        bitmap_v4_header& operator=(const bitmap_info_header&);

        auto operator<=>(const bitmap_v4_header&) const = default;
    };
    static_assert(sizeof(bitmap_v4_header) == 108, "Bad Struct Size");

    struct __attribute__((__packed__)) b1_pixel
    {
        bool value {};
        size_t position {};

        size_t load(const uint8_t* p, const size_t position = 0);
        size_t save(uint8_t* p, const size_t position = 0) const;

        auto operator<=>(const b1_pixel&) const = default;
    };

    struct __attribute__((__packed__)) b2_pixel
    {
        uint8_t idx {};
        size_t position {};

        size_t load(const uint8_t* p, const size_t position = 0);
        size_t save(uint8_t* p, const size_t position = 0) const;

        auto operator<=>(const b2_pixel&) const = default;
    };

    struct __attribute__((__packed__)) b4_pixel
    {
        uint8_t idx {};
        size_t position {};

        size_t load(const uint8_t* p, const size_t position = 0);
        size_t save(uint8_t* p, const size_t position = 0) const;

        auto operator<=>(const b4_pixel&) const = default;
    };

    struct __attribute__((__packed__)) b8_pixel
    {
        uint8_t idx {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const b8_pixel&) const = default;
    };

    struct __attribute__((__packed__)) b16_pixel
    {
        uint16_t b : 5 {};
        uint16_t g : 5 {};
        uint16_t r : 5 {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const b16_pixel&) const = default;
    };

    struct __attribute__((__packed__)) b24_pixel
    {
        uint8_t b {};
        uint8_t g {};
        uint8_t r {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const b24_pixel&) const = default;
    };

    struct __attribute__((__packed__)) b32_pixel
    {
        uint8_t b {};
        uint8_t g {};
        uint8_t r {};
        uint8_t a {};

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        b32_pixel& operator=(const b24_pixel&);
        b32_pixel& operator=(const b16_pixel&);

        auto operator<=>(const b32_pixel&) const = default;
    };

    template < typename PixelType >
    struct bmp_basic_pixel_array
    {
        private:
        uint32_t width {};
        uint32_t height {};
        std::vector< PixelType > pixel {};

        public:
        uint32_t w() const;
        uint32_t h() const;
        PixelType& get(const uint32_t x, const uint32_t y);
        const PixelType& get(const uint32_t x, const uint32_t y) const;
        void resize(const uint32_t width_, const uint32_t height_);

        auto operator<=>(const bmp_basic_pixel_array&) const = default;
    };

    struct bmp32_pixel_array : public bmp_basic_pixel_array< b32_pixel >
    {
        public:
        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const bmp32_pixel_array&) const = default;
    };

    struct bmp24_pixel_array : public bmp_basic_pixel_array< b24_pixel >
    {
        public:
        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const bmp24_pixel_array&) const = default;
    };

    struct bmp16_pixel_array : public bmp_basic_pixel_array< b16_pixel >
    {
        public:
        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const bmp16_pixel_array&) const = default;
    };

    struct bmp8_pixel_array : public bmp_basic_pixel_array< b8_pixel >
    {
        public:
        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const bmp8_pixel_array&) const = default;
    };

    struct bmp4_pixel_array : public bmp_basic_pixel_array< b4_pixel >
    {
        public:
        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const bmp4_pixel_array&) const = default;
    };

    struct bmp2_pixel_array : public bmp_basic_pixel_array< b2_pixel >
    {
        public:
        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const bmp2_pixel_array&) const = default;
    };

    struct bmp1_pixel_array : public bmp_basic_pixel_array< b1_pixel >
    {
        public:
        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const bmp1_pixel_array&) const = default;
    };

    template < typename DibHeaderType, typename PixelType, typename PixelArrayType >
    struct basic_bmp
    {
        using dib_type = DibHeaderType;
        using pixel_type = PixelType;
        using pixel_array_type = PixelArrayType;

        bitmap_file_header file_header;
        DibHeaderType dib_header;
        // TODO: Extra bit masks
        std::vector< b32_pixel > color_table;
        PixelArrayType pixel_array;

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;
        void resize(const uint32_t width, const uint32_t height);
        basic_bmp sub(
            const uint32_t offset_x, const uint32_t offset_y, const uint32_t width, const uint32_t height) const;
        std::vector< basic_bmp > split(const uint32_t width, const uint32_t height) const;

        auto operator<=>(const basic_bmp&) const = default;
    };

    template < typename DibHeaderType >
    struct bmp1 : public basic_bmp< DibHeaderType, b1_pixel, bmp1_pixel_array >
    {
        template < typename DibType >
        bmp1& operator=(const bmp1< DibType >& v)
        {
            this->file_header = v.file_header;
            this->dib_header = v.dib_header;
            this->color_table = v.color_table;
            this->pixel_array = v.pixel_array;
            return *this;
        }

        auto operator<=>(const bmp1&) const = default;
    };

    template < typename DibHeaderType >
    struct bmp2 : public basic_bmp< DibHeaderType, b2_pixel, bmp2_pixel_array >
    {
        auto operator<=>(const bmp2&) const = default;
    };

    template < typename DibHeaderType >
    struct bmp4 : public basic_bmp< DibHeaderType, b4_pixel, bmp4_pixel_array >
    {
        auto operator<=>(const bmp4&) const = default;
    };

    template < typename DibHeaderType >
    struct bmp8 : public basic_bmp< DibHeaderType, b8_pixel, bmp8_pixel_array >
    {
        auto operator<=>(const bmp8&) const = default;
    };

    template < typename DibHeaderType >
    struct bmp16 : public basic_bmp< DibHeaderType, b16_pixel, bmp16_pixel_array >
    {
        auto operator<=>(const bmp16&) const = default;
    };

    template < typename DibHeaderType >
    struct bmp24 : public basic_bmp< DibHeaderType, b24_pixel, bmp24_pixel_array >
    {
        auto operator<=>(const bmp24&) const = default;
    };

    template < typename DibHeaderType >
    struct bmp32 : public basic_bmp< DibHeaderType, b32_pixel, bmp32_pixel_array >
    {
        private:
        template < typename BmpType >
        b32_pixel get_pixel(const BmpType& v, const uint32_t x, const uint32_t y);
        template < typename DibType >
        b32_pixel get_pixel(const bmp1< DibType >& v, const uint32_t x, const uint32_t y);
        template < typename DibType >
        b32_pixel get_pixel(const bmp2< DibType >& v, const uint32_t x, const uint32_t y);
        template < typename DibType >
        b32_pixel get_pixel(const bmp4< DibType >& v, const uint32_t x, const uint32_t y);
        template < typename DibType >
        b32_pixel get_pixel(const bmp8< DibType >& v, const uint32_t x, const uint32_t y);

        public:
        template < typename BmpType >
        bmp32& operator=(const BmpType& v);

        auto operator<=>(const bmp32&) const = default;
    };

    struct bmp
    {
        private:
        std::variant< std::monostate, // Empty

            bmp32< bitmap_info_header >, // RGBA BMP
            bmp24< bitmap_info_header >, // RGB BMP
            bmp16< bitmap_info_header >, // RGB BMP
            bmp8< bitmap_info_header >,  // 256 Color BMP
            bmp4< bitmap_info_header >,  // 128 Color BMP
            bmp2< bitmap_info_header >,  // 16 Color BMP
            bmp1< bitmap_info_header >,  // B/W BMP

            bmp24< bitmap_core_header >, // RGB BMP
            bmp8< bitmap_core_header >,  // 256 Color BMP
            bmp4< bitmap_core_header >,  // 128 Color BMP
            bmp1< bitmap_core_header >   // B/W BMP
            >
            __bmp;

        public:
        template < typename T >
        T& get()
        {
            return std::get< T >(__bmp);
        }
        template < typename T >
        const T& get() const
        {
            return std::get< T >(__bmp);
        }

        template < typename T >
        bool has() const
        {
            return std::holds_alternative< T >(__bmp);
        }

        inline operator bool() const
        {
            return !std::holds_alternative< std::monostate >(__bmp);
        }

        size_t load(const uint8_t* p);
        size_t save(uint8_t* p) const;

        auto operator<=>(const bmp&) const = default;
    };

    enum class bitmap_compression_methods : uint32_t
    {
        BI_RGB = 0,
        BI_RLE8 = 1,
        BI_RLE4 = 2,
        BI_BITFIELDS = 3,
        BI_JPEG = 4,
        BI_PNG = 5,
        BI_ALPHABITFIELDS = 6,
        BI_CMYK = 11,
        BI_CMYKRLE8 = 12,
        BI_CMYKRLE4 = 13,
    };

    enum class bitmap_dib_type : size_t
    {
        BITMAPCOREHEADER = 12,
        OS21XBITMAPHEADER = 12,
        BITMAPINFOHEADER = 40,
        BITMAPV2INFOHEADER = 52,
        BITMAPV3INFOHEADER = 56,
        OS22XBITMAPHEADER = 64,
        BITMAPV4HEADER = 108,
        BITMAPV5HEADER = 124,
    };

    struct bitmap_analyse
    {
        bool found_file_header {};
        bool found_dib {};
        uint32_t width {};
        uint32_t height {};
        uint16_t bits_per_pixel {};
        bitmap_compression_methods compression {};
        bitmap_dib_type dib {};

        auto operator<=>(const bitmap_analyse&) const = default;
    };

    bitmap_analyse analyse(const uint8_t* p);
}

template < typename PixelType >
uint32_t dfm::utils::image::bmp_basic_pixel_array< PixelType >::w() const
{
    return width;
}

template < typename PixelType >
uint32_t dfm::utils::image::bmp_basic_pixel_array< PixelType >::h() const
{
    return height;
}

template < typename PixelType >
PixelType& dfm::utils::image::bmp_basic_pixel_array< PixelType >::get(const uint32_t x, const uint32_t y)
{
    const size_t row = height - y - 1;
    return pixel[ (row * width) + x ];
}

template < typename PixelType >
const PixelType& dfm::utils::image::bmp_basic_pixel_array< PixelType >::get(const uint32_t x, const uint32_t y) const
{
    const size_t row = height - y - 1;
    return pixel[ (row * width) + x ];
}

template < typename PixelType >
void dfm::utils::image::bmp_basic_pixel_array< PixelType >::resize(const uint32_t width_, const uint32_t height_)
{
    width = width_;
    height = height_;
    pixel.resize(width * height);
}

template < typename DibHeaderType, typename PixelType, typename PixelArrayType >
size_t dfm::utils::image::basic_bmp< DibHeaderType, PixelType, PixelArrayType >::load(const uint8_t* p)
{
    assert(p != nullptr);
    size_t s = 0;
    {
        s += file_header.load(p + s);
        s += dib_header.load(p + s);

        while (s + 4 <= file_header.data_offset)
        {
            color_table.push_back({});
            s += color_table.back().load(p + s);
        }

        // Gap between color table and pixel array
        assert(s <= file_header.data_offset);
        if (s != file_header.data_offset)
        {
            s = file_header.data_offset;
        }

        // Pixel array allocation
        pixel_array.resize(dib_header.width, dib_header.height);

        s += pixel_array.load(p + s);
    }
    return s;
}

template < typename DibHeaderType, typename PixelType, typename PixelArrayType >
size_t dfm::utils::image::basic_bmp< DibHeaderType, PixelType, PixelArrayType >::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += file_header.save((p == nullptr ? p : (p + s)));
        s += dib_header.save((p == nullptr ? p : (p + s)));
        for (const auto& e : color_table)
        {
            s += e.save((p == nullptr ? p : (p + s)));
        }
        assert(s <= file_header.data_offset);
        s += dfm::utils::bits::pad2p(file_header.data_offset - s, (p == nullptr ? p : (p + s)));
        s += pixel_array.save((p == nullptr ? p : (p + s)));
    }
    return s;
}

template < typename DibHeaderType, typename PixelType, typename PixelArrayType >
void dfm::utils::image::basic_bmp< DibHeaderType, PixelType, PixelArrayType >::resize(
    const uint32_t width, const uint32_t height)
{
    dib_header.width = width;
    dib_header.height = height;
    pixel_array.resize(width, height);
    dib_header.image_size = this->pixel_array.save(nullptr);
}

template < typename DibHeaderType, typename PixelType, typename PixelArrayType >
dfm::utils::image::basic_bmp< DibHeaderType, PixelType, PixelArrayType > dfm::utils::image::
    basic_bmp< DibHeaderType, PixelType, PixelArrayType >::sub(
        const uint32_t offset_x, const uint32_t offset_y, const uint32_t width, const uint32_t height) const
{
    auto cp = *this;
    cp.resize(width, height);
    for (uint32_t x = 0; x < width; ++x)
    {
        for (uint32_t y = 0; y < height; ++y)
        {
            if (((x + offset_x) < dib_header.width) && ((y + offset_y) < dib_header.height))
            {
                cp.pixel_array.get(x, y) = this->pixel_array.get(x + offset_x, y + offset_y);
            }
        }
    }
    return cp;
}

template < typename DibHeaderType, typename PixelType, typename PixelArrayType >
std::vector< dfm::utils::image::basic_bmp< DibHeaderType, PixelType, PixelArrayType > > dfm::utils::image::
    basic_bmp< DibHeaderType, PixelType, PixelArrayType >::split(const uint32_t width, const uint32_t height) const
{
    std::vector< dfm::utils::image::basic_bmp< DibHeaderType, PixelType, PixelArrayType > > images;
    {
        const size_t rows = (dib_header.height / height);
        const size_t cols = (dib_header.width / width);
        for (size_t row = 0; row < rows; ++row)
        {
            for (size_t col = 0; col < cols; ++col)
            {
                images.push_back(sub(col * width, row * height, width, height));
            }
        }
    }
    return images;
}

template < typename DibHeaderType >
template < typename BmpType >
dfm::utils::image::b32_pixel dfm::utils::image::bmp32< DibHeaderType >::get_pixel(
    const BmpType& v, const uint32_t x, const uint32_t y)
{
    b32_pixel cl;
    cl = v.pixel_array.get(x, y);
    return cl;
}

template < typename DibHeaderType >
template < typename DibType >
dfm::utils::image::b32_pixel dfm::utils::image::bmp32< DibHeaderType >::get_pixel(
    const dfm::utils::image::bmp1< DibType >& v, const uint32_t x, const uint32_t y)
{
    const auto clwhite = b32_pixel { .b = 0xff, .g = 0xff, .r = 0xff, .a = 0xff };
    const auto clblack = b32_pixel { .b = 0x00, .g = 0x00, .r = 0x00, .a = 0x00 };
    if (v.pixel_array.get(x, y).value)
    {
        return clwhite;
    }
    return clblack;
}

template < typename DibHeaderType >
template < typename DibType >
dfm::utils::image::b32_pixel dfm::utils::image::bmp32< DibHeaderType >::get_pixel(
    const dfm::utils::image::bmp2< DibType >& v, const uint32_t x, const uint32_t y)
{
    b32_pixel cl;
    cl = v.color_table[ v.pixel_array.get(x, y).idx ];
    return cl;
}

template < typename DibHeaderType >
template < typename DibType >
dfm::utils::image::b32_pixel dfm::utils::image::bmp32< DibHeaderType >::get_pixel(
    const dfm::utils::image::bmp4< DibType >& v, const uint32_t x, const uint32_t y)
{
    b32_pixel cl;
    cl = v.color_table[ v.pixel_array.get(x, y).idx ];
    return cl;
}

template < typename DibHeaderType >
template < typename DibType >
dfm::utils::image::b32_pixel dfm::utils::image::bmp32< DibHeaderType >::get_pixel(
    const dfm::utils::image::bmp8< DibType >& v, const uint32_t x, const uint32_t y)
{
    dfm::utils::image::b32_pixel cl;
    cl = v.color_table[ v.pixel_array.get(x, y).idx ];
    return cl;
}

template < typename DibHeaderType >
template < typename BmpType >
dfm::utils::image::bmp32< DibHeaderType >& dfm::utils::image::bmp32< DibHeaderType >::operator=(const BmpType& v)
{
    this->pixel_array.resize(v.dib_header.width, v.dib_header.height);
    for (uint32_t x = 0; x < v.dib_header.width; ++x)
    {
        for (uint32_t y = 0; y < v.dib_header.height; ++y)
        {
            const auto px = get_pixel(v, x, y);
            this->pixel_array.get(x, y) = px;
        }
    }

    this->dib_header = v.dib_header;
    this->dib_header.bits_per_pixel = 32;
    this->dib_header.image_size = this->pixel_array.save(nullptr);

    this->file_header.id[ 0 ] = 'B';
    this->file_header.id[ 1 ] = 'M';
    this->file_header.data_offset = this->file_header.save(nullptr) + this->dib_header.save(nullptr);

    this->file_header.size = this->save(nullptr);

    return *this;
}
