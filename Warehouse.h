#ifndef WAREHOUSE_WAREHOUSE_H
#define WAREHOUSE_WAREHOUSE_H


#include "Product.h"
#include "Storage.h"


class Warehouse {
private:
    Storage storage;
    vector<Product> products;
    string fileName;

public:
//    Warehouse();
//    void loadProduct(uint16_t , string, char*, char*, string, string, float, float, string);

    void addProduct(string, char*, char*, string, string, float, float, string);

    // Saves all products to a file with given name.
    void saveProducts(string);
    void saveProducts();
    // Loads products from given file path.
    void loadProducts(string);

    void printInfo();
    void printStorage();

};


#endif //WAREHOUSE_WAREHOUSE_H
