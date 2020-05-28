#ifndef WAREHOUSE_WAREHOUSE_H
#define WAREHOUSE_WAREHOUSE_H


#include "Product.h"


class Warehouse {
private:
    vector<Product> products;
    string fileName;

public:
    void addProduct(string, char*, char*, string, string, float, float, string);

    // Saves all products to a file with given name.
    void saveProducts(string);
    void saveProducts();
    // Loads products from given file path.
    void loadProducts(string);

    void printInfo();

};


#endif //WAREHOUSE_WAREHOUSE_H
