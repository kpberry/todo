//
// Created by Kevin on 5/7/2017.
//

#include <string>

#include "scanner.hpp"
#include "token.hpp"

using namespace std;
/*
const std::vector<token>& scanner::scan(std::string input) {
    unsigned int start_index = 0;
    unsigned int end_index = 0;
    int input_length = input.length();
    std::vector<const token*> still_matching;
    std::vector<const token*> next_matching;
    for (int i = 0; i < tokens.size(); i++) {
        still_matching.push_back(&tokens[i]);
    }
    const token* longest_match = nullptr;
    while (start_index < input_length) {
        string str = input.substr(start_index, end_index);
        while (still_matching.size() > 0) {
            for (const token* t : still_matching) {
                if (t->matches(str)) {
                    longest_match = t;
                }
            }
        }
    }
    return std::vector<token>();
}

*/
