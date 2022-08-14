/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

// Ext
#include <errno.h>
#include <iconv.h>
#include <string.h>

// Std
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// Own
#include <dfm/utils/iconv.h>

std::u16string dfm::utils::iconv::u8_to_u16le(const std::string& str)
{
    if (str.empty())
    {
        return {};
    }

    using buffer_value_type = char16_t;
    using target_value_type = char;
    const std::string to_code = "UTF-16LE";
    const std::string from_code = "UTF-8";
    std::vector< buffer_value_type > buffer;
    {
        buffer.resize(str.size() * sizeof(target_value_type) * 2);
    }
    char* iconv_in = const_cast< char* >(reinterpret_cast< const char* >(&(str[ 0 ])));
    char* iconv_out = const_cast< char* >(reinterpret_cast< const char* >(&(buffer[ 0 ])));
    size_t iconv_in_left = str.size() * sizeof(target_value_type);
    size_t iconv_out_left = buffer.size() * sizeof(buffer_value_type);
    ::iconv_t cd = ::iconv_open(to_code.c_str(), from_code.c_str());
    ::iconv(cd, &iconv_in, &iconv_in_left, &iconv_out, &iconv_out_left);
    ::iconv_close(cd);
    return std::u16string(buffer.data(), buffer.size() - (iconv_out_left / sizeof(buffer_value_type)));
}

std::u16string dfm::utils::iconv::u8_to_u16be(const std::string& str)
{
    if (str.empty())
    {
        return {};
    }

    using buffer_value_type = char16_t;
    using target_value_type = char;
    const std::string to_code = "UTF-16BE";
    const std::string from_code = "UTF-8";
    std::vector< buffer_value_type > buffer;
    {
        buffer.resize(str.size() * sizeof(target_value_type) * 2);
    }
    char* iconv_in = const_cast< char* >(reinterpret_cast< const char* >(&(str[ 0 ])));
    char* iconv_out = const_cast< char* >(reinterpret_cast< const char* >(&(buffer[ 0 ])));
    size_t iconv_in_left = str.size() * sizeof(target_value_type);
    size_t iconv_out_left = buffer.size() * sizeof(buffer_value_type);
    ::iconv_t cd = ::iconv_open(to_code.c_str(), from_code.c_str());
    ::iconv(cd, &iconv_in, &iconv_in_left, &iconv_out, &iconv_out_left);
    ::iconv_close(cd);
    return std::u16string(buffer.data(), buffer.size() - (iconv_out_left / sizeof(buffer_value_type)));
}

std::string dfm::utils::iconv::u16le_to_u8(const std::u16string& str)
{
    if (str.empty())
    {
        return {};
    }

    using buffer_value_type = char;
    using target_value_type = char16_t;
    const std::string to_code = "UTF-8";
    const std::string from_code = "UTF-16LE";
    std::vector< buffer_value_type > buffer;
    {
        buffer.resize(str.size() * sizeof(target_value_type) * 2);
    }
    char* iconv_in = const_cast< char* >(reinterpret_cast< const char* >(&(str[ 0 ])));
    char* iconv_out = const_cast< char* >(reinterpret_cast< const char* >(&(buffer[ 0 ])));
    size_t iconv_in_left = str.size() * sizeof(target_value_type);
    size_t iconv_out_left = buffer.size() * sizeof(buffer_value_type);
    ::iconv_t cd = ::iconv_open(to_code.c_str(), from_code.c_str());
    ::iconv(cd, &iconv_in, &iconv_in_left, &iconv_out, &iconv_out_left);
    ::iconv_close(cd);
    return std::string(buffer.data(), buffer.size() - (iconv_out_left * sizeof(buffer_value_type)));
}

std::string dfm::utils::iconv::u16be_to_u8(const std::u16string& str)
{
    if (str.empty())
    {
        return {};
    }

    using buffer_value_type = char;
    using target_value_type = char16_t;
    const std::string to_code = "UTF-8";
    const std::string from_code = "UTF-16BE";
    std::vector< buffer_value_type > buffer;
    {
        buffer.resize(str.size() * sizeof(target_value_type) * 2);
    }
    char* iconv_in = const_cast< char* >(reinterpret_cast< const char* >(&(str[ 0 ])));
    char* iconv_out = const_cast< char* >(reinterpret_cast< const char* >(&(buffer[ 0 ])));
    size_t iconv_in_left = str.size() * sizeof(target_value_type);
    size_t iconv_out_left = buffer.size() * sizeof(buffer_value_type);
    ::iconv_t cd = ::iconv_open(to_code.c_str(), from_code.c_str());
    ::iconv(cd, &iconv_in, &iconv_in_left, &iconv_out, &iconv_out_left);
    ::iconv_close(cd);
    return std::string(buffer.data(), buffer.size() - (iconv_out_left * sizeof(buffer_value_type)));
}

std::string dfm::utils::iconv::u16be_to_u8(const char* s, const size_t len)
{
    using buffer_value_type = char;
    using target_value_type = char16_t;
    const std::string to_code = "UTF-8";
    const std::string from_code = "UTF-16BE";
    std::vector< buffer_value_type > buffer;
    {
        buffer.resize(len * sizeof(target_value_type) * 3);
    }
    char* iconv_in = const_cast< char* >(s);
    char* iconv_out = const_cast< char* >(reinterpret_cast< const char* >(&(buffer[ 0 ])));
    size_t iconv_in_left = len * sizeof(target_value_type);
    size_t iconv_out_left = buffer.size() * sizeof(buffer_value_type);
    ::iconv_t cd = ::iconv_open(to_code.c_str(), from_code.c_str());
    ::iconv(cd, &iconv_in, &iconv_in_left, &iconv_out, &iconv_out_left);
    ::iconv_close(cd);
    return std::string(buffer.data(), buffer.size() - (iconv_out_left * sizeof(buffer_value_type)));
}

std::string dfm::utils::iconv::u16le_to_u8(const char* s, const size_t len)
{
    using buffer_value_type = char;
    using target_value_type = char16_t;
    const std::string to_code = "UTF-8";
    const std::string from_code = "UTF-16LE";
    std::vector< buffer_value_type > buffer;
    {
        buffer.resize(len * sizeof(target_value_type) * 3);
    }
    char* iconv_in = const_cast< char* >(s);
    char* iconv_out = const_cast< char* >(reinterpret_cast< const char* >(&(buffer[ 0 ])));
    size_t iconv_in_left = len * sizeof(target_value_type);
    size_t iconv_out_left = buffer.size() * sizeof(buffer_value_type);
    ::iconv_t cd = ::iconv_open(to_code.c_str(), from_code.c_str());
    ::iconv(cd, &iconv_in, &iconv_in_left, &iconv_out, &iconv_out_left);
    ::iconv_close(cd);
    return std::string(buffer.data(), buffer.size() - (iconv_out_left * sizeof(buffer_value_type)));
}

std::string dfm::utils::iconv::u32be_to_u8(const char* s, const size_t len)
{
    using buffer_value_type = char;
    using target_value_type = char16_t;
    const std::string to_code = "UTF-8";
    const std::string from_code = "UTF-32BE";
    std::vector< buffer_value_type > buffer;
    {
        buffer.resize(len * sizeof(target_value_type) * 5);
    }
    char* iconv_in = const_cast< char* >(s);
    char* iconv_out = const_cast< char* >(reinterpret_cast< const char* >(&(buffer[ 0 ])));
    size_t iconv_in_left = len * sizeof(target_value_type);
    size_t iconv_out_left = buffer.size() * sizeof(buffer_value_type);
    ::iconv_t cd = ::iconv_open(to_code.c_str(), from_code.c_str());
    ::iconv(cd, &iconv_in, &iconv_in_left, &iconv_out, &iconv_out_left);
    ::iconv_close(cd);
    return std::string(buffer.data(), buffer.size() - (iconv_out_left * sizeof(buffer_value_type)));
}

std::string dfm::utils::iconv::u32le_to_u8(const char* s, const size_t len)
{
    using buffer_value_type = char;
    using target_value_type = char16_t;
    const std::string to_code = "UTF-8";
    const std::string from_code = "UTF-32LE";
    std::vector< buffer_value_type > buffer;
    {
        buffer.resize(len * sizeof(target_value_type) * 5);
    }
    char* iconv_in = const_cast< char* >(s);
    char* iconv_out = const_cast< char* >(reinterpret_cast< const char* >(&(buffer[ 0 ])));
    size_t iconv_in_left = len * sizeof(target_value_type);
    size_t iconv_out_left = buffer.size() * sizeof(buffer_value_type);
    ::iconv_t cd = ::iconv_open(to_code.c_str(), from_code.c_str());
    ::iconv(cd, &iconv_in, &iconv_in_left, &iconv_out, &iconv_out_left);
    ::iconv_close(cd);
    return std::string(buffer.data(), buffer.size() - (iconv_out_left * sizeof(buffer_value_type)));
}
