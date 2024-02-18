#include <cstring>
#include <iostream>
#include <sstream>

#include "DateTimeParser.h"

using namespace std;

DateTimeParser::DateTimeParser() {}

void DateTimeParser::parseDateTime(const string& datetimeString) {

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

void DateTimeParser::parseAlarmTime(const string& alarmTimeString) {

    istringstream iss(alarmTimeString);
    // Read the weekday name or the date
    iss >> day;
    // Read hour, minutes, and seconds, ignore colons
    char colon;
    iss >> hour >> colon >> minutes >> colon >> seconds;
}

int DateTimeParser::DayStoI(string dayName) {
    
    for (int i = 0; i<7; i++) {
        if (daysArr[i] == dayName) {
            return i + 1;
        }
    }
    cout << "Please enter a valid day" << endl;
    return 0;
}

string DateTimeParser::DayItoS(int dayNumber) {
    return daysArr[dayNumber+1];
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
