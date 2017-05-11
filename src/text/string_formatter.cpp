//
// Created by kpberry on 5/9/17.
//

#include <iostream>
#include <sstream>
#include "string_formatter.hpp"

using namespace std;
using namespace color_ns;

string color_string(const string& s, fg::color color) {
    return "\033[1;" + to_string(color) + "m" + s + "\033[0m";
}

const std::string rgb_string(const std::string& s, const color_ns::color_t& c) {
#if defined(_WIN32)
    return "\033[1;"
           + to_string(30 + closest_windows_color_index(c))
           + "m" + s + "\033[0m";
#else
    stringstream stream;
    stream << "\033[38;2;"
           << c.r << ';' << c.g << ';' << c.b << 'm'
           << s
           << "\033[0m";
    return stream.str();
#endif
}