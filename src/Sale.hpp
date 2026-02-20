#ifndef SALE_H
#define SALE_H

#include <string>
#include <sstream>
#include <iostream>
#include "utils.hpp"

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
            s.date = date::dateToEpoch(temp);
        } else
            s.date = std::stoul(temp);
        return s;
    }
    
    void display() const {
        std::cout << "ID: " << id << " | Buyer: " << buyer
        << " | Item: " << item << " | Date: "
        << date::epochToDate(date) << " | Price: $" << price::intToPrice(price) << std::endl;
    }
};

#endif