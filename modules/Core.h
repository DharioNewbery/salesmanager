#include "../ModuleSDK.h"

void listSales(SalesManager& sm, Vector<std::string> args) {
    int start = 0, end = INT_MAX;

    try
    {
        switch (args.getSize())
        {
        case 2:
            start = std::stoi(args[1]);
            break;
        case 3:
            start = std::stoi(args[1]);
            end = std::stoi(args[2]);
            break;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    sm.listSales(start, end);
}

void loadSales(SalesManager& sm, Vector<std::string> args) {
    std::cout << "loading files...\n";
    sm.loadSales();
    std::cout << "files loaded!\n";

}

void saveSales(SalesManager& sm, Vector<std::string> args) {
    std::cout << "saving files...\n";
    sm.saveSales();
    std::cout << "files saved\n";
}

void addSale(SalesManager& sm, Vector<std::string> args) {
    Sale newSale;
    std::string input;

    std::cout << "comprador: ";
    std::getline(std::cin, input);
    newSale.buyer = input;

    std::cout << "produto: ";
    std::getline(std::cin, input);
    newSale.item = input;
    
    std::cout << "data (dd/MM/yyyy): ";
    std::getline(std::cin, input);
    newSale.date = input;

    std::cout << "preço: ";
    std::getline(std::cin, input);
    newSale.price = std::stoi(input);

    if (sm.addSale(newSale))
        std::cout << "sale added successfully!\n";
    else
        std::cout << "Something went wrong while trying to add new sale. Try again.\n";
}

REGISTER_COMMAND("list", listSales)
REGISTER_COMMAND("load", loadSales)
REGISTER_COMMAND("save", saveSales)
REGISTER_COMMAND("add", addSale)
