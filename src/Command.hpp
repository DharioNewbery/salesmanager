#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <unordered_map>
#include <string>
#include <iostream>

#include "Utils.hpp"
#include "Vector.hpp"
#include "SalesManager.hpp"

enum class ArgType {
    STRING,
    INT,
    DATE,
    MONEY,
    FLAG
};

using Signature = Vector<ArgType>;

class Command {
public:
    virtual std::string getHelpMessage() const { return "Nenhuma mensagem de ajuda disponivel para este comando"; }
    virtual Vector<Signature> getSignatures() const { return {}; }

    virtual void execute(SalesManager& sm, Vector<std::string> args) = 0;

    virtual ~Command() = default;
};

class CommandRegistry {
public:
    static std::unordered_map<std::string, Command*>& getCommands() {
        static std::unordered_map<std::string, Command*> commands;
        return commands;
    }

    ~CommandRegistry() {
        for (auto& pair : getCommands()) {
            delete pair.second;
        }
    }
};

struct CommandRegistrator {
    CommandRegistrator(std::string name, Command* cmd) {
        CommandRegistry::getCommands()[name] = cmd;
    }
    
    ~CommandRegistrator() = default;
};

class CommandDispatcher {
public:
    static void dispatch(std::string input, SalesManager& sm) {
        Vector<std::string> tokens = input::splitInput(input);
        
        if (tokens.getSize() == 0) return;

        std::string cmdName = tokens[0];
        auto& commandMap = CommandRegistry::getCommands();

        if (commandMap.find(cmdName) == commandMap.end()) {
            std::cout << "Comando desconhecido: " << cmdName << "\n";
            return;
        }

        Command* cmd = commandMap[cmdName];
        tokens.remove(0); // Remove o nome do comando, restam os argumentos

        if (validate(cmd, tokens)) {
            cmd->execute(sm, tokens);
        } else {
            std::cout << "Erro: Argumentos invalidos.\n" << cmd->getHelpMessage() << "\n";
        }
    }

private:

    static bool tryConvert(const std::string& arg, ArgType t) {
        bool isValid = true;
        switch (t)
        {
            case ArgType::STRING: break;
            case ArgType::INT:
                try { std::stoi(arg); }
                catch (...) { isValid = false; }
                break;
            case ArgType::DATE:
                isValid = date::isFormatValid(arg);
                break;
            case ArgType::MONEY:
                try { std::stoul(arg); }
                catch (...) { isValid = false; }
                break;
            case ArgType::FLAG:
                isValid = flag::isFormatValid(arg);
                break;
        }
        return isValid;
        
    }
    static bool validate(Command* cmd, Vector<std::string> args) {
        auto signatures = cmd->getSignatures();
        if (signatures.isEmpty()) return true; // Se não definiu assinaturas, assume livre
        
        for (int i = 0; i < signatures.getSize(); i++) {
            Signature sig = signatures[i];
            int sigSize = sig.getSize();
         
            if (sig.getSize() == args.getSize()) {
                
                if (sigSize == 0) return true; // Assinaturas vazias.


                for (int j = 0; j < sigSize; j++) {
                    if (!tryConvert(args[j], sig[j])) return false;
                }
                return true;
            }
        }
        return false;
    }
};

#endif