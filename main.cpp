#include <iostream>
#include "Vector.h"
#include "SalesManager.h"
#include "ModuleSDK.h"

using namespace std;
Vector<string> splitInput(string input) {
    Vector<string> result = Vector<string>();
    string currentToken = "";
    bool insideQuotes = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (c == '\"') {
            // Toggle the state when we hit a quote
            insideQuotes = !insideQuotes;
            // Note: We don't add the " character itself to the token
        } 
        else if (c == ' ' && !insideQuotes) {
            // If it's a space and we aren't in quotes, the word is finished
            if (!currentToken.empty()) {
                result.push(currentToken);
                currentToken = "";
            }
        } 
        else {
            // Otherwise, keep building the current word
            currentToken += c;
        }
    }

    // Don't forget to add the very last token
    if (!currentToken.empty()) {
        result.push(currentToken);
    }

    return result;
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
        if (tokens[0] == "exit")
            isRunning = false;
        else if (commands.count(tokens[0]))
            commands[tokens[0]](sm, tokens);
        else
            cout << "Unknown command.\n";
    }

    return 0;
}