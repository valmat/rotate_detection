#pragma once

// 
// Simplest wrapper for RAII reason
// 

#include <iostream>
#include <utility>


struct Pix;

namespace derot { //detect rotation

    struct PixWrap final
    {
        Pix* pix = nullptr;

        PixWrap() = default;

        PixWrap(const char *fname) noexcept;

        ~PixWrap();

        bool writePng(const char *fname, float gamma = 0) noexcept;

        operator Pix*() noexcept
        {
            return pix;
        }
        Pix* get() noexcept
        {
            return pix;
        }
        const Pix* get() const noexcept
        {
            return pix;
        }

        PixWrap(Pix* ptr) noexcept :
            pix(ptr)
        {}

        PixWrap(PixWrap && rhs) noexcept :
            pix(std::exchange(rhs.pix, nullptr))
        {}

        PixWrap &operator=(PixWrap && rhs) noexcept
        {
            std::swap(pix, rhs.pix);
            return *this;
        }

        // No copyable
        PixWrap(const PixWrap &)            = delete;
        PixWrap &operator=(const PixWrap &) = delete;

    };
}