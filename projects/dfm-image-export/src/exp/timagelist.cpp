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
#include <exp/timagelist.h>

void exp::timagelist(
    const std::string& nspath, const std::string& outpath, const dfm::ast::node* node, const bool out_raw)
{
    const auto* node_obj = dynamic_cast< const dfm::ast::node_object* >(node);
    if (node_obj == nullptr)
    {
        throw std::invalid_argument("Expected dfm::ast::node_object but got something else");
    }
    if (!node_obj->p.has("Bitmap"))
    {
        return;
    }

    // Make sure the out path exists
    std::filesystem::create_directories(outpath);

    const auto& bitmap_field = node_obj->p[ "Bitmap" ];
    const auto binary_node_ptr = std::dynamic_pointer_cast< dfm::ast::node_value_binary >(bitmap_field.param_value);
    const auto& v = binary_node_ptr->value;

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
    dfm::utils::form::dfm_timagelist_header p0_dfm;
    const size_t start_p0 = s;
    s += p0_dfm.load(p + s);
    if (out_raw)
    {
        dfm::utils::io::save_to_file(p + start_p0, p + s, prefix + ".raw.p0");
    }

    // Load/Save Part 1 : Bitmap (Picture)
    dfm::utils::image::bmp p1_bmp;
    const size_t start_p1 = s;
    s += p1_bmp.load(p + s);
    if (out_raw)
    {
        dfm::utils::io::save_to_file(p + start_p1, p + s, prefix + ".raw.p1");
    }

    // Load/Save Part 2 : Bitmap (Alpha)
    dfm::utils::image::bmp p2_bmp;
    const size_t start_p2 = s;
    s += p2_bmp.load(p + s);
    if (out_raw)
    {
        dfm::utils::io::save_to_file(p + start_p2, p + s, prefix + ".raw.p2");
    }

    // Load/Save Part 3 : Unknown
    dfm::utils::form::dfm_timagelist_footer p3_dfm;
    if (s < v.size())
    {
        const size_t start_p3 = s;
        s += p3_dfm.load(p + s);
        if (out_raw)
        {
            dfm::utils::io::save_to_file(p + start_p3, p + s, prefix + ".raw.p3");
        }
    }
    else
    {
        // For reason unknown sometimes the 3rd part is missing, in that case no trailing bytes after part 2 (alpha
        // channel) should be present
        assert(s == v.size());
    }

    // Build new BMP32 with color information from p1 and alpha information from p2
    dfm::utils::image::bmp32< dfm::utils::image::bitmap_v4_header > merge;
    {
        if (p1_bmp.has< dfm::utils::image::bmp32< dfm::utils::image::bitmap_info_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp32< dfm::utils::image::bitmap_info_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp24< dfm::utils::image::bitmap_info_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp24< dfm::utils::image::bitmap_info_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp16< dfm::utils::image::bitmap_info_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp16< dfm::utils::image::bitmap_info_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp8< dfm::utils::image::bitmap_info_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp8< dfm::utils::image::bitmap_info_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp4< dfm::utils::image::bitmap_info_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp4< dfm::utils::image::bitmap_info_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp2< dfm::utils::image::bitmap_info_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp2< dfm::utils::image::bitmap_info_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp1< dfm::utils::image::bitmap_info_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp1< dfm::utils::image::bitmap_info_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp24< dfm::utils::image::bitmap_core_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp24< dfm::utils::image::bitmap_core_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp8< dfm::utils::image::bitmap_core_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp8< dfm::utils::image::bitmap_core_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp4< dfm::utils::image::bitmap_core_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp4< dfm::utils::image::bitmap_core_header > >();
        }
        else if (p1_bmp.has< dfm::utils::image::bmp1< dfm::utils::image::bitmap_core_header > >())
        {
            merge = p1_bmp.get< dfm::utils::image::bmp1< dfm::utils::image::bitmap_core_header > >();
        }
        else
        {
            std::cout << "Unsupported in " << __FILE__ << ":" << __LINE__ << std::endl;
            assert(false);
        }

        dfm::utils::image::bmp1< dfm::utils::image::bitmap_v4_header > alpha_info;
        {
            if (p2_bmp.has< dfm::utils::image::bmp1< dfm::utils::image::bitmap_info_header > >())
            {
                alpha_info = p2_bmp.get< dfm::utils::image::bmp1< dfm::utils::image::bitmap_info_header > >();
            }
            else if (p2_bmp.has< dfm::utils::image::bmp1< dfm::utils::image::bitmap_core_header > >())
            {
                alpha_info = p2_bmp.get< dfm::utils::image::bmp1< dfm::utils::image::bitmap_core_header > >();
            }
            else
            {
                std::cout << "Unsupported in " << __FILE__ << ":" << __LINE__ << std::endl;
                assert(false);
            }
        }

        assert(alpha_info.dib_header.width == merge.dib_header.width);
        assert(alpha_info.dib_header.height == merge.dib_header.height);
        for (uint32_t x = 0; x < alpha_info.dib_header.width; ++x)
        {
            for (uint32_t y = 0; y < alpha_info.dib_header.height; ++y)
            {
                if (alpha_info.pixel_array.get(x, y).value)
                {
                    merge.pixel_array.get(x, y).a = 0xff;
                }
                else
                {
                    merge.pixel_array.get(x, y).a = 0x00;
                }
            }
        }
    }
    dfm::utils::io::save_to_file(merge, prefix + ".icons.bmp");

    const auto icons = merge.split(p0_dfm.image_width, p0_dfm.image_height);
    assert(p0_dfm.number_of_images <= icons.size());
    for (uint16_t icon_no = 0; icon_no < p0_dfm.number_of_images; ++icon_no)
    {
        dfm::utils::io::save_to_file(icons[ icon_no ], prefix + ".icon" + std::to_string(icon_no) + ".bmp");
    }

    assert(s <= v.size());
    if (s < v.size())
    {
        if (out_raw)
        {
            dfm::utils::io::save_to_file(p + s, p + v.size(), prefix + ".raw.trailing");
        }
        std::cout << "Info: trailing " << (v.size() - s) << " bytes with unknown meaning found" << std::endl;
    }
}
