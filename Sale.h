#ifndef SALE_H
#define SALE_H

#include <iostream>

struct Sale {
    int id;
    int price;
    std::string item;
    std::string buyer;
    std::string date;

    // We can define the display logic right here
    void display() const {
        std::cout << "ID: " << id << " | Item: " << item
        << " | Price: $" << price << " | Buyer: "
        << buyer << " | Date: " << date << std::endl;
    }
};

#endif