#ifndef SALES_MANAGER_H
#define SALES_MANAGER_H

#include "Vector.h"
#include "Sale.h"
#include "Fileio.hpp"

class SalesManager
{
private:
    Vector<Sale> m_sales;
    int m_nextId;
    int getLargestId();
public:
    SalesManager();
    ~SalesManager();

    Sale getSaleByIndex (int index);
    int getSalesAmmount();
    bool addSale(Sale sale);
    bool removeSaleById(const int id);
    bool updateSale(Sale sale);
    void listSales(const int start = 0, int end = INT_MAX);
    bool loadSales(std::string filename, bool append = false);
    bool saveSales(std::string filename, bool override = false);
    void quickSort(int idStart, int idEnd);
    int  partition(int idStart, int idEnd);
    bool sortByPrice();
    // Aqui a função ela vai reescrever na própria variavel os valores , então n retorna nada. 
    void getStats(
        int& totalDeVendas, 
        int& valorArrecadado, 
        int& maiorVenda, 
        int& menorVenda,
        Vector<std::string>& produtos,
        Vector<double>& mediaPorProduto
    );
  
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

int SalesManager::getLargestId()
{
    int biggest = 0;
    for (int i = 0; i < m_sales.getSize(); i++)
        biggest = (biggest < m_sales[i].id)? m_sales[i].id : biggest;
    return biggest;
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

void SalesManager::listSales(const int start, int end) {

    if (end == INT_MAX) end = m_sales.getSize();
    
    for (int i = start; i < end; i++)
        m_sales[i].display();
    
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
            m_nextId = getLargestId() + 1;
        }
        return true;
    } catch (...) { return false; }
}

bool SalesManager::saveSales(std::string filename, bool override)
{
    try {
        if (override) { loadSales(filename, true); }
        saveToFile(filename, m_sales);
        return true;
    }
    catch (...) { return false; }
}

void SalesManager::getStats(
    int& totalDeVendas, 
    int& valorArrecadado, 
    int& maiorVenda, 
    int& menorVenda,
    Vector<std::string>& produtos,
    Vector<double>& mediaPorProduto
) {
    // verifica o total de vendas efetuadas, eu pensei em usar o sales.id mas ai teria que ficar verificando o maior id, e se tiver um id faltando por conta de uma venda removida, ia dar problema. Então é mais seguro usar o getSize na classe inteira mesmo;
    totalDeVendas = m_sales.getSize();
    valorArrecadado = 0;
    // aqui eu tive que criar a variavel de produtos e media, pq quando eu rodava o comando aparentemente ficava os valores anteriores , ai eu precisava resetar esses vetores(se não a média dava errada), mas n conseguir pensar numa forma melhor (fora rodar um vetor vazio toda vez que chamar o comando stats); 
    produtos = Vector<std::string>();
    mediaPorProduto = Vector<double>();
    // aqui só verifica se tem ou n vendas, eu tava colocando output aqui , mas já tirei , pq aqui só fica a lógica interna né? 
    if (totalDeVendas == 0) {
        maiorVenda = 0;
        menorVenda = 0;
        return;
    }

    maiorVenda = m_sales[0].price;
    menorVenda = m_sales[0].price;

    // esses vetores aqui eu vou usar eles pela posição, então basicamente posições iguais = mesma informação;
    // são vetores acumuladores; -> senão , n tem média ; 
    Vector<int> somaPorProduto;
    Vector<int> quantidadePorProduto;
    // esse loop aqui é o que vai somar o meu valor total;
    for (int i = 0; i < totalDeVendas; i++) {

        int precoAtual = m_sales[i].price;
        std::string itemAtual = m_sales[i].item;

        valorArrecadado = valorArrecadado + precoAtual;

        if (precoAtual > maiorVenda)
            maiorVenda = precoAtual;

        if (precoAtual < menorVenda)
            menorVenda = precoAtual;
        // essa variável aqui ela serva pra identificar se algum produto já foi adicionado no vetor de produtos, sem isso aqui ficava adicionando o mesmo produto como se fosse um produto novo; 
        bool encontrado = false;
        // aqui caso o produto já tenha sido add anteriormente , ele somana num vetor específico daquele produto ( baseado n posição dele);
        for (int j = 0; j < produtos.getSize(); j++) {
            if (produtos[j] == itemAtual) {
                somaPorProduto[j] = somaPorProduto[j] + precoAtual;
                quantidadePorProduto[j]++;
                encontrado = true;
                // mn aqui eu fiquei em dúvido sobre esse break, pq a professora n gosta né ? 
                // mas se eu tirar esse break, o loop vai ficar comparando até o final o vetor com o item atual :/;
                break;
            }
        }
        // se for a primeira vez em que o produto aparece ele é adicionado no vetor de produtos, ai como vai ter algo no vetor agora , quando rodar dnv o loop , ele vai entrar no for de antes; 
        if (encontrado == false) {
            produtos.push(itemAtual);
            somaPorProduto.push(precoAtual);
            quantidadePorProduto.push(1);
        }
    }

    for (int i = 0; i < produtos.getSize(); i++) {
        mediaPorProduto.push(
            (double)somaPorProduto[i] / quantidadePorProduto[i]
        );
    }
}

#endif