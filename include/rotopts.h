#pragma once

namespace derot { //detect rotation

    struct PixRotOpts final
    {
        float contrast_factor = 1.0;
        int   threshold       = 170;   // Threshold for creating black-white representation
        int   angle_first     = -45;   // Starts searching angle from angle_first
        int   angle_last      = 45;    // Completes search the angle on angle_last
        int   angle_step      = 1;     // Step withs searching angle
        bool  fast            = false; // true -- fast, false -- slow, but more accurate (scans vertical lines)
        uint  threads         = 0;     // 0 -- Use all (Multithreading)
    };

}