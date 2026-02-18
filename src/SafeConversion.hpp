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

bool tryConvertDateToLong (const std::string& str, unsigned long& out) {
    if (str.empty()) return false;
    try {
        out = dateToEpoch(str);
        return true;
    } catch (...) {
        return false;
    }
}

bool tryConvertLongToDate(unsigned long epoch, std::string& out) {
    try {
        out = epochToDate(epoch);
        return true;
    } catch (...) {
        return false;
    }
}

#endif