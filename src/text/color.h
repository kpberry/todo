//
// Created by kpberry on 5/9/17.
//

#ifndef COLOR_H
#define COLOR_H

#include "../../include/json.hpp"

using json=nlohmann::json;

namespace color_ns {
    typedef struct color_t {
        int r, g, b;
    } color_t;

    //function is static to avoid linker errors
    static void to_json(json &j, const color_t &c) {
        j = json{
                {"r", c.r},
                {"g", c.g},
                {"b", c.b}
        };
    }

    static void from_json(const json &j, color_t &c) {
        c.r = j.at("r").get<int>();
        c.g = j.at("g").get<int>();
        c.b = j.at("b").get<int>();
    }
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

