//
// Created by Kevin on 5/7/2017.
//

#include "token.hpp"

const std::string &token::getName() const {
    return name;
}

const std::regex &token::getPattern() const {
    return pattern;
}

token::token(const std::string &name, const std::regex &pattern)
        : name(name), pattern(pattern) {
}

const bool token::matches(std::string s) const {
    return std::regex_match(s, this->pattern);
}
