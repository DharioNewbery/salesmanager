
#include "Main.hpp"

int main() {
    SalesManager sm;
    std::string input;
    
    std::cout << "SalesManager CLI - Digite 'exit' para sair ou 'help' para ajuda e comandos disponíveis.\n";

    CommandDispatcher::dispatch("load test_file.txt", sm);

    bool isRunning = true;
    while (isRunning) {
        
        std::cout << "> ";

        // Sai do loop se o usuario digitar "exit" ou se ocorrer um EOF (Ctrl+D)
        if (!std::getline(std::cin, input) || input == "exit") {
            isRunning = false;
            // Uso de continue para evitar processamento adicional após o comando de saída ou EOF
            // e aumentar a legibilidade do código, diminuindo um nível de indentação.
            continue; 
        }

        try {
            CommandDispatcher::dispatch(input, sm);
        } catch (const std::exception& e) {
            std::cerr << "ocorreu um erro durante execução do comando: " << e.what() << std::endl;
        }
    }

    std::cout << "Encerrando aplicação..." << std::endl;
    return 0;
}