#include <iostream>
#include <cmath>
#include <sstream>
#include <allheaders.h>
#include "pixwrap.h"
#include "get_rotation.h"



int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <from_image_file> <to_file.png>" << std::endl; 
        return 1;
    }

    PixWrap pix_orig {argv[1]};
    
    PixRotOpts opts;
    // opts.use_vertical = false;
    // opts.threads = 1;
    
    int angle = get_pix_rotation(pix_orig, opts);
    std::cerr << "angle: " << angle << std::endl; 
    
    double angle_rad = angle * M_PI / 180;    
    
    std::cerr << "width : " << pixGetWidth (pix_orig) << std::endl; 
    std::cerr << "height: " << pixGetHeight(pix_orig) << std::endl; 

    auto [width, height] = get_pix_rotation_wh(pix_orig, angle);
    std::cerr << "width : " << width << std::endl; 
    std::cerr << "height: " << height << std::endl; 

    // pixRotate ( PIX *pixs, l_float32 angle, l_int32 type, l_int32 incolor, l_int32 width, l_int32 height );
    PixWrap(pixRotate(pix_orig, angle_rad, L_ROTATE_AREA_MAP, L_BRING_IN_WHITE, width, height )).writePng(argv[2]);
    // PixWrap(pixRotate(pix_orig, angle_rad, L_ROTATE_AREA_MAP, L_BRING_IN_WHITE, 0, 0 )).writePng("out-rot.png");

    return 0;
}

// bin/example1.bin ../demo/1-in.jpg ../demo/1-out.png
// bin/example1.bin ../demo/2-in.jpg ../demo/2-out.png
// bin/example1.bin ../demo/3-in.jpg ../demo/3-out.png
// bin/example1.bin ../demo/4-in.jpg ../demo/4-out.png
// bin/example1.bin ../demo/5-in.jpg ../demo/5-out.png