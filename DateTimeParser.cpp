#include <iostream>
#include <sstream>

#include "DateTimeParser.h"

using namespace std;

/**
 * Constructor for the DateTimeParser class
 */
DateTimeParser::DateTimeParser() {}

/**
 * Parse a datetime string in the format 'Day dd/MM/yyyy hh:mm:ss'
 * @param datetimeString An address reference for a datetime string
 */
void DateTimeParser::parseDateTime(const string& datetimeString) {

    istringstream iss(datetimeString);
    // Read day of the week
    iss >> this->dayName;
    // Read date, month, and year, ignore slashes
    char slash;
    iss >> this->date >> slash >> this->month >> slash >> this->year;
    // Read hour, minutes, and seconds, ignore colons
    char colon;
    iss >> this->hour >> colon >> this->minutes >> colon >> this->seconds;
}

/**
 * Parse a datetime string in the format 'Day hh:mm:ss' or 'dd hh:mm:ss'
 * @param datetimeString An address reference for a datetime string
 */
void DateTimeParser::parseAlarmTime(const string& alarmTimeString) {

    istringstream iss(alarmTimeString);
    // Read the weekday name or the date
    iss >> this->dayNumber;
    // Read hour, minutes, and seconds, ignore colons
    char colon;
    iss >> this->hour >> colon >> this->minutes >> colon >> this->seconds;
}

/**
 * Converts the name of a day of the week to a corresponding integer value
 * from 1 (Monday) to 7 (Sunday)
 * @param dayName the day to convert to int
 * @return an integer value representing the day of the week, from 1 to 7
 */

int DateTimeParser::dayStoI(string dayName) {
    
    for (int i = 0; i<7; i++) {
        if (this->daysArr[i] == dayName) {
            return i + 1;
        }
    }
    cout << "Please enter a valid day" << endl;
    return 0;
}

/**
 * Converts an integer value to the name of a day of the week. Acceptable
 * inputs range from 1 (returns "Monday") to 7 (returns "Sunday").
 * @param dayName an int in the range 1 to 7
 * @return an string value for the weekday name
 */
string DateTimeParser::dayItoS(int dayNumber) {
    return this->daysArr[dayNumber - 1];
}

/**
 * Getters for the DateTimeParser member variables
*/
string DateTimeParser::getDayName() {
    return this->dayName; 
}
int DateTimeParser::getDayNumber() {
    return this->dayNumber; 
}
int DateTimeParser::getDate() {
    return this->date; 
}
int DateTimeParser::getMonth(){
    return this->month;
}
int DateTimeParser::getYear() { 
    return this->year; 
}
int DateTimeParser::getHour() {
    return this->hour;
}
int DateTimeParser::getMinutes() {
    return this->minutes;
}
int DateTimeParser::getSeconds() {
    return this->seconds; 
}
