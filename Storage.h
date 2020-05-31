#ifndef WAREHOUSE_STORAGE_H
#define WAREHOUSE_STORAGE_H

#define MAX_ROW_CAPACITY 512
#define NUMBER_OF_SHELFS 128
#define ROWS_IN_SHELF 8

#include <vector>
#include "Product.h"
#include <iostream>
#include <cstring>
#include <string>


using namespace std;

class Storage {
private:
    std::vector<std::vector<Product*>> shelfs;
public:
    Storage();


    // Looks for available storage space given the following rules:
    // A new product with a different expiration date that an already existing one is placed in a different location.
    // Products with matching names and expiration dates are placed in the same location if possible.
    uint8_t addProduct(Product*, char*, uint8_t);


    // Load product from file.
    void loadProduct(Product*, char*);

    // Prints location of loaded products as a matrix of pointers. Use for testing.
    void printStorage();

    // Fills a char array with the locations an empty storage space.
    void getEmptyRow(char*);

    // Sets storage sell to nullptr. Used for removing a product;
    void setNull(char*);

    // Zeroize storage
    void close();
};


#endif //WAREHOUSE_STORAGE_H
