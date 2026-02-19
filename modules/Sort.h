#ifndef SORT_H
#define SORT_H

#include "../src/ModuleSDK.h" 

void sortCommand(SalesManager& manager, Vector<std::string> args) {
    
    if (manager.sortByPrice()) {
        std::cout << "Vendas ordenadas por preço com sucesso!\n";
    }
    else {
        std::cout << "Não há vendas para ordenar.\n";
    }
}

REGISTER_COMMAND("sort", sortCommand );


#endif   