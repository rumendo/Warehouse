#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include "Warehouse.h"


void Warehouse::addProduct(string _name, char *_expiryDate, char *_acceptanceDate, string _manufacturer, string _measurementUnit, float _quantity, float _price, string _description) {

   // Input validation. Exclude commas from all strings.



    Product product(_name, _expiryDate, _acceptanceDate, _manufacturer, _measurementUnit, _quantity, _price, _description);

    uint16_t findNewPlace = 1;

    for (auto &prod : products) {
        if (prod.getName() == _name) {
            findNewPlace = 0;
            break;
        } else
            findNewPlace = 1;
    }


    while (product.getQuantity()) {
        char placement[6] = "\0";
        uint16_t leftover = storage.addProduct(&product, placement, findNewPlace);

        if(product.getQuantity() == 0.0) break;

        if(leftover==1) {
            findNewPlace = 1;
            continue;
        }

        if(leftover==2) {
            if (product.getQuantity() > MAX_ROW_CAPACITY) {
                float left = product.getQuantity() - MAX_ROW_CAPACITY;
                this->addProduct(_name, _expiryDate, _acceptanceDate, _manufacturer, _measurementUnit, left, _price,
                                 _description);
                product.setQuantity(MAX_ROW_CAPACITY);
                char placement2[6];
                storage.getEmptyRow(placement2);
                product.setPlacement(placement2);
                products.push_back(product);
                storage.loadProduct(&products.back(), placement2);
            } else {
                product.setPlacement(placement);
                products.push_back(product);
                storage.loadProduct(&products.back(), placement);
            }
            break;
        }

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


        for(uint32_t i = 0; i < result.size(); i+=9) {

            char date1[11], date2[11], placement[6];
            string name = result.at(i);
            strcpy(date1, result.at(i + 1).c_str());
            strcpy(date2, result.at(i + 2).c_str());
            string manufacturer = result.at(i + 3);
            string measurementUnit = result.at(i + 4);
            float quantity = stof(result.at(i + 5));
            float price = stof(result.at(i + 6));
            strcpy(placement, result.at(i + 7).c_str());
            string description = result.at(i + 8);

            Product product(name, date1, date2, manufacturer, measurementUnit, quantity, price, placement, description);

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
        char place[6];
        product.getPlacement(place);
        printf("\n");
    }
}

void Warehouse::printStorage() {
    storage.printStorage();
}

void Warehouse::removeProduct(string name, float quantity) {

    // Check for product availability
    float availability = 0.0;

    for (auto &product : products) {
        if (product.getName() == name)
            availability += product.getQuantity();
    }

    if (availability == 0.0) {
        printf("%s is out of stock.\n", name.c_str());
        return;
    }


    // If requested quantity exceeds availability, customer is asked to make a decision.
    if (availability < quantity) {
        printf("We're in short supply of %s.\nWe have the following amount in storage:\n", name.c_str());
        for (auto &product : products) {
            if(product.getName() == name) {
                char expiryDate[11];
                product.getDate(expiryDate);
                printf("%.2f %s %s with an expiration date of %s\n", product.getQuantity(), product.getMU().c_str(), product.getName().c_str(), expiryDate);
            }
        }
        char response = 'n';
        printf("Would you want what's left in stock? y/n: ");
        cin >> response;
        printf("\n");

        if(response=='y'||response=='Y') {
            this->removeProduct(name, availability);
            quantity = 0.0;
        } else return;
    }

    while (quantity != 0.0) {
        uint32_t oldestExpiryDate = 42000000;
        for (auto &product : products) {
            if (product.getName() == name) {
                if (product.getExpiryDateTimestamp() < oldestExpiryDate)
                    oldestExpiryDate = product.getExpiryDateTimestamp();
            }
        }

        uint16_t productToRemove = 0;
        for (auto &product : products) {
            if (product.getName() == name && product.getExpiryDateTimestamp() == oldestExpiryDate) {
                if (product.getQuantity() > quantity) {
                    char place[6];
                    product.getPlacement(place);
                    product.setQuantity(product.getQuantity()-quantity);
                    printf("%.2f %s %s was removed from %s\n", quantity, product.getMU().c_str(), product.getName().c_str(), place);
                    quantity = 0.0;
                    break;
                }else if(product.getQuantity() == quantity) {
                    char place[6];
                    product.getPlacement(place);
                    printf("%.2f %s %s was removed from %s\n", quantity, product.getMU().c_str(), product.getName().c_str(), place);
                    quantity = 0.0;
                    storage.setNull(place);
                    products.erase(products.begin() + productToRemove);
                    break;
                }else if(product.getQuantity() < quantity) {
                    char place[6];
                    product.getPlacement(place);
                    quantity -= product.getQuantity();
                    printf("%.2f %s %s was removed from %s\n", product.getQuantity(), product.getMU().c_str(), product.getName().c_str(), place);
                    storage.setNull(place);
                    products.erase(products.begin() + productToRemove);
                    break;
                }
            }
            productToRemove++;
        }
    }
}

void Warehouse::clean() {

    printf("Cleanup started..\n");

    time_t now = time(nullptr) + DAYS_TO_SPOIL * 24 * 60 * 60;
    tm *timeNow = localtime(&now);
    string time;

    if(1 + timeNow->tm_mon < 10)
        time += to_string(1900 + timeNow->tm_year) + '/' + '0' + to_string(1 + timeNow->tm_mon) + '/';
    else
        time += to_string(1900 + timeNow->tm_year) + '/' + to_string(1 + timeNow->tm_mon) + '/';

    if (timeNow->tm_mday < 10)
        time += '0' + to_string(timeNow->tm_mday);
    else
        time += to_string(timeNow->tm_mday);

    Date spoilTime(time.c_str());

    for(uint8_t i=0; i<10; i++) {
        for (auto &product : products) {
            if (spoilTime.getTimestamp() + DAYS_TO_SPOIL > product.getExpiryDateTimestamp()) {
                this->removeProduct(product.getName(), product.getQuantity());
            }
        }
    }
}
