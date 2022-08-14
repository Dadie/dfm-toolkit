/* SPDX-License-Identifier: MIT */
/* Copyright © 2022 Daniel Korner */
/* {HEADER} */

#pragma once
// Ext

// Std
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>

// POSIX
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// Own

namespace dfm::utils::io
{
    template < typename T >
    T load_from_file(const std::filesystem::path& path)
    {
        // open file descriptor
        auto fd = ::open(path.c_str(), O_RDONLY);
        std::shared_ptr< void > close_fd(nullptr, [ & ](...) { ::close(fd); });

        // Memorymap file
        const auto file_size = std::filesystem::file_size(path);
        void* file_ptr = ::mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
        std::shared_ptr< void > unmap_file_ptr(nullptr, [ & ](...) { ::munmap(file_ptr, file_size); });

        // Load from memorymap
        T data;
        data.load(reinterpret_cast< uint8_t* >(file_ptr));
        return data;
    }

    template < typename T >
    size_t save_to_file(const T& data, const std::filesystem::path& path)
    {
        // Determine mmap size
        const auto file_size = data.save(nullptr);

        // open file descriptor
        auto fd = ::open(path.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        ::ftruncate(fd, file_size);
        std::shared_ptr< void > close_fd(nullptr, [ & ](...) { ::close(fd); });

        // Create memorymapped file
        void* file_ptr = ::mmap(nullptr, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        std::shared_ptr< void > unmap_file_ptr(nullptr, [ & ](...) { ::munmap(file_ptr, file_size); });

        // Save to memorymapped file
        data.save(reinterpret_cast< uint8_t* >(file_ptr));
        return file_size;
    }

    template < typename InputIt >
    size_t save_to_file(InputIt begin, InputIt end, const std::filesystem::path& path)
    {
        std::ofstream outstream(path);
        if (begin != end)
        {
            std::copy(begin, end, std::ostream_iterator< uint8_t >(outstream));
        }
        return outstream.tellp();
    }

    std::string sanitize_filename(const std::string& fname);

}
