#ifndef SEARCH_H
#define SEARCH_H

#include "../src/Command.hpp"

class searchCommand : public Command{
public:
    void execute(SalesManager& manager, Vector<std::string> args) override
    {
        if (args.getSize() < 2)
        {
            std::cout << "Precisa de: search <oQueBusca= item ou comprador> <parametro = nomeDoItem|nomeDoComprador>\n";
            return;
    }

    std::string search = args[0];
    std::string item = args[1];

        manager.searchBy(search, item);
    }
};

CommandRegistrator registerSearchCommand("search", new searchCommand());

#endif