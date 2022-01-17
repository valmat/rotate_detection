#include "utils.h"

std::vector<std::pair<int, int>>
splitRange(int from, int to, size_t threads) noexcept
{
    // TODO Redo this into a range
    std::vector<std::pair<int, int>> pairs;
    pairs.reserve(threads);

    int range_len = to - from + 1;
    int sub_len   = range_len / threads;
    size_t rest_len  = range_len % threads;

    int cur_from = from;
    int cur_to;

    for (size_t i = 0; i < rest_len && cur_from <= to; ++i) {
        cur_to   = cur_from + sub_len;
        pairs.emplace_back(cur_from, cur_to);
        cur_from = cur_to + 1;
    }
    
    for (size_t i = rest_len; i < threads && cur_from <= to; ++i) {
        cur_to   = cur_from + sub_len - 1 ;
        pairs.emplace_back(cur_from, cur_to);
        cur_from = cur_to + 1;
    }    

    return pairs;
}

// 
// Example:
// Splits [-45, 45] into following
// 
// [-45, -38] /(8pcs.)
// [-37, -30] /(8pcs.)
// [-29, -22] /(8pcs.)
// [-21, -14] /(8pcs.)
// [-13, -6 ] /(8pcs.)
// [-5,  2  ] /(8pcs.)
// [3,   10 ] /(8pcs.)
// [11,  17 ] /(7pcs.)
// [18,  24 ] /(7pcs.)
// [25,  31 ] /(7pcs.)
// [32,  38 ] /(7pcs.)
// [39,  45 ] /(7pcs.)
