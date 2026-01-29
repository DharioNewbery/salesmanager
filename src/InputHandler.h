#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Vector.h"
#include "string"

Vector<std::string> splitInput(std::string input) {
    Vector<std::string> result = Vector<std::string>();
    std::string currentToken = "";
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

#endif