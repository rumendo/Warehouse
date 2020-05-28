#include <fstream>
#include <iostream>
#include <sstream>
#include "Warehouse.h"

void Warehouse::addProduct(string _name, char *_expiryDate, char *_acceptanceDate, string _manufacturer, string _measurementUnit, float _quantity, float _price, string _description) {

   // Input validation. Exclude commas from all strings.

    for (auto &product : products)
    {
        char date[11];
        Date expDate = product.getExpiryDate();
        expDate.getDate(date);
        if(!strcmp(date, _expiryDate)){
            product.addQuantity(_quantity);
            return;
        }
    }

    Product product(_name, _expiryDate, _acceptanceDate, _manufacturer, _measurementUnit, _quantity, _price, _description);
    products.push_back(product);
}

void Warehouse::saveProducts(string file) {
    fstream productFile;
    productFile.open(file, ios::out | ios::trunc);

    for (auto &product : products)
    {
        productFile << product.getCSV();
    }

    printf("Successfully saved another %s.", file.c_str());
    productFile.close();
}

void Warehouse::saveProducts() {
    fstream productFile;
    productFile.open(fileName, ios::out | ios::trunc);

    for (auto &product : products)
    {
        productFile << product.getCSV();
    }

    printf("Successfully saved %s.", fileName.c_str());
    productFile.close();
}

void Warehouse::loadProducts(string file) {
    fileName = file;
    string str;
    ifstream productFile(file);

    if(!productFile.is_open()) {
        printf("An error occurred while opening file %s.", fileName.c_str());
        return;
    }

    while(std::getline(productFile, str)) {

        // Sourced from stack overflow. Ref: 5607589 Author: user:415784
        vector<string> result;
        stringstream s_stream(str);
        while(s_stream.good()) {
            string substr;
            getline(s_stream, substr, ',');
            result.push_back(substr);
        }
        //


        for(int i = 0; i < result.size(); i+=9) {

            char date1[11], date2[11];
            string name = result.at(i + 1);

            strcpy(date1, result.at(i + 2).c_str());
            strcpy(date2, result.at(i + 3).c_str());
            string manufacturer = result.at(i + 4);
            string measurementUnit = result.at(i + 5);
            float quantity = stof(result.at(i + 6));
            float price = stof(result.at(i + 7));
            string description = result.at(i + 8);

            this->addProduct(name, date1, date2, manufacturer, measurementUnit, quantity, price, description);
        }



    }

    printf("Successfully opened %s.", fileName.c_str());
    productFile.close();
}

void Warehouse::printInfo() {
    for (auto &product : products)
    {
        product.printInfo();
        printf("\n");
    }
}

