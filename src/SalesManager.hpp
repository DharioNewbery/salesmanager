#ifndef SALES_MANAGER_H
#define SALES_MANAGER_H

#include "Vector.hpp"
#include "Sale.hpp"
#include "Fileio.hpp"
#include <climits>

std::string toLower(std::string str){
    for (int i = 0; i < str.size(); i++)
        str[i] = std::tolower(str[i]);
    return str;
}

class SalesManager
{
private:
    Vector<Sale> m_sales;
    int m_nextId;
    int getBiggestId();
public:
    SalesManager();
    ~SalesManager();

    Sale getSaleByIndex (int index);
    int getSalesAmmount();
    bool addSale(Sale sale);
    bool removeSaleById(const int id);
    bool updateSale(Sale sale);
    bool loadSales(std::string filename, bool append = false);
    bool saveSales(std::string filename, bool override = false);
    void flush();
    Vector<Sale> getSales() { return m_sales; }
    void setSales(Vector<Sale> sales) {m_sales = sales; }
};

int SalesManager::getBiggestId()
{
    return salesManagerUtils::getBiggestId(m_sales);
}

SalesManager::SalesManager() : m_sales(), m_nextId(1) {}
SalesManager::~SalesManager() {}

inline Sale SalesManager::getSaleByIndex(int index)
{
    return m_sales[index];
}

inline int SalesManager::getSalesAmmount()
{
    return m_sales.getSize();
}

bool SalesManager::addSale(Sale sale) {
    sale.id = m_nextId;
    m_sales.push(sale);
    m_nextId++;
    return true;
}

bool SalesManager::removeSaleById(const int id) {
    
    Sale mockSale = Sale();
    mockSale.id = id;
    int index = m_sales.find(mockSale);

    if (index == -1) return false;

    m_sales.remove(index);
    return true;
}

inline bool SalesManager::updateSale(Sale sale)
{
    int index = m_sales.find(sale); 
    if (index == -1) return false;

    m_sales.replace(index, sale);
    return true;
}

bool SalesManager::loadSales(std::string filename, bool append)
{
    try {
        Vector<Sale> loadedData = loadFromFile(filename);
        
        if (append) {
            for (int i = 0; i < loadedData.getSize(); i++) {
                // Assign a NEW unique ID based on the CURRENT manager state
                loadedData[i].id = m_nextId++; 
                m_sales.push(loadedData[i]);
            }
        } else {
            m_sales = loadedData;
            m_nextId = getBiggestId() + 1;
        }
        return true;
    } catch (...) { return false; }
}

void SalesManager::flush()
{
    m_sales = Vector<Sale>();
    m_nextId = 1;
}

bool SalesManager::saveSales(std::string filename, bool append)
{

    try {
        Vector<Sale> loadedData;

        if (append) {
            loadedData = loadFromFile(filename);
            int largestId = salesManagerUtils::getBiggestId(loadedData);

            for (int i = 0; i < m_sales.getSize(); i++) {
                Sale currentSale = m_sales[i];
                currentSale.id = largestId + 1;
                loadedData.push(currentSale);
                largestId++;
            }
        } else {
            loadedData = m_sales;
        }

        saveToFile(filename, loadedData);
    } catch (...) { return false; }
    return true;
}

#endif