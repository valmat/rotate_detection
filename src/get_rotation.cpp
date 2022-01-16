#include "get_rotation.h"
#include "utils.h"

#include <cmath>
#include <limits>

#include <thread>
#include <future>

#include <iostream>
#include <allheaders.h>


namespace {

    // Get pix value (0/1)
    int getPixVal(size_t x, size_t y, const uint32_t *data, int32_t wpl) noexcept
    {
        return GET_DATA_BIT(data + y * wpl, x) ? 1 : 0;
    }

    float Q_rsqrt( float number ) noexcept
    {   
        const float x2 = number * 0.5F;
        const float threehalfs = 1.5F;

        union {
            float f;
            uint32_t i;
        } conv = {number}; // member 'f' set to value of 'number'.
        conv.i = 0x5f3759df - ( conv.i >> 1 );
        conv.f *= threehalfs - x2 * conv.f * conv.f;
        return conv.f;
    }

    double getEntropy(double p) noexcept
    {
        double q = 1.0 - p;
        // The Rényi entropy
        // return (p > 0.0 && p < 1.0) ? -log(p*p + q*q) : 0.0;
        // return (p > 0.0 && p < 1.0) ? -log(pow(p, 100) + pow(q, 100)) / 99 : 0.0;
        return (p > 0.0 && p < 1.0) ? 2 * log(sqrt(p) + sqrt(q)) : 0.0;
        return (p > 0.0 && p < 1.0) ? 2 * log(Q_rsqrt(p) + Q_rsqrt(q)) : 0.0;

        // return (p > 0.0 && p < 1.0) ? log(pow(p, 0.1) + pow(q, 0.1)) / 0.9 : 0.0;
        // Шеннон
        // return (p > 0.0 && p < 1.0) ? -(p * log(p) + q * log(q)) : 0.0;
    }

    double getEntropy(const uint32_t *pixData, size_t width, size_t height, int32_t wpl, int angle, bool use_vertical) noexcept
    {
        double angle_rad = angle * M_PI / 180;
        double entSum = 0;

        for (size_t y = 0; y < height; ++y)
        {
            size_t blacks = 0;

            for (size_t x = 0; x < width; ++x)
            {
                int x_ = int(width  + x * cos(angle_rad) - y * sin(angle_rad) ) % width;
                int y_ = int(height + x * sin(angle_rad) + y * cos(angle_rad) ) % height;
                
                blacks += getPixVal(x_, y_, pixData, wpl);
            }

            entSum += getEntropy(1.0 * blacks / width) / height;
        }

        if(use_vertical) {
            for (size_t x = 0; x < width; ++x)
            {
                size_t blacks = 0;
                for (size_t y = 0; y < height; ++y)
                {
                    int x_ = int(width  + x*cos(angle_rad) - y*sin(angle_rad) ) % width;
                    int y_ = int(height + x*sin(angle_rad) + y*cos(angle_rad) ) % height;
                    
                    blacks += getPixVal(x_, y_, pixData, wpl);;
                }
                entSum += getEntropy(1.0 * blacks / height) / width;
            }
            entSum /= 2.0;
        }

        // std::cerr << angle << ", " << entSum << std::endl;
        return entSum;
    }

    PixWrap bw_bix(const PIX *pix, float contrast_factor, int threshold) noexcept
    {
        const PIX *orig_pix = pix;
        PixWrap gray_pix;

        if(pixGetDepth(pix) > 8) {
            gray_pix = pixConvertRGBToLuminance(const_cast<PIX*>(pix));
            orig_pix = gray_pix;
        }
        PixWrap ctr_pix {pixContrastTRC(nullptr, const_cast<PIX*>(orig_pix), contrast_factor)};

        return pixConvertTo1(ctr_pix, threshold);
    }

    std::pair<int, double> find_best(const uint32_t *pixData, size_t width, size_t height, int32_t wpl, const GetPixRotOts& opts) noexcept
    {
        int    best_angle = 0;
        double min_ent    = std::numeric_limits<double>::max();

        for (int angle = opts.angle_first; angle <= opts.angle_last; angle += opts.angle_step) {
            double ent = getEntropy(pixData, width, height, wpl, angle, opts.use_vertical);
            if(min_ent > ent) {
                min_ent    = ent;
                best_angle = angle;
            }
        }

        return std::make_pair(-best_angle, min_ent);
    }
}

int get_pix_rotation(const PIX *orig_pix, const GetPixRotOts& opts) noexcept
{
    PixWrap pix = bw_bix(orig_pix, opts.contrast_factor, opts.threshold);
    pix.writePng("out-1.png");


    size_t width  = pixGetWidth  (pix);
    size_t height = pixGetHeight (pix);
    int32_t   wpl  = pixGetWpl   (pix);
    const uint32_t *pixData = pixGetData(pix);


    uint threads = (0 == opts.threads) ? std::thread::hardware_concurrency() : opts.threads;
    // std::cerr << "threads : " << threads << std::endl;
    if(1 == threads) {
        auto [best_angle, min_ent] = find_best(pixData, width, height, wpl, opts);
        return best_angle;
    }


    // Multithreading
    std::vector<std::future<std::pair<int, double>>> tasks;
    tasks.reserve(threads);

    for (auto&& [cur_from, cur_to]: splitRange(opts.angle_first, opts.angle_last, threads)) {
        GetPixRotOts o = opts;
        o.angle_first     = cur_from;
        o.angle_last      = cur_to;

        // std::cerr << "(" << cur_from << ", " << cur_to << ")*[" << (cur_to - cur_from + 1) << "]" << std::endl;
        tasks.emplace_back( std::async(std::launch::async, find_best, pixData, width, height, wpl, o) );
    }

    int    best_angle = 0;
    double min_ent    = std::numeric_limits<double>::max();
    for(auto& task: tasks) {
        auto [angle, ent] = task.get();
        if(min_ent > ent) {
            min_ent    = ent;
            best_angle = angle;
        }
    }
    
    return best_angle;
}

// returns [width, height]
std::pair<int, int> get_pix_rotation_wh(const PIX *pix, int angle) noexcept
{
    int width  = pixGetWidth (pix);
    int height = pixGetHeight(pix);
    double angle_rad = angle * M_PI / 180; 

    return std::make_pair(
        width * sin(angle_rad) + height * cos(angle_rad) ,
        width * cos(angle_rad) + height * sin(angle_rad)
    );
}