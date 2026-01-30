#include "../src/ModuleSDK.h"

namespace help {
    const auto listSales = "\
    >> list --help (shows this message)\n\
    \n\
    >> list\n\
    list all sales.\n\
    \n\
    >> list <integer start>\n\
    list all subsequent sales.\n\
    \n\
    >> list <integer start> <integer end>\n\
    list all elements in the interval.\n";

    const auto loadSales = "\
    >> load --help (shows this message)\n\
    \n\
    >> load <filename>\n\
    load all sales from the file.\n";

    const auto saveSales = "\
    >> save --help (shows this message)\n\
    \n\
    >> save <filename>\n\
    write all sales to the file.\n";
    
    const auto addSale = "\
    >> add --help (shows this message)\n\
    \n\
    >> add\n\
    Start a routine to add a new sale.\n\
    \n\
    >> add <string buyer> <string item> <string date> <int price>\n\
    Add a new sale.\n";

    const auto clear = "\
    >> clear --help (shows this message)\n\
    \n\
    >> clear\n\
    clear the terminal\n";
    
    const auto removeSale = "\
    >> remove --help (shows this message)\n\
    \n\
    >> remove <integer id>\n\
    remove the sale with the specified id.\n";
}



void listSales(SalesManager& sm, Vector<std::string> args) {
    int start = 0, end = INT_MAX;
    if (args.getSize() > 1) {
        if (!tryParseInt(args[1], start)) {
            std::cerr << "Error: Invalid start index '" << args[1] << "'\n";
            return;
        }
    }

    if (args.getSize() > 2) {
        if (!tryParseInt(args[2], end)) {
            std::cerr << "Error: Invalid end index '" << args[2] << "'\n";
            return;
        }
    }

    sm.listSales(start, end);
}

void loadSales(SalesManager& sm, Vector<std::string> args) {
    // Basic validation: Command + Filename = 2 total tokens
    
    if (args.getSize() != 2) {
        std::cerr << "Usage: load <filename>\n";
        return;
    }

    const std::string& filename = args[1];
    std::cout << "Loading sales from '" << filename << "'...\n";
    
    if (sm.loadSales(filename)) {
        std::cout << "Success: Data loaded!\n";
    } else {
        std::cerr << "Error: Could not open or parse '" << filename << "'.\n";
    }
}

void saveSales(SalesManager& sm, Vector<std::string> args) {
    if (args.getSize() < 2) {
        std::cerr << "Usage: save <filename>\n";
        return;
    }

    const std::string& filename = args[1];
    std::cout << "Saving sales to '" << filename << "'...\n";
    
    if (sm.saveSales(filename)) {
        std::cout << "Success: Data saved.\n";
    } else {
        std::cerr << "Error: Failed to write to '" << filename << "'. Check permissions.\n";
    }
}

void clear(SalesManager& sm, Vector<std::string> args)
{
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

void removeSale(SalesManager& sm, Vector<std::string> args) {

    int id;
    
    if (args.getSize() < 2 || !tryParseInt(args[1], id)) {
        std::cerr << "Usage: remove <integer id>\n";
        return;
    }

    if (sm.removeSaleById(id))
        std::cout << "item removed.\n" << std::endl;
    else
        std::cerr << "Something went wrong while removing item with id '" << id << "'.\n" << std::endl;
}

void addSale(SalesManager& sm, Vector<std::string> args) {
    Sale newSale;

    // MODE 1: Fast Add (e.g., add "John Doe" "Apple" "01/01/2026" 150)
    if (args.getSize() >= 5) {
        newSale.buyer = args[1];
        newSale.item = args[2];
        newSale.date = args[3];
        if (!tryParseInt(args[4], newSale.price)) {
            std::cerr << "Error: Invalid price format '" << args[4] << "'\n";
            return;
        } 
    } 
    // MODE 2: Interactive Prompts (if they just type 'add')
    else {
        std::string input;
        
        std::cout << "Comprador: ";
        std::getline(std::cin, newSale.buyer);

        std::cout << "Produto: ";
        std::getline(std::cin, newSale.item);
        
        std::cout << "Data (dd/MM/yyyy): ";
        std::getline(std::cin, newSale.date);

        bool isPriceValid = false;
        while (!isPriceValid) {
            std::cout << "Valor: ";
            std::getline(std::cin, input);
            if (!tryParseInt(input, newSale.price)) {
                std::cerr << "Error: Invalid price format '" << input << "'\n";
            } else isPriceValid = true;
        }
    }

    if (sm.addSale(newSale))
        std::cout << "Sale added successfully!\n";
    else
        std::cout << "Error: Manager could not store the sale.\n";
}

REGISTER_HELP_MESSAGE("list", help::listSales, listSales)
REGISTER_HELP_MESSAGE("load", help::loadSales, loadSales)
REGISTER_HELP_MESSAGE("save", help::saveSales, saveSales)
REGISTER_HELP_MESSAGE("add", help::addSale, addSale)
REGISTER_HELP_MESSAGE("clear", help::clear, clear)
REGISTER_HELP_MESSAGE("remove", help::removeSale, removeSale)

REGISTER_COMMAND("list", listSales)
REGISTER_COMMAND("load", loadSales)
REGISTER_COMMAND("save", saveSales)
REGISTER_COMMAND("add", addSale)
REGISTER_COMMAND("clear", clear)
REGISTER_COMMAND("remove", removeSale)
