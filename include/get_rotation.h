#pragma once

#include <utility>
#include "pixwrap.h"
#include "rotopts.h"


namespace derot { //detect rotation

    // Returns the angle to rotate image to make aligned
    int get_pix_rotation(const Pix *pix, const PixRotOpts& opts = {}) noexcept;

    // returns diagonal size to extend image with rotatiion
    size_t get_pix_diagonal(const Pix *pix) noexcept;

    // returns [width, height]
    std::pair<int, int> get_pix_rotation_wh(const Pix *pix, int angle) noexcept;
    
    // Returns transformed to black/white pix if necessary.
    // If original image is already black/white, returns nullptr.
    Pix* get_bw_pix(const Pix* pix, float contrast_factor, int threshold) noexcept;
}