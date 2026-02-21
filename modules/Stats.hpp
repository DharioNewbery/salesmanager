#ifndef STATS_H
#define STATS_H

#include "../src/Command.hpp"

class StatsCommand : public Command {
private:
    void getStats(
        int& totalDeVendas, 
        int& valorArrecadado, 
        int& maiorVenda, 
        int& menorVenda,
        Vector<std::string>& produtos,
        Vector<double>& mediaPorProduto
    );

    Vector<Sale> m_sales = {};
public:

    std::string getHelpMessage() const override {
    return "Este comando gera um relatório de vendas. Ele pode ser usado da seguinte forma:\n\
1. stats: mostra dados de vendas, total vendidos por produto, maior e menor venda e a média de vendas.\n\
Exemplo de uso: stats";}

    Vector<Signature> getSignatures() const override {
        return {
            {} // stats
        };
    }

    void execute(SalesManager& sm, Vector<std::string> args) override {
        int allSales, total, biggestSale, minorSale;
        Vector<std::string> products;
        Vector<double> media;
        
        m_sales = sm.getSales();

        getStats(
            allSales,
            total,
            biggestSale,
            minorSale,
            products,
            media
        );

        if (allSales == 0) {
            std::cout << "Nenhuma venda registrada.\n";
            return;
        }

        std::cout << "===== Estatísticas =====\n";
        std::cout << "Total de vendas: " << allSales << "\n";
        std::cout << "Valor total arrecadado: R$" << price::toPrice(total) << "\n";
        std::cout << "Maior venda: R$" << price::toPrice(biggestSale) << "\n";
        std::cout << "Menor venda: R$" << price::toPrice(minorSale) << "\n";

        std::cout << "\n--- Média por Produto ---\n";
        for (int i = 0; i < products.getSize(); i++) {
            std::cout << products[i]
                      << " -> R$" << price::toPrice(media[i])
                      << "\n";
        }

        m_sales = {};
    }
};

void StatsCommand::getStats(
    int& allSales, 
    int& total, 
    int& biggestSale, 
    int& minorSale,
    Vector<std::string>& products,
    Vector<double>& mediaByProducts
) {
    
    allSales = m_sales.getSize();
    total = 0;
    products = Vector<std::string>();
    mediaByProducts = Vector<double>();

    biggestSale = m_sales[0].price;
    minorSale = m_sales[0].price;

    
    // Acumuladores; 
    Vector<int> sumByProduct;
    Vector<int> quantityPerProduct;
    // esse loop soma o valor total por cada produto;
    for (int i = 0; i < allSales; i++) {

        int currentPrice = m_sales[i].price;
        std::string currentItem = m_sales[i].item;

        total = total + currentPrice;

        if (currentPrice > biggestSale)
            biggestSale = currentPrice;

        if (currentPrice < minorSale)
            minorSale = currentPrice;
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

CommandRegistrator statsCommandRegistrator("stats", new StatsCommand());

#endif