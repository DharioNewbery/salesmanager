#ifndef SORT_H
#define SORT_H

#include "../src/ModuleSDK.h" 
// ela vai ser chamada para ordenar as vendas por preço. ela verifica se o vetor de vendas tem 0 ou 1 elemento, e se tiver, ela n faz nada. caso contrário, ela chama o quicksort passando o índice do primeiro e do último elemento do vetor. depois, se o vetor tiver 0 elementos, ela avisa que n tem vendas para ordenar (OBS sort_by_price chama o quicksorte e o quick sort vai chamar o patition, pq o partition é o auxiliar do quicksort;)
void SalesManager::Sort_by_price() {
    if (sales.getSize() <= 1) {
    std::cout << "Nada para ordenar.\n";
    return;
}
    // ai o quicksort que é uma função que precisa do vetor de vendas eu deixei no arquivo de salemanager mesmo; 
    quickSort(0, sales.getSize() - 1); // se tiver algo pra ordenar, ele chama o quicksort passando o índice do primeiro e do último elemento. ( que é o low e o high)

}

// chamada da função 
// aqui sinceramente falando eu não faço ideia do que tá acontecendo, tu me explicou o a estrutra , mas eu ns como ela roda por trás 
// então eu só dei cntrl C e cntrl V , ai qualquer coisa se me fala se tem algo de errado; 
void sortCommand(SalesManager& manager, Vector<std::string> args) {
    
    // aqui eu coloquei só a chamada da função e uma msg , que como é um output, ele tem que tá aqui e n no salesmanager né ? 
    manager.Sort_by_price();
    std::cout << "Vendas ordenadas por preço com sucesso!\n";
}


// void sortCommand(SalesManager& manager, Vector<std::string> args) , obrigatório -> cadastro de comando (função principal ). 


REGISTER_COMMAND("sort", sortCommand );


#endif   