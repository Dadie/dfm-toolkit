/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// libdfm
#include <dfm/ast/node.h>
#include <dfm/ast/node_object.h>
#include <dfm/ast/node_value_binary.h>
#include <dfm/pt/node.h>
#include <dfm/utils/form/envelope.h>
#include <dfm/utils/image/bmp32.h>
#include <dfm/utils/io.h>
#include <dfm/utils/replace.h>

// Own
#include <exp/timage.h>

static const std::string g_unknown_file_extension = "ukn";
static const std::vector< std::tuple< std::string, std::vector< uint8_t > > > g_magic_numbers {
    { "png", { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a } },
    { "gif", { 0x47, 0x49, 0x46, 0x38, 0x37, 0x61 } },
    { "gif", { 0x47, 0x49, 0x46, 0x38, 0x39, 0x61 } },
    { "jpg", { 0xff, 0xd8, 0xff, 0xee } },
    { "jpg", { 0xff, 0xd8, 0xff, 0xe0 } },
    { "jpg", { 0xff, 0xd8, 0xff, 0xe1 } },
    { "jp2", { 0x00, 0x00, 0x00, 0x0c, 0x6a, 0x50, 0x20, 0x20, 0x0d, 0x0a, 0x87, 0x0a } },
    { "jp2", { 0xff, 0x4f, 0xff, 0x51 } },
    { "bmp", { 0x42, 0x4d } },
    { "wim", { 0x4d, 0x53, 0x57, 0x49, 0x4d } },
    { "tif", { 0x49, 0x49, 0x2a, 0x00 } },
    { "tif", { 0x4d, 0x4d, 0x00, 0x20 } },
    { "flif", { 0x46, 0x4c, 0x49, 0x46 } },
};

static std::tuple< std::string, size_t > deduct_file_extension(
    const uint8_t* p, const std::string& fallback_ext = g_unknown_file_extension)
{
    for (const auto& [ mn_ext, mn_v ] : g_magic_numbers)
    {
        if (std::equal(mn_v.cbegin(), mn_v.cend(), p))
        {
            return { mn_ext, 0 };
            break;
        }
        // Hotfix:
        // Found at least one example in which the first 4 bytes are not part
        // of the image but an offset for some meta data like an BMP file header.
        // TODO:
        // More examples are required
        if (std::equal(mn_v.cbegin(), mn_v.cend(), p + 4))
        {

            return { mn_ext, 4 };
            break;
        }
    }
    return { fallback_ext, 0 };
}

void exp::timage(const std::string& nspath, const std::string& outpath, const dfm::ast::node* node, const bool out_raw)
{
    const auto* node_obj = dynamic_cast< const dfm::ast::node_object* >(node);
    if (node_obj == nullptr)
    {
        throw std::invalid_argument("Expected dfm::ast::node_object but got something else");
    }

    if (!node_obj->p.has("Picture.Data"))
    {
        return;
    }

    // Make sure the out path exists
    std::filesystem::create_directories(outpath);

    const auto& data_field = node_obj->p[ "Picture.Data" ];
    const auto binary_node_ptr = std::dynamic_pointer_cast< dfm::ast::node_value_binary >(data_field.param_value);
    const auto& v = binary_node_ptr->value;

    if (std::find_if_not(v.begin(), v.end(), [](auto a) { return a == 0; }) == v.end())
    {
        // data is full of zeros.
        std::cout << "Info: Given data (size:" << v.size() << ") only contains zeros" << std::endl;
        return;
    }

    // Sanitize nspath
    const auto filename_prefix = dfm::utils::io::sanitize_filename(nspath);

    // Part, Raw, Icons, BMP Path Prefix
    const std::string prefix = outpath + "/" + filename_prefix;

    // Data position
    size_t s = 0;
    auto* p = v.data();

    // Full Raw
    if (out_raw)
    {
        dfm::utils::io::save_to_file(p, p + v.size(), prefix + ".raw");
    }

    // Load/Save Part 0 : DFM Header
    dfm::utils::form::dfm_timage_header p0_dfm;
    s += p0_dfm.load(p + s);
    if (out_raw)
    {
        dfm::utils::io::save_to_file(p0_dfm, prefix + ".raw.p0");
    }

    size_t s_end_p0 = s;
    size_t s_end_p1 = v.size();
    std::string file_extension = "ukn";

    // Process Part 1 using the TImage header information
    if (p0_dfm.id == "TdxPNGImage")
    {
        file_extension = "png";
    }
    else if (p0_dfm.id == "TBitmap")
    {
        // Dunno why, but TBitmap files have 4 additional bytes after the timage header
        // which is the size field of the bitmap file header.
        s += 4;
        file_extension = "bmp";
    }
    else if (p0_dfm.id == "TPngImage")
    {
        file_extension = "png";
    }
    else if (p0_dfm.id == "TPNGGraphic")
    {
        // Found at least one example online in which this field contains something else than a PNG file.
        const auto [ d_ext, s_offset ] = deduct_file_extension(p + s, "png");
        file_extension = d_ext;
        s += s_offset;
    }
    else if (p0_dfm.id == "TJPEGImage")
    {
        file_extension = "jpg";
    }
    else if (p0_dfm.id == "TIcon")
    {
        file_extension = "ico";
    }
    else if (p0_dfm.id == "TGIFImage")
    {
        file_extension = "gif";
    }
    else
    {
        std::cout << "Info: Found unknown image type '" << p0_dfm.id << "' in TImage header" << std::endl;
        // Unknown type, try to detect base on the magic number
        const auto [ d_ext, s_offset ] = deduct_file_extension(p + s);
        file_extension = d_ext;
        s += s_offset;
        std::cout << "Info: Assume file extension " << file_extension << std::endl;
    }

    assert(s_end_p0 <= s);
    assert(s < s_end_p1);
    assert(s_end_p1 <= v.size());
    if (out_raw)
    {
        dfm::utils::io::save_to_file(p + s, p + s_end_p1, prefix + ".raw.p1");
    }
    dfm::utils::io::save_to_file(p + s, p + s_end_p1, prefix + ".img." + file_extension);

    if (s_end_p1 < v.size())
    {
        std::cout << "Info: Found trailing bytes of unknown origin " << file_extension << std::endl;
        if (out_raw)
        {
            dfm::utils::io::save_to_file(p + s_end_p1, p + v.size(), prefix + ".raw.p2");
        }
    }
}
