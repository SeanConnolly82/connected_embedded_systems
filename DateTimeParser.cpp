#include <cstring>
#include <iostream>
#include <sstream>

#include "DateTimeParser.h"

using namespace std;

DateTimeParser::DateTimeParser(const string& datetimeString) {
        cout << datetimeString << endl;
        
        istringstream iss(datetimeString);
        // Read day of the week
        iss >> day;
        // Read date, month, and year, ignore slashes
        char slash;
        iss >> date >> slash >> month >> slash >> year;
        // Read hour, minutes, and seconds, ignore colons
        char colon;
        iss >> hour >> colon >> minutes >> colon >> seconds;
    }

string DateTimeParser::getDay() { 
    return day; 
}
int DateTimeParser::getDate() {
    return date; 
}
int DateTimeParser::getMonth(){
    return month;
}
int DateTimeParser::getYear() { 
    return year; 
}
int DateTimeParser::getHour() {
    return hour;
}
int DateTimeParser::getMinutes() {
    return minutes;
}
int DateTimeParser::getSeconds() {
    return seconds; 
}
