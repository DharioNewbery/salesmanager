#ifndef CORE_H
#define CORE_H

#include "../src/Command.hpp"

class ListSaleCommand: public Command {
    void execute(SalesManager& sm, Vector<std::string> args) override {
        int start = 0, end = INT_MAX;
        if (args.getSize() > 1)
            start = std::stoi(args[1]);
        if (args.getSize() > 2) {
            end = std::stoi(args[2]);
        }
        utils::printSalesList(sm.getSales(), start, end);
    }
};

class LoadSalesCommand: public Command {
    void execute(SalesManager& sm, Vector<std::string> args) override {
    if (args.getSize() != 1) {
        std::cerr << "Usage: load <filename>\n";
        return;
    }

    const std::string& filename = args[0];
        sm.loadSales(filename);
    }
};

class SaveSalesCommand: public Command {
    void execute(SalesManager& sm, Vector<std::string> args) override {
        if (args.getSize() != 1) {
            std::cerr << "Usage: save <filename>\n";
            return;
        }

        const std::string& filename = args[0];
        sm.saveSales(filename);
    }
};

class ClearCommand: public Command {
    void execute(SalesManager& sm, Vector<std::string> args) override {
        #if defined _WIN32
            system("cls");
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            system("clear");
        #elif defined (__APPLE__)
            system("clear");
        #endif
    }
};

class RemoveCommand: public Command {
    void execute(SalesManager& sm, Vector<std::string> args) override {
    
        if (args.getSize() != 1) {
            std::cerr << "Usage: remove <integer id>\n";
            return;
        }
        int id = std::stoi(args[0]);
        sm.removeSaleById(id);
    }
};

class AddSaleCommand : public Command {
private:
    bool BuilderFromArgs(Vector<std::string> args, Sale& newSale) {
        newSale.buyer = args[0];
        newSale.item = args[1];
        if (!tryConvertDateToLong(args[2], newSale.date)) return false;
        if (!tryConvertPriceToInt(args[3], newSale.price)) return false;
        return true;
    }
    Sale BuilderhelperPrompt() {
        Sale newSale;
        std::string input;
        
        std::cout << "Comprador: ";
        std::getline(std::cin, newSale.buyer);

        std::cout << "Produto: ";
        std::getline(std::cin, newSale.item);
        
        bool isDateValid = false;
        while (!isDateValid) {
            std::cout << "Data (dd/MM/yyyy): ";
            std::getline(std::cin, input);
            if (!tryConvertDateToLong(input, newSale.date)) {
                std::cerr << "Error: Invalid date format '" << input << "'. Expected format: dd/MM/yyyy\n";
            } else isDateValid = true;
        }

        bool isPriceValid = false;
        while (!isPriceValid) {
            std::cout << "Valor: ";
            std::getline(std::cin, input);
            if (!tryConvertPriceToInt(input, newSale.price)) {
                std::cerr << "Error: Invalid price format '" << input << "'. Expected format: dd/MM/yyyy\n";
            } else isPriceValid = true;
        }
        return newSale;
    }

    void execute(SalesManager& sm, Vector<std::string> args) override {
        Sale newSale;

        // MODE 1: Fast Add (e.g., add "Dhario Newbery" "Garrafa d'água" "01/01/2026" 2,50)
        if (args.getSize() == 4) {
            if (!BuilderFromArgs(args, newSale)) {
                std::cerr << "Error: Invalid arguments. Usage:\n";
                std::cerr << "add <string buyer> <string item> <string date> <int price>\n";
                return;
            }
        }

        // MODE 2: Interactive Prompts (just 'add')
        else if (args.getSize() == 0) {
            newSale = BuilderhelperPrompt();
        } else {
            std::cerr << "Sintaxe invalida: digite 'add --help'\n";
            return;
        }
        sm.addSale(newSale);
    }
};

CommandRegistrator registerListCommand("list", new ListSaleCommand());
CommandRegistrator registerLoadCommand("load", new LoadSalesCommand());
CommandRegistrator registerSaveCommand("save", new SaveSalesCommand());
CommandRegistrator registerClearCommand("clear", new ClearCommand());
CommandRegistrator registerRemoveCommand("remove", new RemoveCommand());
CommandRegistrator registerAddSaleCommand("add", new AddSaleCommand());

#endif