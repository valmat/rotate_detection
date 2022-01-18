#pragma once

#include <utility>
#include <vector>
#include "pixwrap.h"


derot::PixWrap pix_rotate(const Pix* pix, int degrees, bool extend_size = true) noexcept;
