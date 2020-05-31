#include "Storage.h"

Storage::Storage() {

    for(uint8_t shelf = 0; shelf < NUMBER_OF_SHELFS; shelf++) {
        vector<Product*> temp;
        for(uint8_t row = 0; row < ROWS_IN_SHELF; row++) {
            temp.push_back(nullptr);
        }
        shelfs.push_back(temp);
    }


}

void Storage::printStorage() {
    for(auto &shelf : shelfs) {
        for(auto &row : shelf) {
            printf("%p ", row);
        }
        printf("\n");
    }
}

uint8_t Storage::addProduct(Product *product, char *placement, uint8_t findNewPlace) {
    uint16_t shelf_number = 0;
        for(auto &shelf : shelfs) {
        uint8_t row_number = 0;

        for(auto &row : shelf) {
            if ((findNewPlace && row == nullptr ) || (row != nullptr && row->getExpiryDateTimestamp() != product->getExpiryDateTimestamp() )) {

                string place;
                if(shelf_number<10) {
                    place = "00" + to_string(shelf_number) + '/' + to_string(row_number);
                }else if(shelf_number>=10 && shelf_number < 100) {
                    place = "0" + to_string(shelf_number) + '/' + to_string(row_number);
                }else
                    place = to_string(shelf_number) + '/' + to_string(row_number);

                strcpy(placement, place.c_str());
                return 2;
            }



            if(row != nullptr) {

                if (row->getQuantity() <= MAX_ROW_CAPACITY && row->getName() == product->getName() && row->getExpiryDateTimestamp() == product->getExpiryDateTimestamp()) {
                    float availableRowCapacity = MAX_ROW_CAPACITY - row->getQuantity();

                    if (availableRowCapacity >= product->getQuantity()) {
                        row->addQuantity(product->getQuantity());
                        return 0;
                    }

                    float leftover = product->getQuantity() - availableRowCapacity;
                    row->addQuantity(availableRowCapacity);
                    product->setQuantity(leftover);

                    return 1;
                }
            }
            row_number++;
        }
        shelf_number++;
    }

    return 0;
}

void Storage::loadProduct(Product *product, char *placement) {
    uint16_t shelfNumber = (placement[0] - '0') * 100 + (placement[1] - '0') * 10 + (placement[2] - '0');
    uint16_t rowNumber = placement[4] - '0';

    shelfs[shelfNumber][rowNumber] = product;
}

void Storage::getEmptyRow(char *placement) {
    uint16_t shelf_number = 0;
    for (auto &shelf : shelfs) {
        uint8_t row_number = 0;

        for (auto &row : shelf) {
            if(row == nullptr) {
                string place;
                if (shelf_number < 10) {
                    place = "00" + to_string(shelf_number) + '/' + to_string(row_number);
                } else if (shelf_number >= 10 && shelf_number < 100) {
                    place = "0" + to_string(shelf_number) + '/' + to_string(row_number);
                } else
                    place = to_string(shelf_number) + '/' + to_string(row_number);


                strcpy(placement, place.c_str());
            }
            row_number++;
        }
        shelf_number++;
    }
}

void Storage::setNull(char *placeToRemove) {
    for(auto &shelf : shelfs) {
        for(auto &row : shelf) {
            if(row != nullptr) {
                char place[6];
                row->getPlacement(place);
                if (!strcmp(placeToRemove, place)) {
                    row = nullptr;
                    return;
                }
            }
        }
    }
}
