#include <fstream>
#include <iostream>
#include <sstream>
#include "Warehouse.h"


void Warehouse::addProduct(string _name, char *_expiryDate, char *_acceptanceDate, string _manufacturer, string _measurementUnit, float _quantity, float _price, string _description) {

   // Input validation. Exclude commas from all strings.



    Product product(_name, _expiryDate, _acceptanceDate, _manufacturer, _measurementUnit, _quantity, _price, _description);

    uint8_t findNewPlace = 1;

    for (auto &prod : products) {
        if (prod.getName() == _name) {
            findNewPlace = 0;
            break;
        } else
            findNewPlace = 1;
    }


    while (product.getQuantity()) {
        char placement[6] = "\0";

        uint8_t leftover = storage.addProduct(&product, placement, findNewPlace);

//        printf("%.2f\n", product.getQuantity());
        if(product.getQuantity() == 0.0) break;
        if(leftover==1) {
            findNewPlace = 1;
            continue;
        }
        if(leftover==2) {
            if(product.getQuantity() > MAX_ROW_CAPACITY) {
                float left = product.getQuantity() - MAX_ROW_CAPACITY;
                this->addProduct(_name, _expiryDate, _acceptanceDate, _manufacturer, _measurementUnit, left, _price, _description);
                product.setQuantity(MAX_ROW_CAPACITY);
                char placement2[6];
                storage.getEmptyRow(placement2);
                product.setPlacement(placement2);
                products.push_back(product);
                storage.loadProduct(&products.back(), placement2);
//                printf("%s\n\n", products.back().getCSV().c_str());
                break;
            }else {
                product.setPlacement(placement);
                products.push_back(product);
                storage.loadProduct(&products.back(), placement);
//                printf("%s\n\n", products.back().getCSV().c_str());
                break;
            }
        }
//        if(leftover){
//            Product product(_name, _expiryDate, _acceptanceDate, _manufacturer, _measurementUnit, _quantity, _price, placement, _description);
//            products.push_back(product);
//            storage.loadProduct(&products.back(), placement);
//        }
//        printf("Result: %d\n", leftover);

    }
}

void Warehouse::saveProducts(string file) {
    fstream productFile;
    productFile.open(file, ios::out | ios::trunc);

    for (auto &product : products)
    {
        productFile << product.getCSV();
    }

    printf("Successfully saved another %s.\n", file.c_str());
    productFile.close();
}

void Warehouse::saveProducts() {
    fstream productFile;
    productFile.open(fileName, ios::out | ios::trunc);

    for (auto &product : products)
    {
        productFile << product.getCSV();
    }

    printf("Successfully saved %s.\n", fileName.c_str());
    productFile.close();
}

void Warehouse::loadProducts(string file) {
    fileName = file;
    string str;
    ifstream productFile(file);

    if(!productFile.is_open()) {
        printf("An error occurred while opening file %s.\n", fileName.c_str());
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


        for(uint8_t i = 0; i < result.size(); i+=10) {

            char date1[11], date2[11], placement[6];
            uint16_t id = stoi(result.at(i));
            string name = result.at(i + 1);
            strcpy(date1, result.at(i + 2).c_str());
            strcpy(date2, result.at(i + 3).c_str());
            string manufacturer = result.at(i + 4);
            string measurementUnit = result.at(i + 5);
            float quantity = stof(result.at(i + 6));
            float price = stof(result.at(i + 7));
            strcpy(placement, result.at(i + 8).c_str());
            string description = result.at(i + 9);

            Product product(id, name, date1, date2, manufacturer, measurementUnit, quantity, price, placement, description);

            products.push_back(product);
            storage.loadProduct(&products.back(), placement);

        }



    }

    printf("Successfully opened %s.\n", fileName.c_str());
    productFile.close();
}

void Warehouse::printInfo() {
    for (auto &product : products)
    {
        product.printInfo();
        printf("\n");
    }
}

void Warehouse::printStorage() {
    storage.printStorage();
}



//void Warehouse::loadProduct(uint16_t _id, string _name, char *_expiryDate, char *_acceptanceDate, string _manufacturer, string _measurementUnit, float _quantity, float _price, string _description) {
//
//    // Input validation. Exclude commas from all strings.
//
////
////    for (auto &product : products)
////    {
////        char date[11];
////        Date expDate = product.getExpiryDate();
////        expDate.getDate(date);
////        if(!strcmp(date, _expiryDate)){
////            product.addQuantity(_quantity);
////            return;
////        }
////    }
//
//    Product product(_id, _name, _expiryDate, _acceptanceDate, _manufacturer, _measurementUnit, _quantity, _price, _description);
//    products.push_back(product);
//}
