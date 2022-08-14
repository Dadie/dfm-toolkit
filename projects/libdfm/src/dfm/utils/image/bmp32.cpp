/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

// Own
#include <dfm/utils/bits.h>
#include <dfm/utils/debug.h>
#include <dfm/utils/image/bmp32.h>

size_t dfm::utils::image::bmp::load(const uint8_t* p)
{
    assert(p != nullptr);
    const auto support_bpp = [](const uint16_t bpp)
    {
        const std::vector< uint16_t > supported_bits_per_pixel {
            1,
            2,
            4,
            8,
            16,
            24,
            32,
        };
        return std::find(supported_bits_per_pixel.begin(), supported_bits_per_pixel.end(), bpp) !=
               supported_bits_per_pixel.end();
    };
    const auto support_dib = [](const dfm::utils::image::bitmap_dib_type dib)
    {
        const std::vector< dfm::utils::image::bitmap_dib_type > supported_dibs {
            dfm::utils::image::bitmap_dib_type::BITMAPINFOHEADER,
        };
        return std::find(supported_dibs.begin(), supported_dibs.end(), dib) != supported_dibs.end();
    };

    const auto analysis = dfm::utils::image::analyse(p);
    if (!support_dib(analysis.dib))
    {
        throw std::runtime_error(
            "Unsupported DIB (" + std::to_string(static_cast< size_t >(analysis.dib)) + ") in bitmap");
    }

    if (!support_bpp(analysis.bits_per_pixel))
    {
        throw std::runtime_error(
            "Unsupported bits per pixel (" + std::to_string(analysis.bits_per_pixel) + ") in bitmap");
    }

    size_t s = 0;
    switch (analysis.dib)
    {
        case dfm::utils::image::bitmap_dib_type::BITMAPINFOHEADER:
            switch (analysis.bits_per_pixel)
            {
                case 1:
                {
                    bmp1< bitmap_info_header > bmp_;
                    s += bmp_.load((p == nullptr ? p : (p + s)));
                    __bmp = bmp_;
                }
                break;
                case 2:
                {
                    bmp2< bitmap_info_header > bmp_;
                    s += bmp_.load((p == nullptr ? p : (p + s)));
                    __bmp = bmp_;
                }
                break;
                case 4:
                {
                    bmp4< bitmap_info_header > bmp_;
                    s += bmp_.load((p == nullptr ? p : (p + s)));
                    __bmp = bmp_;
                }
                break;
                case 8:
                {
                    bmp8< bitmap_info_header > bmp_;
                    s += bmp_.load((p == nullptr ? p : (p + s)));
                    __bmp = bmp_;
                }
                break;
                case 16:
                {
                    bmp16< bitmap_info_header > bmp_;
                    s += bmp_.load((p == nullptr ? p : (p + s)));
                    __bmp = bmp_;
                }
                break;
                case 24:
                {
                    bmp24< bitmap_info_header > bmp_;
                    s += bmp_.load((p == nullptr ? p : (p + s)));
                    __bmp = bmp_;
                }
                break;
                case 32:
                {
                    bmp32< bitmap_info_header > bmp_;
                    s += bmp_.load((p == nullptr ? p : (p + s)));
                    __bmp = bmp_;
                }
                break;
                default:
                    throw std::runtime_error(
                        "Unsupported bits per pixel (" + std::to_string(analysis.bits_per_pixel) + ") in bitmap");
            }
            break;
        default:
            throw std::runtime_error(
                "Unsupported DIB (" + std::to_string(static_cast< size_t >(analysis.dib)) + ") in bitmap");
    }
    return s;
}

size_t dfm::utils::image::bmp::save(uint8_t* p) const
{
    if (has< bmp32< bitmap_info_header > >())
    {
        return get< bmp32< bitmap_info_header > >().save(p);
    }

    if (has< bmp24< bitmap_info_header > >())
    {
        return get< bmp24< bitmap_info_header > >().save(p);
    }

    if (has< bmp16< bitmap_info_header > >())
    {
        return get< bmp16< bitmap_info_header > >().save(p);
    }

    if (has< bmp8< bitmap_info_header > >())
    {
        return get< bmp8< bitmap_info_header > >().save(p);
    }

    if (has< bmp4< bitmap_info_header > >())
    {
        return get< bmp4< bitmap_info_header > >().save(p);
    }

    if (has< bmp2< bitmap_info_header > >())
    {
        return get< bmp2< bitmap_info_header > >().save(p);
    }

    if (has< bmp1< bitmap_info_header > >())
    {
        return get< bmp1< bitmap_info_header > >().save(p);
    }

    assert(false);
    return 0;
}

size_t dfm::utils::image::bmp32_pixel_array::load(const uint8_t* p)
{
    assert(p != nullptr);
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).load((p == nullptr ? p : (p + s)));
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += (4 - (s % 4)) % 4;
    }
    return s;
}

size_t dfm::utils::image::bmp32_pixel_array::save(uint8_t* p) const
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).save((p == nullptr ? p : (p + s)));
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += dfm::utils::bits::pad2p((4 - (s % 4)) % 4, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::bmp24_pixel_array::load(const uint8_t* p)
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).load((p == nullptr ? p : (p + s)));
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += (4 - (s % 4)) % 4;
    }
    return s;
}

size_t dfm::utils::image::bmp24_pixel_array::save(uint8_t* p) const
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).save((p == nullptr ? p : (p + s)));
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += dfm::utils::bits::pad2p((4 - (s % 4)) % 4, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::bmp16_pixel_array::load(const uint8_t* p)
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).load((p == nullptr ? p : (p + s)));
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += (4 - (s % 4)) % 4;
    }
    return s;
}

size_t dfm::utils::image::bmp16_pixel_array::save(uint8_t* p) const
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).save((p == nullptr ? p : (p + s)));
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += dfm::utils::bits::pad2p((4 - (s % 4)) % 4, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::bmp8_pixel_array::load(const uint8_t* p)
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).load((p == nullptr ? p : (p + s)));
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += (4 - (s % 4)) % 4;
    }
    return s;
}

size_t dfm::utils::image::bmp8_pixel_array::save(uint8_t* p) const
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).save((p == nullptr ? p : (p + s)));
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += dfm::utils::bits::pad2p((4 - (s % 4)) % 4, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::bmp4_pixel_array::load(const uint8_t* p)
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).load((p == nullptr ? p : (p + s)), x);
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += (4 - (s % 4)) % 4;
    }
    return s;
}

size_t dfm::utils::image::bmp4_pixel_array::save(uint8_t* p) const
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).save((p == nullptr ? p : (p + s)), x);
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += dfm::utils::bits::pad2p((4 - (s % 4)) % 4, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::bmp2_pixel_array::load(const uint8_t* p)
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).load((p == nullptr ? p : (p + s)), x);
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += (4 - (s % 4)) % 4;
    }
    return s;
}

size_t dfm::utils::image::bmp2_pixel_array::save(uint8_t* p) const
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).save((p == nullptr ? p : (p + s)), x);
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += dfm::utils::bits::pad2p((4 - (s % 4)) % 4, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::bmp1_pixel_array::load(const uint8_t* p)
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).load((p == nullptr ? p : (p + s)), x);
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += (4 - (s % 4)) % 4;
    }
    return s;
}

size_t dfm::utils::image::bmp1_pixel_array::save(uint8_t* p) const
{
    size_t s = 0;
    for (uint32_t row = h(); 0 < row; --row)
    {
        const uint32_t y = row - 1; // First row has y value of 0 etc.
        for (uint32_t x = 0; x < w(); ++x)
        {
            s += get(x, y).save((p == nullptr ? p : (p + s)), x);
        }
        // Padding (as a pixel rows have to start on a mult. of 4)
        s += dfm::utils::bits::pad2p((4 - (s % 4)) % 4, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::bitmap_file_header::load(const uint8_t* p)
{
    size_t s = 0;
    id[ 0 ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    id[ 1 ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    size = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    __reserved_0 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    __reserved_1 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    data_offset = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    assert(s == 14);
    return s;
}

size_t dfm::utils::image::bitmap_file_header::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::i8w2p(id[ 0 ], (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::i8w2p(id[ 1 ], (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(size, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(__reserved_0, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(__reserved_1, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(data_offset, (p == nullptr ? p : (p + s)));
    }
    return s;
}

void dfm::utils::image::bitmap_file_header::pp(std::ostream& out) const
{
    out << "id: " << id[ 0 ] << id[ 1 ] << std::endl;
    out << "size: " << size << std::endl;
    out << "__reserved_0: " << __reserved_0 << std::endl;
    out << "__reserved_1: " << __reserved_1 << std::endl;
    out << "data_offset: " << data_offset << std::endl;
}

size_t dfm::utils::image::bitmap_info_header::load(const uint8_t* p)
{
    size_t s = 0;
    size = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    width = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    height = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    color_planes = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    bits_per_pixel = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    compression = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    image_size = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    h_resolution = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    v_resolution = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    num_of_colors = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    num_of_important_colors = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    assert(s == 40);
    return s;
}

size_t dfm::utils::image::bitmap_info_header::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::u32w2p(size, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(width, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(height, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(color_planes, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(bits_per_pixel, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(compression, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(image_size, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(h_resolution, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(v_resolution, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(num_of_colors, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(num_of_important_colors, (p == nullptr ? p : (p + s)));
    }
    return s;
}

void dfm::utils::image::bitmap_info_header::pp(std::ostream& out) const
{
    out << "size: " << size << std::endl;
    out << "width: " << width << std::endl;
    out << "height: " << height << std::endl;
    out << "color_planes: " << color_planes << std::endl;
    out << "bits_per_pixel: " << bits_per_pixel << std::endl;
    out << "compression: " << compression << std::endl;
    out << "image_size: " << image_size << std::endl;
    out << "h_resolution: " << h_resolution << std::endl;
    out << "v_resolution: " << v_resolution << std::endl;
    out << "num_of_colors: " << num_of_colors << std::endl;
    out << "num_of_important_colors: " << num_of_important_colors << std::endl;
}

size_t dfm::utils::image::bitmap_v4_header::load(const uint8_t* p)
{
    size_t s = 0;
    size = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    width = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    height = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    color_planes = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    bits_per_pixel = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    compression = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    image_size = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    h_resolution = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    v_resolution = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    num_of_colors = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    num_of_important_colors = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);

    r_bitmask = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    g_bitmask = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    b_bitmask = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    a_bitmask = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);

    color_space[ 0 ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    color_space[ 1 ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    color_space[ 2 ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    color_space[ 3 ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);

    for (size_t i = 0; i < 36; ++i)
    {
        cie_xyz_triple[ i ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    }

    r_gamma = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    g_gamma = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    b_gamma = dfm::utils::bits::p2u32((p == nullptr ? p : (p + s)), s);
    assert(s == 108);
    return s;
}

size_t dfm::utils::image::bitmap_v4_header::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::u32w2p(size, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(width, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(height, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(color_planes, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(bits_per_pixel, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(compression, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(image_size, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(h_resolution, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(v_resolution, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(num_of_colors, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(num_of_important_colors, (p == nullptr ? p : (p + s)));

        s += dfm::utils::bits::u32w2p(r_bitmask, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(g_bitmask, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(b_bitmask, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(a_bitmask, (p == nullptr ? p : (p + s)));

        s += dfm::utils::bits::i8w2p(color_space[ 0 ], (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::i8w2p(color_space[ 1 ], (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::i8w2p(color_space[ 2 ], (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::i8w2p(color_space[ 3 ], (p == nullptr ? p : (p + s)));

        for (size_t i = 0; i < 36; ++i)
        {
            s += dfm::utils::bits::i8w2p(cie_xyz_triple[ i ], (p == nullptr ? p : (p + s)));
        }

        s += dfm::utils::bits::u32w2p(r_gamma, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(g_gamma, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u32w2p(b_gamma, (p == nullptr ? p : (p + s)));
    }
    assert(s == 108);
    return s;
}

void dfm::utils::image::bitmap_v4_header::pp(std::ostream& out) const
{
    out << "size: " << size << std::endl;
    out << "width: " << width << std::endl;
    out << "height: " << height << std::endl;
    out << "color_planes: " << color_planes << std::endl;
    out << "bits_per_pixel: " << bits_per_pixel << std::endl;
    out << "compression: " << compression << std::endl;
    out << "image_size: " << image_size << std::endl;
    out << "h_resolution: " << h_resolution << std::endl;
    out << "v_resolution: " << v_resolution << std::endl;
    out << "num_of_colors: " << num_of_colors << std::endl;
    out << "num_of_important_colors: " << num_of_important_colors << std::endl;
    out << "r_bitmask: " << std::hex << r_bitmask << std::dec << std::endl;
    out << "g_bitmask: " << std::hex << g_bitmask << std::dec << std::endl;
    out << "b_bitmask: " << std::hex << b_bitmask << std::dec << std::endl;
    out << "a_bitmask: " << std::hex << a_bitmask << std::dec << std::endl;
    out << "color_space: " << std::string(color_space, 4) << std::endl;
    out << "color_space[0]: " << color_space[ 0 ] << std::endl;
    out << "color_space[1]: " << color_space[ 1 ] << std::endl;
    out << "color_space[2]: " << color_space[ 2 ] << std::endl;
    out << "color_space[3]: " << color_space[ 3 ] << std::endl;

    out << "cie_xyz_triple: "
        << "..." << std::endl;
    out << "r_gamma: " << r_gamma << std::endl;
    out << "g_gamma: " << g_gamma << std::endl;
    out << "b_gamma: " << b_gamma << std::endl;
}

dfm::utils::image::bitmap_v4_header& dfm::utils::image::bitmap_v4_header::operator=(
    const dfm::utils::image::bitmap_info_header& h)
{
    size = 108;
    width = h.width;
    height = h.height;

    color_planes = h.color_planes;
    bits_per_pixel = h.bits_per_pixel;
    compression = static_cast< uint32_t >(dfm::utils::image::bitmap_compression_methods::BI_BITFIELDS);
    image_size = h.image_size;
    h_resolution = h.h_resolution;
    v_resolution = h.v_resolution;
    num_of_colors = h.num_of_colors;
    num_of_important_colors = h.num_of_important_colors;

    r_bitmask = 0x00ff0000;
    b_bitmask = 0x000000ff;
    g_bitmask = 0x0000ff00;
    a_bitmask = 0xff000000;

    color_space[ 1 ] = 'W';
    color_space[ 0 ] = 'i';
    color_space[ 3 ] = 'n';
    color_space[ 2 ] = ' ';

    for (size_t i = 0; i < 36; ++i)
    {
        cie_xyz_triple[ i ] = 0;
    }
    r_gamma = 0;
    g_gamma = 0;
    b_gamma = 0;

    return *this;
}

size_t dfm::utils::image::b32_pixel::load(const uint8_t* p)
{
    size_t s = 0;
    b = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    g = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    r = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    a = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    assert(s == 4);
    return s;
}

size_t dfm::utils::image::b32_pixel::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::u8w2p(b, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u8w2p(g, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u8w2p(r, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u8w2p(a, (p == nullptr ? p : (p + s)));
    }
    return s;
}

dfm::utils::image::b32_pixel& dfm::utils::image::b32_pixel::operator=(const dfm::utils::image::b24_pixel& p24)
{
    b = p24.b;
    g = p24.g;
    r = p24.r;
    a = 0x00;
    return *this;
}

dfm::utils::image::b32_pixel& dfm::utils::image::b32_pixel::operator=(const dfm::utils::image::b16_pixel& p16)
{
    b = p16.b << 3;
    g = p16.g << 3;
    r = p16.r << 3;
    a = 0x00;
    return *this;
}

size_t dfm::utils::image::b24_pixel::load(const uint8_t* p)
{
    size_t s = 0;
    b = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    g = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    r = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    assert(s == 3);
    return s;
}

size_t dfm::utils::image::b24_pixel::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::u8w2p(b, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u8w2p(g, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u8w2p(r, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::b16_pixel::load(const uint8_t* p)
{
    size_t s = 0;
    const auto __raw = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    r = (__raw >> 10) & 0x1f;
    g = (__raw >> 5) & 0x1f;
    b = (__raw >> 0) & 0x1f;
    assert(s == 2);
    return s;
}

size_t dfm::utils::image::b16_pixel::save(uint8_t* p) const
{
    size_t s = 0;
    {
        const uint16_t v = ((r & 0x1f) << 10) | ((g & 0x1f) << 5) | ((b & 0x1f) << 0);
        s += dfm::utils::bits::u16w2p(v, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::b8_pixel::load(const uint8_t* p)
{
    size_t s = 0;
    idx = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    assert(s == 1);
    return s;
}

size_t dfm::utils::image::b8_pixel::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::u8w2p(idx, (p == nullptr ? p : (p + s)));
    }
    return s;
}

size_t dfm::utils::image::b4_pixel::load(const uint8_t* p, const size_t position_)
{
    if (p != nullptr)
    {
        const uint8_t mask = 0xf << ((position_ % 2) * 4);
        idx = (mask & *p) >> ((position_ % 2) * 4);
    }
    position = position_;
    return (position_ % 2);
}

size_t dfm::utils::image::b4_pixel::save(uint8_t* p, const size_t position_) const
{
    if (p != nullptr)
    {
        const uint8_t mask = 0xf << ((position_ % 2) * 4);
        // Clear part
        *p &= ~mask;
        *p |= ((idx << ((position_ % 2) * 4)) & mask);
    }
    return (position_ % 2);
}

size_t dfm::utils::image::b2_pixel::load(const uint8_t* p, const size_t position_)
{
    if (p != nullptr)
    {
        const uint8_t mask = 0b11 << ((position_ % 4) * 2);
        idx = (mask & *p) >> ((position_ % 4) * 2);
    }
    position = position_;
    return (position_ % 4);
}

size_t dfm::utils::image::b2_pixel::save(uint8_t* p, const size_t position_) const
{
    if (p != nullptr)
    {
        const uint8_t mask = 0b11 << ((position_ % 4) * 2);
        // Clear part
        *p &= ~mask;
        *p |= ((idx << ((position_ % 4) * 2)) & mask);
    }
    return (position_ % 4);
}

size_t dfm::utils::image::b1_pixel::load(const uint8_t* p, const size_t position_)
{

    const uint8_t mask = (1 << (7 - (position_ % 8)));
    if (p != nullptr)
    {
        value = (mask & *p) == 0;
    }
    position = position_;
    if ((position_ % 8) == 7)
    {
        return 1;
    }
    return 0;
}

size_t dfm::utils::image::b1_pixel::save(uint8_t* p, const size_t position_) const
{
    if (p != nullptr)
    {
        const uint8_t mask = (1 << (7 - (position_ % 8)));
        if (value)
        {
            *p = (*p | mask);
        }
        else
        {
            *p = (*p & ~mask);
        }
    }
    if (position_ > 0 && (position_ % 8) == 7)
    {
        return 1;
    }
    return 0;
}

dfm::utils::image::bitmap_analyse dfm::utils::image::analyse(const uint8_t* p)
{
    dfm::utils::image::bitmap_analyse res;
    do
    {
        // Analyse Bitmap File Header
        dfm::utils::image::bitmap_file_header file_header;
        size_t s = 0;
        s += file_header.load((p == nullptr ? p : (p + s)));
        res.found_file_header = (file_header.id[ 0 ] == 'B' && file_header.id[ 1 ] == 'M');
        if (!res.found_file_header)
        {
            break;
        }

        res.dib =
            static_cast< dfm::utils::image::bitmap_dib_type >(dfm::utils::bits::p2u32((p == nullptr ? p : (p + s))));
        switch (res.dib)
        {
            case dfm::utils::image::bitmap_dib_type::BITMAPCOREHEADER:
            {
                // CURRENTLY NOT SUPPORTED
                assert(false);
            }
            break;

            case dfm::utils::image::bitmap_dib_type::BITMAPINFOHEADER:
            {
                dfm::utils::image::bitmap_info_header dib;
                s += dib.load((p == nullptr ? p : (p + s)));
                res.found_dib = true;
                res.width = dib.width;
                res.height = dib.height;
                res.bits_per_pixel = dib.bits_per_pixel;
                res.compression = static_cast< dfm::utils::image::bitmap_compression_methods >(dib.compression);
            }
            break;

            case dfm::utils::image::bitmap_dib_type::BITMAPV2INFOHEADER:
            {
                // CURRENTLY NOT SUPPORTED
                assert(false);
            }
            break;

            case dfm::utils::image::bitmap_dib_type::BITMAPV3INFOHEADER:
            {
                // CURRENTLY NOT SUPPORTED
                assert(false);
            }
            break;

            case dfm::utils::image::bitmap_dib_type::OS22XBITMAPHEADER:
            {
                // CURRENTLY NOT SUPPORTED
                assert(false);
            }
            break;

            case dfm::utils::image::bitmap_dib_type::BITMAPV4HEADER:
            {
                // CURRENTLY NOT SUPPORTED
                assert(false);
            }
            break;

            case dfm::utils::image::bitmap_dib_type::BITMAPV5HEADER:
            {
                // CURRENTLY NOT SUPPORTED
                assert(false);
            }
            break;

            default:
            {
                // UNKNOWN DIB
                assert(false);
            }
        }
    } while (false);
    return res;
}
