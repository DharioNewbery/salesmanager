#ifndef SEARCH_H
#define SEARCH_H

#include "../src/Command.hpp"

class searchCommand : public Command{
public:

    std::string getHelpMessage() const override {
    return "Este comando procura uma entrada pelo parametro informado. Ele pode ser usado de duas formas:\n\
1. search item <item>: exibe uma lista de todas as entradas que contém o produto especificado.\n\
2. search buyer <buyer>: exibe uma lista de todas as entradas que contém o comprador especificado.\n\
Exemplo de uso: search buyer \"Helena Duarte\"";}

    Vector<Signature> getSignatures() const override {
        return {
            {ArgType::STRING, ArgType::STRING} // search <type> <query>
        };
    }
    
    void execute(SalesManager& manager, Vector<std::string> args) override
    {
        std::string search = args[0];
        std::string item = args[1];
        manager.searchBy(search, item);
    }
};

CommandRegistrator registerSearchCommand("search", new searchCommand());

#endif