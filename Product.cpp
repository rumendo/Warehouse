#include "Product.h"
#include <cstdio>

Product::Product( string _name, char *_expiryDate, char *_acceptanceDate, string _manufacturer, string _measurementUnit, float _quantity, float _price, char *_placement, string _description) {
    name = _name;
    expiryDate = new Date(_expiryDate);
    acceptanceDate = new Date(_acceptanceDate);
    manufacturer = _manufacturer;
    measurementUnit = _measurementUnit;
    quantity = _quantity;
    price = _price;
    strcpy(placement, _placement);
    description = _description;
}

Product::Product(string _name, char *_expiryDate, char *_acceptanceDate, string _manufacturer, string _measurementUnit, float _quantity, float _price, string _description) {
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
    uint16_t shelfNumber = (placement[0] - '0') * 100 + (placement[1] - '0') * 10 + (placement[2] - '0');
    uint16_t rowNumber = placement[4] - '0';
    printf(
           "Name: %s\n"
           "Expiry Date: %s\n"
           "Acceptance Date: %s\n"
           "Manufacturer: %s\n"
           "Available Quantity: %.2f %s\n"
           "Price: %.2f\n"
           "Shelf: #%d, "
           "Row: #%d\n"
           "Description: %s\n",
           name.c_str(), _expiryDate, _acceptanceDate, manufacturer.c_str(), quantity, measurementUnit.c_str(), price, shelfNumber, rowNumber, description.c_str());
}

string Product::getCSV() {
    string productCSV;
    char date1[11], date2[11];
    expiryDate.getDate(date1);
    acceptanceDate.getDate(date2);
    productCSV = name + ',' + date1 + ',' + date2 + ',' + manufacturer + ',' + measurementUnit + ',' +
            to_string(quantity) + ',' + to_string(price) + ',' + placement + ',' + description + '\n' ;
    return productCSV;
}

string Product::getName() {
    return this->name;
}

void Product::addQuantity(float guantityToAdd) {
    quantity += guantityToAdd;
}

float Product::getQuantity() {
    return quantity;
}

uint32_t Product::getExpiryDateTimestamp() {
    return expiryDate.getTimestamp();
}

void Product::setQuantity(float quantityToSet) {
    quantity = quantityToSet;
}

void Product::setPlacement(char *_placement) {
    strcpy(placement, _placement);
}

void Product::getDate(char *date) {
    expiryDate.getDate(date);
}

string Product::getMU() {
    return measurementUnit;
}

void Product::getPlacement(char *_placement) {
    strcpy(_placement, placement);
}
