#ifndef SORT_H
#define SORT_H

#include "../src/Command.hpp"

class SortCommand: public Command {
public:
    void execute(SalesManager& sm, Vector<std::string> args) override {
        if (sm.sortByPrice())
            std::cout << "Vendas ordenadas por preço com sucesso!\n";
        else
            std::cout << "Não há vendas para ordenar.\n";
    }
};

CommandRegistrator registerSortCommand("sort", new SortCommand());

#endif   