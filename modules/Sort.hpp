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

class SortByCommand: public Command {
public:
    void execute(SalesManager& manager, Vector<std::string> args) override {
        if (args.getSize() < 1) {
            std::cout << "Precisa de usar: sort <oQueVaiSerOrdenado> , Ordem: (asc/desc)\n";
            return;
        }

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
CommandRegistrator registerSortCommand("sort", new SortCommand());

#endif   