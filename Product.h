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
    string name;
    Date expiryDate;
    Date acceptanceDate;
    string manufacturer;
    string measurementUnit;
    float quantity;
    float price;
    char placement[6] = "\0";
    string description;

public:
    // Used for loading objects from file.
    // Used for adding a new object placed in a different location.
    Product(string, char*, char*, string, string, float, float, char*, string);

    // Used for adding a new object.
    Product(string, char*, char*, string, string, float, float, string);

    // Prints readable product data to standard output.
    void printInfo();

    // Constructs CSV formatted string based on product data.
    string getCSV();

    string getName();
    string getMU();
    uint32_t getExpiryDateTimestamp();

    float getQuantity();
    void getDate(char*);
    void getPlacement(char*);
    void setQuantity(float);
    void addQuantity(float);
    void setPlacement(char*);
};


#endif //WAREHOUSE_PRODUCT_H
