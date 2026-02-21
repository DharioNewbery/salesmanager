#ifndef SORT_H
#define SORT_H

#include "../src/Command.hpp"

//class SortCommand: public Command {
//public:
//
//    void execute(SalesManager& sm, Vector<std::string> args) override {
//        if (sm.sortByPrice())
//            std::cout << "Vendas ordenadas por preço com sucesso!\n";
//        else
//            std::cout << "Não há vendas para ordenar.\n";
//    }
//};

class SortByCommand: public Command {
public:

std::string getHelpMessage() const override {
    return "Este comando ordena todos os dados armazenados na memória. Ele pode ser usado de 5 formas:\n\
1. sortBy id <up/down>: Ordena todos as vendas pelo identificador.\n\
2. sortBy price <up/down>: Ordena todos as vendas por preço.\n\
3. sortBy buyer <up/down>: Ordena todos os vendas por ordem alfabética do comprador.\n\
4. sortBy item <up/down>: Ordena todos os produtos por ordem alfabética do item.\n\
5. sortBy date <up/down>: Ordena todos os produtos por data.\n\
<up> ordem crescente | <down> ordem decrescente\n\
Exemplo de uso: sortBy price up";}

    Vector<Signature> getSignatures() const override {
        return {
            {ArgType::STRING, ArgType::STRING} // sortBy <type> <order>
        };
    }

    void execute(SalesManager& manager, Vector<std::string> args) override {

        std::string sort = args[0];
        std::string ordem = "asc";

        if (args.getSize() >= 2)
            ordem = args[1];

        if (manager.sortBy(sort, ordem)) {
            std::cout << "Vendas ordenadas por " << sort
                    << " (" << ordem << ") com sucesso!\n";
        }
        else {
            std::cout << "Não foi possível ordenar.\n";
        }
    }
};

CommandRegistrator registerSortByCommand("sortBy", new SortByCommand());
//CommandRegistrator registerSortCommand("sort", new SortCommand());

#endif   