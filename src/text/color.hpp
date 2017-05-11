//
// Created by kpberry on 5/9/17.
//

#ifndef COLOR_H
#define COLOR_H

#include "../../include/json.hpp"

namespace color_ns {
    typedef struct color_t {
        int r, g, b;
    } color_t;

    void to_json(nlohmann::json &j, const color_t &c);
    void from_json(const nlohmann::json &j, color_t &c);
    int sqr_dist(color_t a, color_t b);
    extern color_ns::color_t windows_colors[8];
    int closest_windows_color_index(color_t c);
}

namespace fg {
    enum color {
        black = 30,
        red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white
    };
}

namespace bg {
    enum color {
        black = 40,
        red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white
    };
}

#endif

