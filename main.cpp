#include <iostream>
#include "Vector.h"
#include "SalesManager.h"
#include "ModuleSDK.h"

using namespace std;

int main () {
    auto& commands = ModuleRegistry::getCommands();
    SalesManager sm = SalesManager();
    
    bool isRunning = true;
    string input;
    
    while (isRunning) {
        getline(cin, input);
        if (commands.count(input))
            commands[input](sm);
        else
            cout << "Unknown command.\n";
    }

    return 0;
}