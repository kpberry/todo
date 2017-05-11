//
// Created by kpberry on 5/10/17.
//

#include "color.hpp"

using namespace color_ns;

namespace color_ns {
    color_t windows_colors[8] = {
            {0,   0,   0},
            {128, 0,   0},
            {0,   128, 0},
            {128, 128, 0},
            {0,   0,   128},
            {128, 0,   128},
            {0,   128, 128},
            {192, 192, 192}
    };

    int closest_windows_color_index(color_t c) {
        int min_dist = sqr_dist(c, windows_colors[0]);
        int index = 0;
        for (int i = 1; i < sizeof(windows_colors) / sizeof(color_t); i++) {
            int dist = sqr_dist(c, windows_colors[i]);
            if (dist < min_dist) {
                min_dist = dist;
                index = i;
            }
        }
        return index;
    }

    int sqr_dist(color_t a, color_t b) {
        return (a.r - b.r) * (a.r - b.r)
               + (a.g - b.g) * (a.g - b.g)
               + (a.b - b.b) * (a.b - b.b);
    }

    void from_json(const nlohmann::json &j, color_t &c) {
        c.r = j.at("r").get<int>();
        c.g = j.at("g").get<int>();
        c.b = j.at("b").get<int>();
    }

    void to_json(nlohmann::json &j, const color_t &c) {
        j = nlohmann::json{
                {"r", c.r},
                {"g", c.g},
                {"b", c.b}
        };
    }
}
