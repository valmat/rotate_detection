#pragma once

#include <utility>
#include "pixwrap.h"


struct GetPixRotOts
{
    float contrast_factor = 1.0;
    int   threshold       = 170;  // Threshold for creating black-white representation
    int   angle_first     = -45;  // Starts searching angle from angle_first
    int   angle_last      = 45;   // Completes search the angle on angle_last
    int   angle_step      = 1;    // Step withs searching angle
    bool  use_vertical    = true; // false -- fast, true -- slow, but more accurate
    uint  threads         = 1;    // 0 -- Use all 
};

// Returns the angle to rotate image to make aligned
int get_pix_rotation(const Pix *pix, const GetPixRotOts& opts = {}) noexcept;

// returns [width, height]
std::pair<int, int> get_pix_rotation_wh(const Pix *pix, int angle) noexcept;