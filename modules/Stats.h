#ifndef STATS_H
#define STATS_H

#include "../src/ModuleSDK.h"

void statsCommand(SalesManager& manager, Vector<std::string> args)
{
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
    std::cout << "Valor total arrecadado: $" << valorArrecadado << "\n";
    std::cout << "Maior venda: $" << maiorVenda << "\n";
    std::cout << "Menor venda: $" << menorVenda << "\n";

    std::cout << "\n--- Média por Produto ---\n";
    for (int i = 0; i < produtos.getSize(); i++) {
        std::cout << produtos[i]
                  << " → $" << media[i]
                  << "\n";
    }
}

REGISTER_COMMAND("stats", statsCommand);

#endif