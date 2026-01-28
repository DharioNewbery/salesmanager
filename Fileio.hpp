#ifndef FILEIO_HPP
#define FILEIO_HPP

#include "Sale.h"
#include "Vector.h"
#include <fstream>
#include <string>

void saveToFile(const std::string& filename, Vector<Sale> sales) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Could not open file for saving");

    for (int i = 0; i < sales.getSize(); i++) {
        file << sales[i].toCsv() << "\n";
    }
    file.close();
}

Vector<Sale> loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    Vector<Sale> sales = Vector<Sale>();

    if (!file.is_open()) return sales; // If file doesn't exist, just start empty

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        sales.push(Sale::fromCsv(line));
    }

    return sales;
}

#endif