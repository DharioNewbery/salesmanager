#ifndef SORT_H
#define SORT_H

#include "../src/Command.hpp"

//class SortCommand: public Command {
//public:
//
//    void execute(SalesManager& sm, Vector<std::string> args) override {
//        if (sm.sortByPrice())
//            std::cout << "Vendas ordenadas por preço com sucesso!\n";
//        else
//            std::cout << "Não há vendas para ordenar.\n";
//    }
//};
// A função reescreve na própria variável os valores;


class SortByCommand: public Command {
private:
    Vector<Sale> m_sales = {};
    bool sortBy(std::string sortBy, std::string ordem = "asc");
public:

std::string getHelpMessage() const override {
    return "Este comando ordena todos os dados armazenados na memória. Ele pode ser usado de 5 formas:\n\
1. sortBy id <up/down>: Ordena todos as vendas pelo identificador.\n\
2. sortBy price <up/down>: Ordena todos as vendas por preço.\n\
3. sortBy buyer <up/down>: Ordena todos os vendas por ordem alfabética do comprador.\n\
4. sortBy item <up/down>: Ordena todos os produtos por ordem alfabética do item.\n\
5. sortBy date <up/down>: Ordena todos os produtos por data.\n\
<up> ordem crescente | <down> ordem decrescente\n\
Exemplo de uso: sortBy price up";}

    Vector<Signature> getSignatures() const override {
        return {
            {ArgType::STRING, ArgType::STRING} // sortBy <type> <order>
        };
    }

    void execute(SalesManager& sm, Vector<std::string> args) override {
        m_sales = sm.getSales();
        
        std::string sort = args[0];
        std::string order = args[1];

        if (sortBy(sort, order)) {
            std::cout << "Vendas ordenadas por " << sort
                    << " (" << order << ") com sucesso!\n";
        }
        else {
            std::cout << "Não foi possível ordenar.\n";
            return;
        }

        sm.setSales(m_sales);
    }
};

CommandRegistrator registerSortByCommand("sortBy", new SortByCommand());

bool SortByCommand::sortBy(std::string sort, std::string order)
{
    if (m_sales.getSize() <= 1) {
        std::cout << "sistema tem menos de 2 elementos\n";
        return false;
    }
    if (!(order != "up" || order != "down")) {
        std::cout << "ordem incorreta: '" << order << "'\n";
        return false;
    }
    if (!(sort == "price" || sort == "id" || sort == "buyer" || sort == "item" || sort == "date")) {
        std::cout << "tipo incorreto: '" << sort << "'\n";
        return false;
    }

    bool toUp = (order == "up");
    //loop principal ;
    for (int i = 0; i < m_sales.getSize() - 1; i++) {
        //loop secundário só pra fazer as comparações; 
        for (int j = i + 1; j < m_sales.getSize(); j++) {

            bool needTrade = false;

            if (sort == "date") {
                if (toUp)
                    needTrade = date::isFirstDateGreater(m_sales[i].date, m_sales[j].date);
                else
                    needTrade = date::isFirstDateGreater(m_sales[j].date, m_sales[i].date);
            }

            else if (sort == "id") {
                if (toUp)
                    needTrade = m_sales[i].id > m_sales[j].id;
                else
                    needTrade = m_sales[i].id < m_sales[j].id;
            }

            else if (sort == "item") {
                if (toUp)
                    needTrade = toLower(m_sales[i].item) > toLower(m_sales[j].item);
                else
                    needTrade = toLower(m_sales[i].item) < toLower(m_sales[j].item);
            }

            else if (sort == "buyer") {
                if (toUp)
                    needTrade = toLower(m_sales[i].buyer) > toLower(m_sales[j].buyer);
                else
                    needTrade = toLower(m_sales[i].buyer) < toLower(m_sales[j].buyer);
            }

            else if (sort == "price") {
                if (toUp)
                    needTrade = m_sales[i].price > m_sales[j].price;
                else
                    needTrade = m_sales[i].price < m_sales[j].price;
            }

            if (needTrade) {
                Sale aux = m_sales[i];
                m_sales[i] = m_sales[j];
                m_sales[j] = aux;
            }
        }
    }

    return true;
}

#endif   