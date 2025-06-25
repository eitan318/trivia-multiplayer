#pragma once
#include <string>

class HashService {
public:
    // Static method to hash a string
    static size_t HashString(const std::string& input) {
        return std::hash<std::string>{}(input);
    }

};
