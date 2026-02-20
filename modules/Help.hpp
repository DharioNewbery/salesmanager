#ifndef HELP_HPP
#define HELP_HPP
#include "../src/Command.hpp"

class HelpCommand: public Command {
public:
    std::string getHelpMessage() const override {
    return "Este comando exibe informações de ajuda sobre os comandos disponíveis. Ele pode ser usado de duas formas:\n\
1. help: exibe uma lista de todos os comandos disponíveis com uma breve descrição de cada um.\n\
2. help <command>: exibe uma descrição detalhada do comando especificado, incluindo sua sintaxe e exemplos de uso.\n\
Exemplo de uso: help add (exibe informações detalhadas sobre o comando 'add').";}

    void execute(SalesManager& sm, Vector<std::string> args) override {
        if (args.getSize() == 0) {
            std::cout << "Comandos disponiveis:\n";
            for (const auto& pair : CommandRegistry::getCommands()) {
                std::cout << pair.first << "\n";
            }
            std::cout << "Digite 'help <command>' para mais detalhes sobre um comando.\n";
            return;
        }

        if (args.getSize() == 1) {
            const std::string& commandName = args[0];
            if (CommandRegistry::getCommands().count(commandName)) {
                std::cout << CommandRegistry::getCommands()[commandName]->getHelpMessage() << "\n";
            } else {
                std::cout << "comando desconhecido: " << commandName << "\n";
            }
        } else {
            std::cout << "Uso: help <command>. ex: 'help list'\n";
        }
    }
};

CommandRegistrator registerHelpCommand("help", new HelpCommand());

#endif