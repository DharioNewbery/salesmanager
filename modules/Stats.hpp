#ifndef STATS_H
#define STATS_H

#include "../src/Command.hpp"

class StatsCommand : public Command {
public:
    void execute(SalesManager& manager, Vector<std::string> args) override {
    // declaro a variavel aqui fora do getStats, pq como a função getStats ela reescreve os valores, eu preciso que elas existam antes de chamar a função, se n da erro de variavel não declarada;
        int totalDeVendas, valorArrecadado, maiorVenda, menorVenda;
        Vector<std::string> produtos;
        Vector<double> media;
        // ai eu chamo a função; 
        manager.getStats(
            totalDeVendas,
            valorArrecadado,
            maiorVenda,
            menorVenda,
            produtos,
            media
        );

        if (totalDeVendas == 0) {
            std::cout << "Nenhuma venda registrada.\n";
            return;
        }

        std::cout << "===== Estatísticas =====\n";
        std::cout << "Total de vendas: " << totalDeVendas << "\n";
        std::cout << "Valor total arrecadado: $" << price::toPrice(valorArrecadado) << "\n";
        std::cout << "Maior venda: $" << price::toPrice(maiorVenda) << "\n";
        std::cout << "Menor venda: $" << price::toPrice(menorVenda) << "\n";

        std::cout << "\n--- Média por Produto ---\n";
        for (int i = 0; i < produtos.getSize(); i++) {
            std::cout << produtos[i]
                    << " -> $" << price::toPrice(media[i])
                    << "\n";
        }
    }
};

CommandRegistrator statsCommandRegistrator("stats", new StatsCommand());

#endif