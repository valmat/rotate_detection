#pragma once

#include <utility>
#include <vector>

namespace derot { //detect rotation
    
    // Evenly splits the values range for load balancing CPU cores 
    [[nodiscard]] 
    std::vector<std::pair<int, int>>
    splitRange(int from, int to, size_t threads) noexcept;
}