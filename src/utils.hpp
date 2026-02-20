#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <climits>

#include "Vector.hpp"

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
};

namespace input {
    Vector<std::string> splitInput(std::string input) {
        Vector<std::string> result = Vector<std::string>();
        std::string currentToken = "";
        bool insideQuotes = false;

        for (size_t i = 0; i < input.length(); ++i) {
            char c = input[i];

            if (c == '\"') {
                // Toggle the state when we hit a quote
                insideQuotes = !insideQuotes;
            } 
            else if (c == ' ' && !insideQuotes) {
                // If it's a space and we aren't in quotes, the word is finished
                if (!currentToken.empty()) {
                    result.push(currentToken);
                    currentToken = "";
                }
            } 
            else {
                // Otherwise, keep building the current word
                currentToken += c;
            }
        }

        // Don't forget to add the very last token
        if (!currentToken.empty()) {
            result.push(currentToken);
        }

        return result;
    }
}

#include "Sale.hpp"

namespace utils {
    void printSalesList(Vector<Sale> sales, int start = 0, int end = INT_MAX) {

        if (end == INT_MAX) end = sales.getSize();

        for (size_t i = start; i < sales.getSize() && i < end; i++) {
            sales[i].display();
        }
    }
}


#endif