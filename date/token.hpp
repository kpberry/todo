//
// Created by Kevin on 5/7/2017.
//

#ifndef TODO_TOKEN_HPP
#define TODO_TOKEN_HPP

#include <string>
#include <regex>

class token {
private:
public:
    token(const std::string &name, const std::regex &pattern);
private:
    const std::string name;
    const std::regex pattern;
public:
    const std::string &getName() const;
    const std::regex &getPattern() const;
    const bool matches(std::string s) const;
};


#endif //TODO_TOKEN_HPP
