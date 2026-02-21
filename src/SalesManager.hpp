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
    void quickSort(int idStart, int idEnd);
    int  partition(int idStart, int idEnd);
    bool sortByPrice();

    void searchBy(std::string searchBy, std::string item);
    bool sortBy(std::string sortBy, std::string ordem = "asc");

    // A função reescreve na própria variável os valores;
    void getStats(
        int& totalDeVendas, 
        int& valorArrecadado, 
        int& maiorVenda, 
        int& menorVenda,
        Vector<std::string>& produtos,
        Vector<double>& mediaPorProduto
    );
    Vector<Sale> getSales() { return m_sales; }
  
};

bool SalesManager::sortByPrice() {
    if (m_sales.getSize() <= 1) {
        return false;
    }
     quickSort(0, m_sales.getSize() - 1);
    return true;
}

 
void SalesManager::quickSort(int idStart, int idEnd)  
{
    if (idStart < idEnd) {
        int pivo = partition(idStart, idEnd);
      
        quickSort(idStart, pivo - 1);
        
        quickSort(pivo + 1, idEnd);
    }
}

 
int SalesManager::partition(int idStart, int idEnd) {
    
    int pivo_2 = m_sales[idEnd].price;
    
    int i = idStart - 1;

    for (int j = idStart; j < idEnd; j++) {
        
        if (m_sales[j].price <= pivo_2) {
            i++;
            Sale aux = m_sales[i];
            m_sales[i] = m_sales[j];
            m_sales[j] = aux;
        }
    }
    
    Sale aux = m_sales[i + 1];
    m_sales[i + 1] = m_sales[idEnd];
    m_sales[idEnd] = aux;

    return i + 1;
}

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

void SalesManager::getStats(
    int& allSales, 
    int& total, 
    int& maijorSales, 
    int& minorSales,
    Vector<std::string>& products,
    Vector<double>& mediaByProducts
) {
    
    allSales = m_sales.getSize();
    total = 0;
 ; 
    products = Vector<std::string>();
    mediaByProducts = Vector<double>();
    // só verifica se tem ou n vendas; 
    if (allSales == 0) {
        maijorSales = 0;
        minorSales = 0;
        return;
    }

    maijorSales = m_sales[0].price;
    minorSales = m_sales[0].price;

    
    // são vetores acumuladores; 
    Vector<int> sumByProduct;
    Vector<int> quantityPerProduct;
    // esse loop -> soma o valor total;
    for (int i = 0; i < allSales; i++) {

        int currentPrice = m_sales[i].price;
        std::string currentItem = m_sales[i].item;

        total = total + currentPrice;

        if (currentPrice > maijorSales)
            maijorSales = currentPrice;

        if (currentPrice < minorSales)
            minorSales = currentPrice;
        // essa variável ela serva pra identificar se algum produto já foi adicionado no vetor de produtos;
        bool find = false;
        // caso o produto já tenha sido add anteriormente , ele somana num vetor específico daquele produto ( baseado n posição dele);
        for (int j = 0; j < products.getSize(); j++) {
            if (products[j] == currentItem) {
                sumByProduct[j] = sumByProduct[j] + currentPrice;
                quantityPerProduct[j]++;
                find = true;
                break;
            }
        }
        // se for a primeira vez em que o produto aparece ele é adicionado no vetor de produtos, ai como vai ter algo no vetor agora , quando rodar dnv o loop , ele vai entrar no for de antes; 
        if (find == false) {
            products.push(currentItem);
            sumByProduct.push(currentPrice);
            quantityPerProduct.push(1);
        }
    }

    for (int i = 0; i < products.getSize(); i++) {
        mediaByProducts.push(
            (double)sumByProduct[i] / quantityPerProduct[i]
        );
    }
}
void SalesManager::searchBy(std::string searchBy, std::string item)
{
    for (int i = 0; i < m_sales.getSize(); i++)
    {
        bool checker = false;

        if (searchBy == "item")
            checker = (m_sales[i].item.find(item) != std::string::npos);

        else if (searchBy == "comprador")
            checker = (m_sales[i].buyer.find(item) != std::string::npos);

        if (checker)
        {
            print::printSale(m_sales[i]);
        }
    }
}

bool SalesManager::sortBy(std::string sortBy, std::string ordem)
{
    if (m_sales.getSize() <= 1)
        return false;

    bool toUp = (ordem != "desc");
    //loop principal ;
    for (int i = 0; i < m_sales.getSize() - 1; i++) {
        //loop secundário só pra fazer as comparações; 
        for (int j = i + 1; j < m_sales.getSize(); j++) {

            bool needTrade = false;

            if (sortBy == "data") {
                if (toUp)
                    needTrade = m_sales[i].date > m_sales[j].date;
                else
                    needTrade = m_sales[i].date < m_sales[j].date;
            }

            else if (sortBy == "id") {
                if (toUp)
                    needTrade = m_sales[i].id > m_sales[j].id;
                else
                    needTrade = m_sales[i].id < m_sales[j].id;
            }

            else if (sortBy == "item") {
                if (toUp)
                    needTrade = toLower(m_sales[i].item) > toLower(m_sales[j].item);
                else
                    needTrade = toLower(m_sales[i].item) < toLower(m_sales[j].item);
            }

            else if (sortBy == "comprador") {
                if (toUp)
                    needTrade = toLower(m_sales[i].buyer) > toLower(m_sales[j].buyer);
                else
                    needTrade = toLower(m_sales[i].buyer) < toLower(m_sales[j].buyer);
            }

            else if (sortBy == "preço") {
                if (toUp)
                    needTrade = m_sales[i].price > m_sales[j].price;
                else
                    needTrade = m_sales[i].price < m_sales[j].price;
            }

            if (needTrade) {
                Sale aux = m_sales[i];
                m_sales[i] = m_sales[j];
                m_sales[j] = aux;
            }
        }
    }

    return true;
}


#endif