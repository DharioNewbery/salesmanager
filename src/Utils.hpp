#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include <climits>
#include "Vector.hpp"
#include "Sale.hpp"

namespace salesManagerUtils {
    int getBiggestId(Vector<Sale> sales) {
        int biggest = 0;
        for (int i = 0; i < sales.getSize(); i++)
            biggest = (biggest < sales[i].id)? sales[i].id : biggest;
        return biggest;
    }
}

namespace flag {
    bool isFormatValid(const std::string& date) {
        if (date.length() != 2) return false;
        if (date[0] != '-') return false;
        return true;
    }
}

namespace date {
    bool isFormatValid(const std::string& date) {
        if (date.length() != 10) return false;
        if (date[2] != '/' || date[5] != '/') return false;
        return true;
    }
}

namespace price {
    unsigned long toUlong(std::string text) {
        if (text.empty()) return 0;
        
        size_t commaPos = text.find(',');
        if (commaPos != std::string::npos) text[commaPos] = '.';
        
        unsigned long value = 0;
        float floatValue = std::stof(text) * 100; // Convertendo para centavos
        value = static_cast<unsigned long>(floatValue);
        return value;
    }

    std::string toPrice(unsigned long price) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << price / 100.0;
        return oss.str();
    }
};

namespace input {
    Vector<std::string> splitInput(std::string input) {
        Vector<std::string> result = Vector<std::string>();
        std::string currentToken = "";
        bool insideQuotes = false;

        for (size_t i = 0; i < input.length(); ++i) {
            char c = input[i];

            if (c == '\"') {
                // Toggle the state when we hit a quote
                insideQuotes = !insideQuotes;
            } 
            else if (c == ' ' && !insideQuotes) {
                // If it's a space and we aren't in quotes, the word is finished
                if (!currentToken.empty()) {
                    result.push(currentToken);
                    currentToken = "";
                }
            } 
            else {
                // Otherwise, keep building the current word
                currentToken += c;
            }
        }

        // Don't forget to add the very last token
        if (!currentToken.empty()) {
            result.push(currentToken);
        }

        return result;
    }
}

#include "Sale.hpp"

#include <string>

namespace print {

    // Função para contar caracteres reais (UTF-8)
    size_t utf8_length(const std::string& str) {
        size_t length = 0;
        for (size_t i = 0; i < str.length(); i++) {
            // Em UTF-8, bytes que começam com 10xxxxxx são continuações.
            // Contamos apenas os bytes que iniciam um caractere (não são 0x80-0xBF).
            if ((str[i] & 0xC0) != 0x80) {
                length++;
            }
        }
        return length;
    }

    std::string formatColumn(std::string text, size_t width) {
        size_t actualLen = utf8_length(text);

        if (actualLen > width) {
            // Truncar é mais complexo em UTF-8. 
            // Vamos percorrer os bytes até atingir o limite de caracteres visíveis.
            size_t bytesToKeep = 0;
            size_t charsCounted = 0;
            while (charsCounted < (width - 3) && bytesToKeep < text.length()) {
                if ((text[bytesToKeep] & 0xC0) != 0x80) charsCounted++;
                bytesToKeep++;
            }
            // Garante que não cortamos um caractere multi-byte ao meio
            while (bytesToKeep < text.length() && (text[bytesToKeep] & 0xC0) == 0x80) {
                bytesToKeep++;
            }
            return text.substr(0, bytesToKeep) + "...";
        }

        // Se o texto é menor, precisamos compensar o setw manualmente
        size_t padding = width - actualLen;
        return text + std::string(padding, ' ');
    }

    void printSale(const Sale& sale) {
        std::cout << "ID: " << sale.id 
                  << " | Buyer: " << sale.buyer 
                  << " | Item: " << sale.item 
                  << " | Date: " << sale.date 
                  << " | Price: R$" << std::fixed << std::setprecision(2) << sale.price / 100.0 
                  << std::endl;
    }
    void printSalesList(Vector<Sale> sales, int start = 0, int end = INT_MAX) {
        if (end == INT_MAX) end = sales.getSize();
        const int wIndex = 4;
        const int wID = 4;
        const int wBuyer = 20;
        const int wItem = 20;
        const int wDate = 10;
        const int wPrice = 15;

    std::cout << "\n// ================ Mostrando vendas de " << start << " a " << end << " (total: " << sales.getSize() << ") ================" << std::endl;
    
    std::cout << std::right
              << std::setw(wIndex) << ""          << " | "
              << std::left
              << std::setw(wID)    << "ID"        << " | "
              << std::setw(wBuyer) << "Comprador" << " | "
              << std::setw(wItem)  << "Item"      << " | "
              << std::setw(wDate)  << "Data"      << " | "
              << "Price" << std::endl;

    // std::cout << std::string(wID + wBuyer + wItem + wDate + wPrice + 12, '-') << std::endl;

    for (int i = start; i <= end && i < sales.getSize(); ++i) {
        const auto& s = sales[i];
        
        std::cout << std::right 
                  << std::setw(wIndex) << i << " | "
                  << std::left

                  << std::setw(wID)    << s.id << " | "
                  << std::setw(wBuyer) << formatColumn(s.buyer, wBuyer) << " | "
                  << std::setw(wItem)  << formatColumn(s.item, wItem)  << " | "
                  << std::setw(wDate)  << s.date << " | "
                  << "R$" << std::fixed << std::setprecision(2) << s.price / 100.0
                  << std::endl;
    }
    }
}

// =========== Monstrando vendas de 0 a 9 (total: 15) ===========
// ID | Buyer          | Item           | Date       | Price
// 0  | Dhario Newbery | Garrafa d'água | 01/01/2026 | R$2,50
// 1  | Alice Smith    | Livro          | 15/02/2026 | R$45,00
// 2  | Bobert Johns...| Caneca         | 20/03/2026 | R$15,75

#endif