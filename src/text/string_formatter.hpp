//
// Created by kpberry on 5/9/17.
//

#ifndef STRING_FORMATTER_H
#define STRING_FORMATTER_H

#include <string>
#include "color.h"

std::string color_string(const std::string s, fg::color color);
const std::string rgb_string(const std::string& s, const color_ns::color_t& c);

#endif