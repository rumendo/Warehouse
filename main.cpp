#include <iostream>
#include <cstring>
#include <sstream>
#include "Product.h"
#include "Warehouse.h"
#include "Storage.h"

using namespace std;

void run_cli();

int main() {
    run_cli();
    return 0;
}

void run_cli(){
    Warehouse warehouse;
    bool closed = true;
    while(true) {
        string str;
        getline(cin, str);
        vector<string> result;
        stringstream s_stream(str);
        while (s_stream.good()) {
            string substr;
            getline(s_stream, substr, ' ');
            result.push_back(substr);
        }

        if(result[0]=="help" || result[0]=="?") {
            printf("The following commands are supported:\n"
                   "open <file>     opens <file>\n"
                   "close           closes currently opened file\n"
                   "save            saves the currently open file\n"
                   "saveas <file>   saves the currently open file in <file>\n"
                   "help            prints this information\n"
                   "exit            exists the program\n\n"
                   "Program specific commands:\n"
                   "print           displays available products in the warehouse\n"
                   "add             adds a product based on supplied information\n"
                   "remove          removes product given a name and quantity\n"
//                   "log <from> <to> displays all warehouse I/O operations given a date range\n"
                   "clean           removes products with due expiration dates\n"
            );
        }

        if(result[0]=="exit") {
            break;
        }

        if(result[0]=="open") {
            closed = false;
            warehouse.loadProducts(result[1]);
        }

        if(closed) continue;

        if(result[0]=="close") {
            warehouse.close();
            closed = true;
        }

        if(result[0]=="save") {
            warehouse.saveProducts();
        }

        if(result[0]=="saveas") {
            warehouse.saveProducts(result[1]);
        }

        if(result[0]=="print") {
            warehouse.printInfo();
        }

        if(result[0]=="add") {
            uint8_t valid = 0;
            char choice = 'n';
            do {
                char date1[11], date2[11];
                string date1Temp, date2Temp;
                string name;
                string manufacturer;
                string measurementUnit;
                float quantity = 0;
                float price = 0;
                string description;

                printf("Enter product name: \n");
                getline(cin, name);

                printf("Enter product expiration date (yyyy/mm/dd): \n");
                getline(cin, date1Temp);
                strcpy(date1, date1Temp.c_str());

                time_t now = time(nullptr);
                tm *timeNow = localtime(&now);
                string time;

                if (1 + timeNow->tm_mon < 10)
                    time += to_string(1900 + timeNow->tm_year) + '/' + '0' + to_string(1 + timeNow->tm_mon) + '/';
                else
                    time += to_string(1900 + timeNow->tm_year) + '/' + to_string(1 + timeNow->tm_mon) + '/';

                if (timeNow->tm_mday < 10)
                    time += '0' + to_string(timeNow->tm_mday);
                else
                    time += to_string(timeNow->tm_mday);

                Date currentTime(time.c_str());
                currentTime.getDate(date2);


                printf("Enter product manufacturer: \n");
                getline(cin, manufacturer);

                printf("Enter measurement unit: \n");
                getline(cin, measurementUnit);

                printf("Enter product quantity: \n");
                cin >> quantity;

                printf("Enter product price/%s: \n", measurementUnit.c_str());
                cin >> price;

                printf("Enter a comment: \n");
                getline(cin, description);


                valid = warehouse.addProduct(name, date1, date2, manufacturer, measurementUnit, quantity, price, description);
                choice = 'n';
                if (valid==1) {
                    printf("Please exclude any commas from the input data.\nWould you want to try again (y/n)?: ");
                    cin >> choice;
                    printf("\n");
                }else if (valid==2) {
                    printf("Invalid data. Please check the expiration date format.\nWould you want to try again (y/n)?: ");
                    cin >> choice;
                    printf("\n");
                }else if (valid==3) {
                    printf("Invalid quantity and/or price. Please enter a number between 0 and 520000.\nWould you want to try again (y/n)?: ");
                    cin >> choice;
                    printf("\n");
                }
                
                
            } while(valid && ( choice == 'Y' || choice == 'y'));
        }

        if(result[0]=="remove") {
            printf("Enter product name: \n");
            string name;
            getline(cin, name);
            printf("Enter quantity to remove: \n");
            float quantity = 0;
            cin >> quantity;
            warehouse.removeProduct(name, quantity);
        }

        if(result[0]=="log") {
            char dateFrom[11], dateTo[11];
            strcpy(dateFrom, result[1].c_str());
            strcpy(dateTo, result[2].c_str());
        }

        if(result[0]=="clean") {
            warehouse.clean();
        }
    }
}
