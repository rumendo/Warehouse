#include "Product.h"
#include <cstdio>

Product::Product(string _name, char *_expiryDate, char *_acceptanceDate, string _manufacturer, string _measurementUnit, float _quantity, float _price, string _description) {
    id = nextID++;
    name = _name;
    expiryDate = new Date(_expiryDate);
    acceptanceDate = new Date(_acceptanceDate);
    manufacturer = _manufacturer;
    measurementUnit = _measurementUnit;
    quantity = _quantity;
    price = _price;
    description = _description;
}

void Product::printInfo() {
    char _expiryDate[11], _acceptanceDate[11];
    expiryDate.getDate(_expiryDate);
    acceptanceDate.getDate(_acceptanceDate);

    printf("ID: %d\n"
           "Name: %s\n"
           "Expiry Date: %s\n"
           "Acceptance Date: %s\n"
           "Manufacturer: %s\n"
           "Measurement Unit: %s\n"
           "Available Quantity: %.2f\n"
           "Price: %.2f\n"
           "Description: %s\n",
           id, name.c_str(), _expiryDate, _acceptanceDate, manufacturer.c_str(), measurementUnit.c_str(), quantity, price, description.c_str());
}