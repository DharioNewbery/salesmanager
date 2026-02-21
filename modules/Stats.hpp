#ifndef STATS_H
#define STATS_H

#include "../src/Command.hpp"

class StatsCommand : public Command {
public:
    void execute(SalesManager& manager, Vector<std::string> args) override {
    // declaro a variavel aqui fora do getStats, pq como a função getStats ela reescreve os valores, eu preciso que elas existam antes de chamar a função, se n da erro de variavel não declarada;
        int allSales, total, maijorSale, minorSale;
        Vector<std::string> products;
        Vector<double> media;
       
        manager.getStats(
            allSales,
            total,
            maijorSale,
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
        std::cout << "Valor total arrecadado: $" << price::toPrice(total) << "\n";
        std::cout << "Maior venda: $" << price::toPrice(maijorSale) << "\n";
        std::cout << "Menor venda: $" << price::toPrice(minorSale) << "\n";

        std::cout << "\n--- Média por Produto ---\n";
        for (int i = 0; i < products.getSize(); i++) {
            std::cout << products[i]
                    << " -> $" << price::toPrice(media[i])
                    << "\n";
        }
    }
};

CommandRegistrator statsCommandRegistrator("stats", new StatsCommand());

#endif