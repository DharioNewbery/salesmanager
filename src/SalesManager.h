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
    bool updateSale(Sale sale);
    void listSales(const int start = 0, int end = INT_MAX);
    bool loadSales(std::string filename, bool append = false);
    bool saveSales(std::string filename, bool override = false);
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
    
    Sale mockSale = Sale();
    mockSale.id = id;
    int index = sales.find(mockSale);

    if (index == -1) return false;

    sales.remove(index);
    return true;
}

inline bool SalesManager::updateSale(Sale sale)
{
    int index = sales.find(sale); 
    if (index == -1) return false;

    sales.replace(index, sale);
    return true;
}

void SalesManager::listSales(const int start, int end) {

    if (end == INT_MAX) end = sales.getSize();
    
    for (int i = start; i < end; i++)
        sales[i].display();
    
}

bool SalesManager::loadSales(std::string filename, bool append = false)
{
    try {
        Vector<Sale> loadedData = loadFromFile(filename);
        
        if (append) {
            for (int i = 0; i < loadedData.getSize(); i++) {
                // Assign a NEW unique ID based on the CURRENT manager state
                loadedData[i].id = nextId++; 
                sales.push(loadedData[i]);
            }
        } else {
            sales = loadedData;
            nextId = getLargestId() + 1;
        }
        return true;
    } catch (...) { return false; }
}

bool SalesManager::saveSales(std::string filename, bool override = false)
{
    try {
        if (override) { loadSales(filename, true); }
        saveToFile(filename, sales);
        return true;
    }
    catch (...) { return false; }
}
#endif