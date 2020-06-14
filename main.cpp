#include "main.h"


// Inkrementiert GregorianCalendar-Objekt um 1 Sekunde
GregorianCalendar& operator++(GregorianCalendar& temp, int) {
    // Anders als bei der Überladung des += Operators, wird hier immer nur um eine Sekunde inkrementiert!
    // es entfallen also Prüfungen bei denen denen ein größerer Zeitraum übersprungen wird.

    // ***************************
    //          lambdas
    // ***************************

    // Liefert die Anzahl Tage des Monats abhängig vom Schaltjahr/Nicht-Schaltjahr
    const auto getNumberOfDaysInMonth = [](uint16_t year, uint8_t month) -> uint8_t {
        const uint8_t dayspermonth[] = {31,28,31,30,31,30,31,31,30,31,30,31}; // const ermöglicht Optimierungen
        if ((month == 2) && ((year % 4 == 0) && (!(year % 100 == 0) | (year % 400 == 0)))) return 29; // Um Wert im Leap Year nicht zu erhöhen, in diesem Fall Konstante 29 zurückgeben
        return dayspermonth[month-1]; // ansonsten Wert aus Array entnehmen
    };


    // *******************************
    //          Algorithmus
    // *******************************

    if (temp.sec +1 == 60) {
        // Minute wird inkrementiert
        if(temp.minute +1 == 60) {
            // Stunde wird inkrementiert
            if (temp.hour +1 == 24) {
                // Tag wird inkrementiert
                if (temp.day +1 > getNumberOfDaysInMonth(temp.year, temp.month)) {
                    // Monat wird inkrementiert
                    if (temp.month +1 > 12) {
                        // Jahr wird inkrementiert
                        temp.year++;
                        temp.month = 1;
                    } else{
                        // Nur Monat erhöhen
                        temp.month++;
                    }
                    // Tag wieder auf 1 setzen
                    temp.day = 1;
                } else{
                    // Nur Tag erhöhen
                    temp.day++;
                }
                // Stunde wieder auf 0 setzen:
                temp.hour = 0;
            } else{
                // Nur Stunde erhöhen
                temp.hour++;
            }
            // Minute wieder auf 0 setzen:
            temp.minute = 0;
        } else {
            // Nur Minute erhöhen
            temp.minute++;
        }
        // Sekunde wieder auf 0 setzen:
        temp.sec = 0;
    } else {
        // Nur Sekunde erhöhen
        temp.sec++;
    }

    return temp;
}


GregorianCalendar start = {2020,6,14,23,58,0}; // Startzeitpunkt


static Application DateIncremention("Date Incremention");


class DateIncrementor : StaticThread<> {
    void run() {
        while (1)
        {
            start++;
            
            AT(NOW() + 1 * SECONDS);
        }
        
    }
} GoForIt;

class DatePrinter : StaticThread<> {
    void run() {
        while (1)
        {
            PRINTF("\r");
            PRINTF("%02d.%02d.%d %02d:%02d:%02d", (int)start.day, (int)start.month, (int)start.year, (int)start.hour, (int)start.minute, (int)start.sec);
            AT(NOW() + 500 * MILLISECONDS);
        }
        
    }
} ShowIt;
