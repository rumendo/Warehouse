#ifndef WAREHOUSE_PRODUCT_H
#define WAREHOUSE_PRODUCT_H


#include <stdint-gcc.h>
#include <cstring>
#include <string>
#include <vector>
#include "Date.h"

using namespace std;


class Product {
private:
    uint16_t id = 0;
    static uint16_t nextID;
    string name;
    Date expiryDate;
    Date acceptanceDate;
    string manufacturer;
    string measurementUnit;
    float quantity;
    float price;
//    vector<float> placement;
    string description;

public:
    Product(string, char*, char*, string, string, float, float, string);

    void printInfo();
};


#endif //WAREHOUSE_PRODUCT_H