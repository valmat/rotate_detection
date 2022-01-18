#pragma once

#include <utility>
#include "pixwrap.h"
#include "rotopts.h"


namespace derot { //detect rotation

    // Returns the angle to rotate image to make aligned
    int get_pix_rotation(const Pix *pix, const PixRotOpts& opts = {}) noexcept;

    // returns [width, height]
    std::pair<int, int> get_pix_rotation_wh(const Pix *pix, int angle) noexcept;
}