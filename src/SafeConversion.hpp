#ifndef SAFE_CONVERSION_HPP
#define SAFE_CONVERSION_HPP

#include <string>
#include "utils.hpp"

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
        out = date::dateToEpoch(str);
        return true;
    } catch (...) {
        return false;
    }
}

bool tryConvertLongToDate(unsigned long epoch, std::string& out) {
    try {
        out = date::epochToDate(epoch);
        return true;
    } catch (...) {
        return false;
    }
}

bool tryConvertIntToPrice (int value, std::string& out) {
    try {
        out = price::intToPrice(value);
        return true;
    } catch (...) {
        return false;
    }
}

bool tryConvertPriceToInt (const std::string& price, int& out) {
    try {
        out = price::priceToInt(price);
        return true;
    } catch (...) {
        return false;
    }
}

#endif