#ifndef SALE_H
#define SALE_H

#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

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

struct Sale {
    int id;
    int price;
    std::string item;
    std::string buyer;
    unsigned long date;

    bool operator==(const Sale& other) const {
        return id == other.id;
    }

    std::string toCsv() const {
        return std::to_string(id) + "," + std::to_string(price) + "," + item + "," + buyer + "," + std::to_string(date);    
    }

    static Sale fromCsv(const std::string& line) {
        std::stringstream ss(line);
        std::string temp;
        Sale s;

        // ORDER MATTERS
        std::getline(ss, temp, ',');
        s.id = std::stoi(temp);

        std::getline(ss, temp, ',');
        s.price = std::stoi(temp);

        std::getline(ss, s.item, ',');

        std::getline(ss, s.buyer, ',');

        std::getline(ss, temp);

        // retrocompatibility: if the date is stored as a string, convert it; otherwise, assume it's already an epoch long
        if (temp.find('/') != std::string::npos) {
            s.date = dateToEpoch(temp);
        } else
            s.date = std::stoul(temp);

        return s;
    }
    
    void display() const {
        std::cout << "ID: " << id << " | Buyer: " << buyer
        << " | Item: " << item << " | Date: "
        << epochToDate(date) << " | Price: $" << price << std::endl;
    }
};

#endif