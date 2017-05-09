//
// Created by kpberry on 5/9/17.
//

#include <iostream>
#include <sstream>
#include "string_formatter.h"

using namespace std;

string color_string(string s, fg::color color) {
    return "\033[1;" + std::to_string(color) + "m" + s + "\033[0m";
}

string rgb_string(string s, int r, int g, int b) {
    std::stringstream stream;
    stream << "\033[38;2;" << r << ';' << g << ';' << b << 'm' << s << "\033[0m";
    return stream.str();
}