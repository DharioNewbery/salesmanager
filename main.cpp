#include <iostream>
#include "Vector.h"
#include "SalesManager.h"
using namespace std;

int main () {
    SalesManager sm = SalesManager();
    Sale a;
    a.buyer = "Dhario";
    a.date = "01/01/1970";
    a.item = "Geladeira Gamer";
    a.price = 2500;
    sm.addSale(a);

    a.buyer = "Khey Niwa";
    a.date = "27/01/2026";
    a.item = "memoria RAM ddr2 256kb";
    a.price = 999999;
    sm.addSale(a);

    sm.listSales();
    return 0;
}