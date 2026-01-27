#ifndef SALES_MANAGER_H
#define SALES_MANAGER_H

#include "Vector.h"
#include "Sale.h"

class SalesManager
{
private:
    Vector<Sale> sales;
    int nextId;
public:
    SalesManager();
    ~SalesManager();

    bool addSale(Sale sale);
    bool removeSaleById(const int id);
    void listSales(const int start = 0, int end = INT_MAX);
};

SalesManager::SalesManager(): sales(), nextId(1) {}
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

#endif