#include <iostream>
#include <cstring>
#include <fstream>
#include "Product.h"
#include "Warehouse.h"
#include "Storage.h"

using namespace std;

uint16_t Product::nextID = 1;

int main() {

    char dateStr[11], date1[11], date2[11];
    strcpy(date1, "2020/11/21");
    strcpy(date2, "2019/07/01");
    string name = "Bilka";
    string name2 = "Bilka2";
    string manufacturer = "Rumbeca EOOD";
    string measurementUnit = "KG";
    float quantity = 1533.1;
    float price = 4.20;
    string description = "Discrip6on";

    Warehouse warehouse;


    Product bilka(name, date1, date2, manufacturer, measurementUnit, quantity, price, description);
//    warehouse.addProduct(name, date1, date2, manufacturer, measurementUnit, quantity, price, description);
//    warehouse.addProduct(name, date1, date2, manufacturer, measurementUnit, quantity, price, description);
//    warehouse.addProduct(name, date1, date2, manufacturer, measurementUnit, quantity, price, description);
    warehouse.loadProducts("products.csv");
//    warehouse.printStorage();

//    warehouse.printInfo();
    warehouse.addProduct(name, date1, date2, manufacturer, measurementUnit, quantity, price, description);
    warehouse.addProduct(name2, date1, date2, manufacturer, measurementUnit, quantity, price, description);

//    warehouse.saveProducts("products.csv");
    warehouse.printInfo();

//    warehouse.printStorage();

    return 0;
}
