/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <string>
#include <string_view>

// Own

namespace dfm
{
    constexpr std::string_view LIBDFM_LICENSE()
    {
        constexpr std::string_view __DFM_LICENSE = R"(MIT License

Copyright (c) 2022 Daniel Korner

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.)";
        return __DFM_LICENSE;
    }

    constexpr std::string_view LIBDFM_URL()
    {
        constexpr std::string_view __DFM_URL = "https://github.com/Dadie/dfm-toolkit";
        return __DFM_URL;
    }

    constexpr std::string_view LIBDFM_NAME()
    {
        constexpr std::string_view __DFM_NAME = "libdfm";
        return __DFM_NAME;
    }
}
