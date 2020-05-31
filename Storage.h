#ifndef WAREHOUSE_STORAGE_H
#define WAREHOUSE_STORAGE_H

#define MAX_ROW_CAPACITY 512 // 512
#define NUMBER_OF_SHELFS 128 // 16
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


    // Returns how much of the product quantity was not added as a positive integer.
    // Returns -1 if the storage was maxed-out.
    // Returns 0 when product quantity was added in full.
    // Fill a given char* with the products' placement.
    uint8_t addProduct(Product*, char*, uint8_t);


    // Load product from file.
    void loadProduct(Product*, char*);

    // Loads products with defined placement.
//    void loadProduct(Product*);

    void printStorage();

    void getEmptyRow(char*);
};




#endif //WAREHOUSE_STORAGE_H
