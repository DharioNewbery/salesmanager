#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "Vector.h"
#include "Sale.h"

namespace utils {
    void printSalesList(Vector<Sale> sales, int start = 0, int end = INT_MAX) {

        if (end == INT_MAX) end = sales.getSize();

        for (size_t i = start; i < sales.getSize() && i < end; i++) {
            sales[i].display();
        }
    }
}

#endif