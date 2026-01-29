#ifndef SALE_H
#define SALE_H

#include <sstream>
#include <iostream>

struct Sale {
    int id;
    int price;
    std::string item;
    std::string buyer;
    std::string date;

    std::string toCsv() const {
        return std::to_string(id) + "," + std::to_string(price) + "," + item + "," + buyer + "," + date;    
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

        std::getline(ss, s.date);

        return s;
    }
    
    void display() const {
        std::cout << "ID: " << id << " | Item: " << item
        << " | Price: $" << price << " | Buyer: "
        << buyer << " | Date: " << date << std::endl;
    }
};

#endif