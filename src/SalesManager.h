#ifndef SALES_MANAGER_H
#define SALES_MANAGER_H

#include "Vector.h"
#include "Sale.h"
#include "Fileio.hpp"

class SalesManager
{
private:
    Vector<Sale> sales;
    int nextId;
    int getLargestId();
public:
    SalesManager();
    ~SalesManager();

    bool addSale(Sale sale);
    bool removeSaleById(const int id);
    void listSales(const int start = 0, int end = INT_MAX);
    bool loadSales(std::string);
    bool saveSales(std::string);
};

int SalesManager::getLargestId()
{
    int biggest = 0;
    for (int i = 0; i < sales.getSize(); i++)
        biggest = (biggest < sales[i].id)? sales[i].id : biggest;
    return biggest;
}

SalesManager::SalesManager() : sales(), nextId(1) {}
SalesManager::~SalesManager() {}

bool SalesManager::addSale(Sale sale) {
    sale.id = nextId;
    sales.push(sale);
    nextId++;
    return true;
}

bool SalesManager::removeSaleById(const int id) {
    sales.remove(id);
    return true;
}

void SalesManager::listSales(const int start, int end) {

    if (end == INT_MAX) end = sales.getSize();
    
    for (int i = start; i < end; i++)
        sales[i].display();
    
}

bool SalesManager::loadSales(std::string saveFileName)
{
    try {
        sales = loadFromFile(saveFileName);
        nextId = getLargestId() + 1;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool SalesManager::saveSales(std::string saveFileName)
{
    try {
        saveToFile(saveFileName, sales);
        return true;
    }
    catch (...) {
        return false;
    }
}
#endif