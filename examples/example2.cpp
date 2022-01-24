#include <iostream>
#include "pixwrap.h"
#include "get_rotation.h"

#include "pix_rotate.h"

using derot::PixWrap;
using derot::PixRotOpts;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <from_image_file> <to_file.png>" << std::endl; 
        return 1;
    }

    PixWrap pix {argv[1]};
    
    PixRotOpts opts;
    // opts.fast = true;
    // opts.threads = 1;
    // opts.contrast_factor = 1.0;
    // opts.threshold       = 170;   // Threshold for creating black-white representation
    // opts.angle_first     = -45;   // Starts searching angle from angle_first
    // opts.angle_last      = 45;    // Completes search the angle on angle_last
    
    // opts.angle_first     = -20;   // Starts searching angle from angle_first
    // opts.angle_last      = 20;    // Completes search the angle on angle_last

    // opts.angle_step      = 1;     // Step withs searching angle
    // opts.fast            = false; // true -- fast, false -- slow, but more accurate (scans vertical lines)
    // opts.threads         = 0;     // 0 -- Use all (Multithreading)

    int angle = derot::get_pix_rotation(pix, opts);
    std::cerr << "angle: " << angle << std::endl;
    
    bool extend_size = true;
    pix_rotate(pix, angle, extend_size).writePng(argv[2]);

    return 0;
}

// bin/example2.bin ../demo/1-in.jpg ../demo/1-out.png
// bin/example2.bin ../demo/2-in.jpg ../demo/2-out.png
// bin/example2.bin ../demo/3-in.jpg ../demo/3-out.png
// bin/example2.bin ../demo/4-in.jpg ../demo/4-out.png
// bin/example2.bin ../demo/5-in.jpg ../demo/5-out.png