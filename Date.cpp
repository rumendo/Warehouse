#include <cstring>
#include <cmath>
#include "Date.h"

Date::Date(const char _date[11]) {
    strcpy(date, _date);

    for(int i=0, j=0; i<10; i++, j++)
        if(_date[i]!='/')
            timestamp += (_date[i] - '0') * pow(10, 7 - j);
        else j--;
}

Date::Date(Date *_Date) {
    strcpy(this->date, _Date->date);
    this->timestamp = _Date->timestamp;
}

void Date::getDate(char _date[11]) {
    strcpy(_date, date);
}

int8_t Date::compare(Date comparedDate) {
    if(this->timestamp > comparedDate.timestamp)
        return 1;
    if(this->timestamp < comparedDate.timestamp)
        return -1;

    return 0;
}

uint32_t Date::getTimestamp() {
    return timestamp;
}