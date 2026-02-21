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
    
    void execute(SalesManager& sm, Vector<std::string> args) override
    {
        Vector<Sale> sales = sm.getSales();
        Vector<Sale> result = {};

        std::string search = toLower(args[0]);
        std::string query = toLower(args[1]);

        if (search != "item" && search != "buyer") {
            std::cout << "tipo incorreto: '" << search << "'\n";
            return;
        }

        for (int i = 0; i < sales.getSize(); i++)
        {
            bool exists = false;

            if (search == "item")
                exists = (toLower(sales[i].item).find(query) != std::string::npos);

            else if (search == "buyer")
                exists = (toLower(sales[i].buyer).find(query) != std::string::npos);

            if (exists)
            {
                result.push(sales[i]);
            }
        }

        print::printSalesList(result);
    }
};

CommandRegistrator registerSearchCommand("search", new searchCommand());

#endif