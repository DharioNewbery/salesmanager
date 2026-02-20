#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <unordered_map>
#include <string>
#include <iostream>

#include "Utils.hpp"
#include "Vector.hpp"
#include "SalesManager.hpp"
#include "SafeConversion.hpp"

class Command {
public:
    virtual std::string getHelpMessage() const { return "Nenhuma mensagem de ajuda disponivel para este comando"; }
    virtual void execute(SalesManager& sm, Vector<std::string> args) = 0;
};

class CommandRegistry {
public:
    static std::unordered_map<std::string, Command*>& getCommands() {
        static std::unordered_map<std::string, Command*> commands;
        return commands;
    }
};

struct CommandRegistrator {
    CommandRegistrator(std::string name, Command* cmd) {
        CommandRegistry::getCommands()[name] = cmd;
    }
}; 

#endif