#ifndef MODULE_SDK_H
#define MODULE_SDK_H

#include <string>
#include <functional>
#include <map>
#include <iostream>
#include "SalesManager.h"
#include "SafeConversion.hpp"

class SalesManager;

typedef std::function<void(SalesManager&, Vector<std::string>)> CommandFunc;

class ModuleRegistry {
public:
    
    static std::unordered_map<std::string, std::string>& getHelpMessages() {
        static std::unordered_map<std::string, std::string> helpMessages;
        return helpMessages;
    }

    struct HelpRegistrator {
        HelpRegistrator(const char* name, const char* message) {
            std::cout << "help message registered for command '" << name << "'\n";
            ModuleRegistry::getHelpMessages()[name] = message;
        }
    };

    static std::unordered_map<std::string, CommandFunc>& getCommands() {
        static std::unordered_map<std::string, CommandFunc> commands;
        return commands;
    }

    struct CommandRegistrator {
        CommandRegistrator(std::string name, CommandFunc func) {
            std::cout << "new command added: " << name << std::endl;
            ModuleRegistry::getCommands()[name] = func;
        }
    };
};

#define REGISTER_HELP_MESSAGE(name, message, func) \
    static ModuleRegistry::HelpRegistrator global_reg_help_##func(name, message);

#define REGISTER_COMMAND(name, func) \
    static ModuleRegistry::CommandRegistrator global_reg_##func(name, func);
#endif