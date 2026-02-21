#ifndef CORE_H
#define CORE_H

#include "../src/Command.hpp"

class ListSaleCommand: public Command {
public:
    std::string getHelpMessage() const override {
    return "Este comando lista as vendas registradas. Ele pode ser usado de três formas:\n\
1. list: lista todas as vendas.\n\
2. list <integer start>: lista todas as vendas a partir do índice 'start'.\n\
3. list <integer start> <integer end>: lista as vendas no intervalo de índices de 'start' a 'end'.\n\
Exemplo de uso: list 0 10 (lista as primeiras 10 vendas).";
}

    Vector<Signature> getSignatures() const override {
        return {
            {}, // list
            {ArgType::INT}, // list <start>
            {ArgType::INT, ArgType::INT} // list <start> <end>
        };
    }

    void execute(SalesManager& sm, Vector<std::string> args) override {
        int start = 0, end = INT_MAX;
        if (args.getSize() > 0)
            start = std::stoi(args[0]);
        if (args.getSize() > 1) {
            end = std::stoi(args[1]);
        }
        print::printSalesList(sm.getSales(), start, end);
    }
};

class LoadSalesCommand: public Command {
public:
    std::string getHelpMessage() const override {
    return "Este comando carrega vendas de um arquivo. Ele pode ser usado da seguinte forma:\n\
1. load <filename>: carrega todas as vendas do arquivo especificado.\n\
2. load <filename> -a: carrega as vendas do arquivo e as adiciona às vendas já existentes (sem substituir).\n\
Exemplo de uso: load vendas.txt -a";}
    
    Vector<Signature> getSignatures() const override {
        return {
            {ArgType::STRING}, // load <filename>
            {ArgType::STRING, ArgType::FLAG} // load <filename> <append>
        };
    }

    void execute(SalesManager& sm, Vector<std::string> args) override {
        const std::string& filename = args[0];
        
        if (!std::ifstream(filename)) {
            std::cout << "Falha ao carregar de '" << filename << "'Arquivo nao encontrado.";
            return;
        }

        bool append = false;
        if (args.getSize() == 2) {
            append = (args[1] == "-a");
        }


        sm.loadSales(filename, append);
        std::cout << "Arquivo '" <<  filename << "carregado com sucesso!\n";
    }
};

class SaveSalesCommand: public Command {
public:
    std::string getHelpMessage() const override {
    return "Este comando salva as vendas em um arquivo. Ele pode ser usado da seguinte forma:\n\
1. save <filename>: salva todas as vendas no arquivo especificado.\n\
2. save <filename> -a: salva as vendas no arquivo, sem sobreescrever as vendas que já estão armazenadas lá. \n\
Ou seja, o arquivo final conterá tanto as vendas atuais quanto as vendas previamente salvas no arquivo.\n\
Exemplo de uso: save vendas.txt -a";}
    
    Vector<Signature> getSignatures() const override {
        return {
            {ArgType::STRING}, // save <filename>
            {ArgType::STRING, ArgType::FLAG} // save <filename> <override>
        };
    }

    void execute(SalesManager& sm, Vector<std::string> args) override {

        const std::string& filename = args[0];
        bool append = false;
        if (args.getSize() == 2) {
            append = (args[1] == "-a");
        }
        sm.saveSales(filename, append);
        std::cout << "Arquivo '" << filename << "' salvo com sucesso!\n";
    }
};

class ClearCommand: public Command {
public:
    std::string getHelpMessage() const override {
    return "Este comando limpa o terminal. Ele pode ser usado da seguinte forma:\n\
1. clear: limpa o terminal.\n\n\
Exemplo de uso: clear";}
    
    Vector<Signature> getSignatures() const override {
        return {
            {} // clear
        };
    }

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
public:
    std::string getHelpMessage() const override {
    return "Este comando remove uma venda pelo ID. Ele pode ser usado da seguinte forma:\n\
1. remove <integer id>: remove a venda com o ID especificado.\n\
Exemplo de uso: remove 5 (remove a venda com ID 5).";}

    Vector<Signature> getSignatures() const override {
        return {
            {ArgType::INT} // remove <id>
        };
    }

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
        if (!date::isFormatValid(args[2])) return false;
        newSale.date = args[2];
        newSale.price = price::toUlong(args[3]);
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
            if (!date::isFormatValid(input)) {
                std::cerr << "Error: Invalid date format '" << input << "'. Expected format: dd/MM/yyyy\n";
            } else {
                newSale.date = input;
                isDateValid = true;
            }
        }

        std::getline(std::cin, input);
        newSale.price = price::toUlong(input);
        return newSale;
    }

public:
    std::string getHelpMessage() const override {
    return "Este comando adiciona uma nova venda. Ele pode ser usado de duas formas:\n\
1. add <string buyer> <string item> <string date> <int price>: adiciona uma nova venda com os detalhes especificados.\n\
A data deve estar no formato dd/MM/yyyy e o preço deve ser um número em reais separando centavos por ',' ou '.' (10 ou 20,50).\n\
use aspas duplas ("") para nomes e produtos que contêm espaços.\n\
2. add: inicia uma rotina interativa que solicita os detalhes da venda um por um.\n\
Exemplo de uso: add \"Dhario Newbery\" \"Garrafa d'água\" 01/01/2026 2,50\n\
(adiciona uma venda para Dhario Newbery comprando uma garrafa d'água por R$2,50 no dia 01/01/2026).";}

    Vector<Signature> getSignatures() const override {
        return {
            {ArgType::STRING, ArgType::STRING, ArgType::DATE, ArgType::MONEY}, // add <buyer> <item> <date> <price>
            {} // add (interactive mode)
        };
    }

    void execute(SalesManager& sm, Vector<std::string> args) override {
        Sale newSale;
        // MODE 1: Fast Add (e.g., add "Dhario Newbery" "Garrafa d'água" "01/01/2026" 2,50)
        if (args.getSize() == 4) {
            if (!BuilderFromArgs(args, newSale)) {
                std::cerr << "Error: Argumentos invalidos. tente novamente.\n";
                return;
            }
        }
        // MODE 2: Interactive Prompts (just 'add')
        if (args.getSize() == 0) 
            newSale = BuilderhelperPrompt();

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