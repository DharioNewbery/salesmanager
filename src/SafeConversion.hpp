#ifndef SAFE_CONVERSION_HPP
#define SAFE_CONVERSION_HPP

#include <string>

bool tryParseInt(const std::string& str, int& out) {
    if (str.empty()) return false;
    try {
        out = std::stoi(str);
        return true;
    } catch (...) {
        return false;
    }
}

#endif