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
    // aqui eu coloquei na private pq a função precisa de acesso ao vetor de vendar né , ai eu ns se eu colocar pra fora eu ia conseguir manipular o vetor;
    void quickSort(int id_start, int id_end);
    int partition(int id_start, int id_end);

public:
    SalesManager();
    ~SalesManager();

    bool addSale(Sale sale);
    bool removeSaleById(const int id);
    bool updateSale(Sale sale);
    void listSales(const int start = 0, int end = INT_MAX);
    bool loadSales(std::string filename, bool append = false);
    bool saveSales(std::string filename, bool override = false);
    // aqui a função que vai ser chamada pelo cliente; 
    void Sort_by_price();
};

// Aqui é a implementação do quicksort em sí; 
void SalesManager::quickSort(int id_start, int id_end)  // o int id_start e o int id_end são os indices do vetor, mas já estão sendo passados pelo sort_by_price; 
{
    if (id_start < id_end) {
        int pivo = partition(id_start, id_end);
        //vai ordenar tudo que é menor que o pivo a sua esquerda;
        quickSort(id_start, pivo - 1);
        // vai ordenar tudo que é maior que o pivo a sua direita;
        quickSort(pivo + 1, id_end);
    }
}

// agora a partição parte da partição que é chamada pelo quicksort; 
// o partition basicamente escolhe um pivo ( que é sempre o último elemento do vetor)
// ai ele vai jogando tudo que é maior que o pivo pra frente dele e tudo que é menor que o pivo vai pra trás; 
int SalesManager::partition(int id_start, int id_end) {
    // pivo_2 é o último elemento do vetor;
    int pivo_2 = sales[id_end].price;
    // i vai guardar a última posição em que o elemento é menor ou igual ao pivo_2;
    int i = id_start - 1;

    for (int j = id_start; j < id_end; j++) {
        // égua pprt aqui eu demorei muito pra entender que existe um VETOR do tipo sales kkkkkk ;
        // eu tava trocando só o sales.price , mas isso trocava só o preço da venda;
        // tipo o notebook que custa 2000 com uma geladeira que custa 3000, ai trocando só o sales.price, o notebook virava 3000 e a geladeira virava 2000, kkkkkkkkkkk;
        // até eu entender que sales é a uma struct; 
        // eu tinha que comparar um ATRIBUTO de sales ( o preço) com o pivo_2 , ai se for maior A POSIÇÃO da venda por completo é permutada; 
        // OBS: to escrevendo essa krlhada de comentário pq eu to me perdendo muito nesse código, depois pode apagar tudo :> ;
        
        // todos os elementos menores ou iguais ao pivo_2 ficam sempre a esquerda; 
        if (sales[j].price <= pivo_2) {
            i++;
            Sale aux = sales[i];
            sales[i] = sales[j];
            sales[j] = aux;
        }
    }
    // coloca o pivo_2 na posição correta;
    // já que i representa a posição do último elemento menor que o pivo, i+1 vai ser a posição do próprio pivo ;
    // ai isso vai ajudar na divisão do vetor em duas partes, com elementos menores ou iguais a esquerda e elemento maiores a direita;
    // ai quando ele retornar o i+1, ele tá retornando a posição do pivo, para que ele seja usado nos próximo quicksorts;
    // mn muito foda essa função; 
    Sale aux = sales[i + 1];
    sales[i + 1] = sales[id_end];
    sales[id_end] = aux;

    return i + 1;
}

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