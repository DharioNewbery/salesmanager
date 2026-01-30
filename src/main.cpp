#include <iostream>
#include "Vector.h"
#include "SalesManager.h"
#include "ModuleSDK.h"
#include "inputHandler.h"

using namespace std;

int main () {
    auto& commands = ModuleRegistry::getCommands();
    auto& helpMessages = ModuleRegistry::getHelpMessages();
    
    SalesManager sm = SalesManager();

    bool isRunning = true;
    Vector<string> tokens;
    string input;
    
    while (isRunning) {
        getline(cin, input);
        tokens = splitInput(input);
                
        
        if (tokens.getSize() == 0)
            continue; // Guard for empty command lines;
        
        if (tokens[0] == "exit") {
            isRunning = false;
            continue;
        }

        if (commands.count(tokens[0]) && tokens.getSize() == 2 && (tokens[1] == "--help" || tokens[1] == "--h")) {
            std::cout << helpMessages[tokens[0]] << std::endl;
            continue;
        }

        if (commands.count(tokens[0]))
            commands[tokens[0]](sm, tokens);
        else
            cout << "Unknown command.\n";
    }

    return 0;
}