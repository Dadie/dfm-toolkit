/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext

// Std
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

// Own
#include <dfm/utils/bits.h>
#include <dfm/utils/form/envelope.h>

size_t dfm::utils::form::dfm_timage_header::load(const uint8_t* p)
{
    size_t s = 0;
    this->size = dfm::utils::bits::p2u8((p == nullptr ? p : (p + s)), s);
    this->id.resize(size);
    for (size_t i = 0; i < this->size; ++i)
    {
        id[ i ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    }
    assert(this->size >= 0);
    assert(s == static_cast< size_t >(this->size + 1));
    return s;
}

size_t dfm::utils::form::dfm_timage_header::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::u8w2p(size, (p == nullptr ? p : (p + s)));
        for (size_t i = 0; i < size; ++i)
        {
            s += dfm::utils::bits::i8w2p(id[ i ], (p == nullptr ? p : (p + s)));
        }
    }
    return s;
}

dfm::utils::form::dfm_timage_header::operator bool() const
{
    return size > 0 && size == id.size();
}

void dfm::utils::form::dfm_timage_header::pp(std::ostream& out) const
{
    out << "size: " << +(size) << std::endl;
    out << "id: " << id << std::endl;
}

size_t dfm::utils::form::dfm_timagelist_header::load(const uint8_t* p)
{
    size_t s = 0;
    assert(p != nullptr);
    id[ 0 ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    id[ 1 ] = dfm::utils::bits::p2i8((p == nullptr ? p : (p + s)), s);
    unknown_0 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    number_of_images = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_2 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_3 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    image_width = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    image_height = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_4 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_5 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_6 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_7 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_8 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_9 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_a = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);

    assert(s == 28);
    return s;
}

size_t dfm::utils::form::dfm_timagelist_header::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::i8w2p(id[ 0 ], (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::i8w2p(id[ 1 ], (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_0, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(number_of_images, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_2, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_3, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(image_width, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(image_height, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_4, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_5, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_6, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_7, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_8, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_9, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_a, (p == nullptr ? p : (p + s)));
    }
    assert(s == 28);
    return s;
}

dfm::utils::form::dfm_timagelist_header::operator bool() const
{
    return id[ 0 ] != '\0' && id[ 1 ] != '\0';
}

void dfm::utils::form::dfm_timagelist_header::pp(std::ostream& out) const
{
    out << "id: " << std::string(id, 2) << std::endl;
    out << "unknown_0: " << unknown_0 << std::endl;
    out << "number_of_images: " << number_of_images << std::endl;
    out << "unknown_2: " << unknown_2 << std::endl;
    out << "unknown_3: " << unknown_3 << std::endl;
    out << "image_width: " << image_width << std::endl;
    out << "image_height: " << image_height << std::endl;
    out << "unknown_4: " << unknown_4 << std::endl;
    out << "unknown_5: " << unknown_5 << std::endl;
    out << "unknown_6: " << unknown_6 << std::endl;
    out << "unknown_7: " << unknown_7 << std::endl;
    out << "unknown_8: " << unknown_8 << std::endl;
    out << "unknown_9: " << unknown_9 << std::endl;
    out << "unknown_a: " << unknown_a << std::endl;
}

size_t dfm::utils::form::dfm_timagelist_footer::load(const uint8_t* p)
{
    size_t s = 0;
    unknown_0 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_1 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_2 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_3 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_4 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_5 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_6 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_7 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_8 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_9 = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    unknown_a = dfm::utils::bits::p2u16((p == nullptr ? p : (p + s)), s);
    assert(s == 22);
    return s;
}

size_t dfm::utils::form::dfm_timagelist_footer::save(uint8_t* p) const
{
    size_t s = 0;
    {
        s += dfm::utils::bits::u16w2p(unknown_0, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_1, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_2, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_3, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_4, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_5, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_6, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_7, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_8, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_9, (p == nullptr ? p : (p + s)));
        s += dfm::utils::bits::u16w2p(unknown_a, (p == nullptr ? p : (p + s)));
    }
    assert(s == 22);
    return s;
}

dfm::utils::form::dfm_timagelist_footer::operator bool() const
{
    return true;
}
