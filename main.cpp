#include <iostream>
#include "Vector.h"
#include "SalesManager.h"
#include "ModuleSDK.h"
#include "inputHandler.h"

using namespace std;

void printV(Vector<int> a) {
    for(int i = 0; i < a.getSize(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main () {
    auto& commands = ModuleRegistry::getCommands();
    SalesManager sm = SalesManager();
    sm.loadSales();

    bool isRunning = true;
    Vector<string> tokens;
    string input;
    
    while (isRunning) {
        getline(cin, input);
        tokens = splitInput(input);
        
        if (tokens[0] == "exit") {
            isRunning = false;
            continue;
        }
        if (commands.count(tokens[0]))
            commands[tokens[0]](sm, tokens);
        else
            cout << "Unknown command.\n";
    }

    return 0;
}