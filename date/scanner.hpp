//
// Created by Kevin on 5/7/2017.
//

#ifndef TODO_SCANNER_H
#define TODO_SCANNER_H

#include <vector>
#include <string>
#include <regex>
#include "token.hpp"

class scanner {
private:
    const std::vector<const token> tokens;
public:
    const std::vector<const token> & scan(std::string input);
};

#endif //TODO_SCANNER_H
