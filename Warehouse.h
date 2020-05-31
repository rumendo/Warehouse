#ifndef WAREHOUSE_WAREHOUSE_H
#define WAREHOUSE_WAREHOUSE_H

#define DAYS_TO_SPOIL 7

#include "Product.h"
#include "Storage.h"


class Warehouse {
private:
    Storage storage;
    vector<Product> products;
    string fileName;

public:

    // Adds products and saves a reference to them given the following rules:
    // A new product with a different expiration date that an already existing one is placed in a different location.
    // Products with matching names and expiration dates are placed in the same location if possible.
    void addProduct(string, char*, char*, string, string, float, float, string);

    // Removes a specified amount of a given product.
    void removeProduct(string, float);

    void clean();

    // Saves all products to a file with given name.
    void saveProducts(string);
    void saveProducts();

    // Loads products from given file path.
    void loadProducts(string);

    // Prints information for all products.
    void printInfo();

    // Prints location of loaded products as a matrix of pointers. Use for testing.
    void printStorage();

};


#endif //WAREHOUSE_WAREHOUSE_H
