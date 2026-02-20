
#include "Main.hpp"

int main () {
    auto& commandMap = CommandRegistry::getCommands();

    SalesManager sm = SalesManager();

    bool isRunning = true;
    Vector<std::string> tokens;
    std::string input;
    
    while (isRunning) {
        getline(std::cin, input);
        tokens = input::splitInput(input);
        
        if (tokens.getSize() == 0)
            continue; // Guard for empty command lines;
        
        if (tokens[0] == "exit") {
            isRunning = false;
            continue; // Exit the loop and end the program
        }

        // Checks if command exists and executes it, passing the SalesManager and the arguments
        if (commandMap.count(tokens[0])) { 
            auto& command = commandMap[tokens[0]];
            tokens.remove(0); // Remove the command name from the arguments list
            command->execute(sm, tokens);
            // commands[tokens[0]](sm, tokens);
        }
        else
            std::cout << "Unknown command.\n";
    }

    return 0;
}