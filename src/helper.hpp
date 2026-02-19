#ifndef HELPER_HPP
#define HELPER_CPP

#include <string>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace date {
    
    unsigned long dateToEpoch(const std::string& date) {
        std::tm tm = {};
        std::istringstream ss(date);
        ss >> std::get_time(&tm, "%d/%m/%Y");
        return std::mktime(&tm);
    }

    std::string epochToDate(unsigned long epoch) {
        std::time_t t = epoch;
        std::tm* tm = std::localtime(&t);
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm);
        return std::string(buffer);
    }
}
namespace price {
    int priceToInt(const std::string& date) {
        int value = 0;
        std::string s_value, s_valueCents;
        
        size_t index = date.find('.');
        if (index == -1) index = date.find(',');
        if (index == -1) index = 0;

        s_value = date.substr(0, index);
        s_valueCents = date.substr(index + 1);
        if (s_valueCents.size() == 1) s_valueCents += "0";

        value = std::stoi(s_value);
        value *= 100; //converting to cents
        value += std::stoi(s_valueCents);

        return value;
    }

    std::string intToPrice(const int value) {

        int whole = 0, cents = 0;
        whole = value / 100;
        cents = (value / 100.0 - whole) * 100; 
 
        return std::to_string(whole) + "," + std::to_string(cents);
    }
}

#endif