#include <iostream>
#include "Vector.h"
#include "SalesManager.h"
using namespace std;

int main () {
    SalesManager sm = SalesManager();
    sm.loadSales();
    sm.listSales();
    return 0;
}