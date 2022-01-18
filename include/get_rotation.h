#pragma once

#include <utility>
#include "pixwrap.h"


namespace derot{ //detect rotation

    struct PixRotOpts
    {
        float contrast_factor = 1.0;
        int   threshold       = 170;   // Threshold for creating black-white representation
        int   angle_first     = -45;   // Starts searching angle from angle_first
        int   angle_last      = 45;    // Completes search the angle on angle_last
        int   angle_step      = 1;     // Step withs searching angle
        bool  fast            = false; // true -- fast, false -- slow, but more accurate (scans vertical lines)
        uint  threads         = 0;     // 0 -- Use all (Multithreading)
    };

    // Returns the angle to rotate image to make aligned
    int get_pix_rotation(const Pix *pix, const PixRotOpts& opts = {}) noexcept;

    // returns [width, height]
    std::pair<int, int> get_pix_rotation_wh(const Pix *pix, int angle) noexcept;
}