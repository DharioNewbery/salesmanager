#ifndef SORT_H
#define SORT_H

#include "../src/ModuleSDK.h" 
bool SalesManager::sortByPrice() {
    if (sales.getSize() <= 1) {
        return false;
    }
     quickSort(0, sales.getSize() - 1);
    return true;
}

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