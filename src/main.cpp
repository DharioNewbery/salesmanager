// ========== SALESMANAGER ==========
// Alunos: Dhario Newbery Evangelista
//         Khey Niwa

//   Tema: Vendas

#include "Main.hpp"

int main() {
    SalesManager sm;
    std::string input;
    
    std::cout << "SalesManager CLI - Digite 'exit' para sair ou 'help' para ajuda e comandos disponíveis.\n";

    CommandDispatcher::dispatch("load test_file.txt", sm);

    bool isRunning = true;
    while (isRunning) {
        
        std::cout << "> ";

        // exits the loop if user types "exit" or EOF occurs (Ctrl+D)
        if (!std::getline(std::cin, input) || input == "exit") {
            isRunning = false;
            // continue for avoiding reduntand message before exiting loop.
            // improves code readability and structure. Be Kind, prof. Paula ;-;
            continue; 
        }

        try { // Safe guards the command execution, even if exception occurs, the code will not stop.
            CommandDispatcher::dispatch(input, sm);
        } catch (const std::exception& e) {
            std::cerr << "ocorreu um erro durante execução do comando: " << e.what() << std::endl;
        }
    }

    std::cout << "Encerrando aplicação..." << std::endl;
    return 0;
}