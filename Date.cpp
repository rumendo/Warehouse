#include <cstring>
#include "Date.h"

Date::Date() {

}

Date::Date(const char _date[11]) {
    strcpy(date, _date);

    timestamp += (_date[0] - '0') * 10000000;
    timestamp += (_date[1] - '0') * 1000000;
    timestamp += (_date[2] - '0') * 100000;
    timestamp += (_date[3] - '0') * 10000;

    timestamp += (_date[5] - '0') * 1000;
    timestamp += (_date[6] - '0') * 100;

    timestamp += (_date[8] - '0') * 10;
    timestamp += (_date[9] - '0');
}

Date::Date(Date *_Date) {
    strcpy(this->date, _Date->date);
    this->timestamp = _Date->timestamp;
}

void Date::getDate(char _date[11]) {
    strcpy(_date, date);
}

uint16_t Date::getYear() {
    return timestamp/10000 % 10000;
}

uint8_t Date::getMonth() {
    return timestamp/100 % 100;
}

uint8_t Date::getDay() {
    return timestamp % 100 - 1;
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
