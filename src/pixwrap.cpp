// 
// Simplest wrapper for RAII reason
// 

#include "pixwrap.h"
#include <allheaders.h>

PixWrap::PixWrap(const char *fname) noexcept :
    pix(pixRead(fname))
{}

PixWrap::~PixWrap()
{
    pixDestroy(&pix);
}

bool PixWrap::writePng(const char *fname, float gamma = 0) noexcept
{
    return pixWritePng(fname, pix, gamma);
}