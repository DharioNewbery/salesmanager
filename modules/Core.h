#include "../ModuleSDK.h"

void listSales(SalesManager& sm, Vector<std::string> args) {
    sm.listSales();
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

REGISTER_COMMAND("list", listSales)
REGISTER_COMMAND("load", loadSales)
REGISTER_COMMAND("save", saveSales)
