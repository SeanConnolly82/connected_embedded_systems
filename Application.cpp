#include "Application.h"
#include "DateTimeParser.h"

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

// Macro for formatting output
#define FRMT_WIDTH(x) setw(2) << setfill('0') << int(x)


Application::Application(unsigned int bus, unsigned int device):RealTimeClock(bus,device){}

/**
 * @brief Set the date and time in the RTC using a formatted string.
 * @param datetimeString The formatted string containing date and time.
 */
void Application::setDateTime(char* dateTimeString) {
    int secs, mins, hrs, day, date, month, year;
    DateTimeParser dtp;
    dtp.parseDateTime(dateTimeString);
    secs = dtp.getSeconds();
    mins = dtp.getMinutes();
    hrs = dtp.getHour();
    day = dtp.dayStoI(dtp.getDayName());
    date = dtp.getDate();
    month = dtp.getMonth();
    year = dtp.getYear() - 2000;
    RealTimeClock::setDateTime(secs, mins, hrs, day, date, month, year);
}

/**
 * @brief Display the formatted date and time.
 */
void Application::displayDateTime() {
    int secs, mins, hrs, day, date, month, year;
    secs = RealTimeClock::readSeconds();
    mins = RealTimeClock::readMinutes();
    hrs = RealTimeClock::readHours();
    day = RealTimeClock::readDay();
    date = RealTimeClock::readDate();
    month = RealTimeClock::readMonth();
    year = RealTimeClock::readYear();

    DateTimeParser dtp;
    // display the date
    cout << endl << "The current date & time is ";
    cout << dtp.dayItoS(RealTimeClock::bcdToDecimal(day)) << " the ";
    cout << FRMT_WIDTH(RealTimeClock::bcdToDecimal(date)) << "-";
    cout << FRMT_WIDTH(RealTimeClock::bcdToDecimal(month)) << "-";
    cout << FRMT_WIDTH(RealTimeClock::bcdToDecimal(year)) + 2000;
    cout << " " << FRMT_WIDTH(RealTimeClock::bcdToDecimal(hrs)) << ":";
    cout << FRMT_WIDTH(RealTimeClock::bcdToDecimal(mins)) << ":";
    cout << FRMT_WIDTH(RealTimeClock::bcdToDecimal(secs)) << endl << endl;
}

/**
 * @brief Display the formatted temperature.
 */
void Application::displayTemperature() {

    unsigned char tempMSB = RealTimeClock::readTempMSB();
    unsigned char tempLSB = RealTimeClock::readTempLSB();
    // display the temperature
    cout << "The current temperature is ";
    cout << RealTimeClock::binaryFractionToDecimal(tempMSB, tempLSB);
    cout << " degrees Celsius" << endl << endl;
}

/**
 * @brief Set an alarm in the RTC based on user input.
 * @param dydt A string indicating 'dy' for alarm by day or 'dt' for alarm by date.
 * @param alarmTimeString The formatted string containing the alarm time.
 * @param alarmNumber A character indicating Alarm 1 or Alarm 2.
 */
void Application::setAlarm(char* dydt, char* alarmTimeString, char* alarmNumber) {
    int secs, mins, hrs, intDydt;

    DateTimeParser dtp;
    dtp.parseAlarmTime(alarmTimeString);

    secs = dtp.getSeconds();
    mins = dtp.getMinutes();
    hrs = dtp.getHour();
    intDydt = dtp.getDayNumber();

    RealTimeClock::setAlarm(dydt, alarmNumber, secs, mins, hrs, intDydt);

    cout << endl << "Alarm " << *alarmNumber << " set for Day/Date ";
    cout << dtp.getDayNumber() << " at " << FRMT_WIDTH(hrs) << ":";
    cout << FRMT_WIDTH(mins) << ":" << FRMT_WIDTH(secs) << endl;
}

/**
 * Main function
*/
int main(int argc, char *argv[]) {

    int alarm;
    Application rtc(1,0x68);
    if (argc > 1) {
        if (strcmp(argv[1], "set-time") == 0) {
            rtc.setDateTime(argv[2]);
        } else if (strcmp(argv[1], "set-alarm") == 0) {
            rtc.setAlarm(argv[2], argv[3], argv[4]);
            // Interrupt is enabled
            rtc.enableInterrupt(argv[4]);
        } else if (strcmp(argv[1], "start-sqw") == 0) {
            rtc.outputSquareWave(argv[2]);
        } else if (strcmp(argv[1], "stop-sqw") == 0) {
            rtc.stopSquareWave();
        }
    }
    rtc.displayDateTime();
    rtc.displayTemperature();
    
    return 0;
}
