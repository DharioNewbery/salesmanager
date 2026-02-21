#ifndef STATS_H
#define STATS_H

#include "../src/Command.hpp"

class StatsCommand : public Command {
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

    void execute(SalesManager& manager, Vector<std::string> args) override {
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