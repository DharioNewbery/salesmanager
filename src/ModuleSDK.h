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
    
    static std::map<std::string, CommandFunc>& getCommands() {
        static std::map<std::string, CommandFunc> commands;
        return commands;
    }

    struct Registrator {
        Registrator(std::string name, CommandFunc func) {
            std::cout << "new command added: " << name << std::endl;
            ModuleRegistry::getCommands()[name] = func;
        }
    };
};

#define REGISTER_COMMAND(name, func) \
    static ModuleRegistry::Registrator global_reg_##func(name, func);
#endif