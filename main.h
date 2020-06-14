#include <cstdint>

// Stellt ein Datum im gregorianischen Kalender dar:
struct GregorianCalendar
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint_fast8_t sec;
};

// Enthält die Tage der Monate in einem nicht-Schaltjahr
const uint8_t DaysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Prototypen: Operatoren sind damit auch in anderen Files nutzbar
GregorianCalendar &operator++(GregorianCalendar &temp, int);

bool checkforLeapYear_gregorian(uint16_t year);