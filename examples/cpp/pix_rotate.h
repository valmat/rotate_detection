#pragma once

#include <utility>
#include <vector>
#include "pixwrap.h"


PixWrap pix_rotate(const Pix* pix, int degrees, bool extend_size = true) noexcept;
