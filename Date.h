#ifndef WAREHOUSE_DATE_H
#define WAREHOUSE_DATE_H


#include <stdint-gcc.h>

class Date {
private:
    char date[11];
    uint32_t timestamp = 0;
public:
    Date();
    Date(const char[11]);
    Date(Date*);

    void getDate(char*); // Fills date in a char array.
    uint32_t getTimestamp(); // Returns date is following format: yyyymmdd.

    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();

    /// Compares to another date.
    /// Returns integer:
    /// 1 - If compared date is closer to AD relative to the object called upon.
    /// 0 - If compared dates match.
    /// -1 - If compared date is further away from AD relative to the object called upon.
    int8_t compare(Date);

};


#endif //WAREHOUSE_DATE_H
