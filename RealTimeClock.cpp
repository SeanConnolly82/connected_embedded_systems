#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>

#include "I2CDevice.h"
#include "RealTimeClock.h"
#include "DateTimeParser.h"

using namespace std;

#define FRMT_WIDTH(x) setw(2) << setfill('0') << int(x)

RealTimeClock::RealTimeClock(unsigned int bus, unsigned int device):I2CDevice(bus,device){}

unsigned char RealTimeClock::bcdToDecimal(unsigned char bcdValue) {
    return ((bcdValue & 0xF0) >> 4) * 10 + (bcdValue & 0x0F);
}
unsigned char RealTimeClock::decimalToBcd(unsigned char decimalValue) {
    return ((decimalValue / 10) << 4) | (decimalValue % 10);
}
unsigned char RealTimeClock::readSeconds(){
    return I2CDevice::readRegister(DS3231_SEC_ADDR);
}
unsigned char RealTimeClock::readMinutes(){
    return I2CDevice::readRegister(DS3231_MIN_ADDR);
}
unsigned char RealTimeClock::readHours(){
    return I2CDevice::readRegister(DS3231_HRS_ADDR);
}
unsigned char RealTimeClock::readDay(){
    return I2CDevice::readRegister(DS3231_DAY_ADDR);
}
unsigned char RealTimeClock::readDate(){
    return I2CDevice::readRegister(DS3231_DTE_ADDR);
}
unsigned char RealTimeClock::readMonth(){
    return I2CDevice::readRegister(DS3231_MON_ADDR);
}
unsigned char RealTimeClock::readYear(){
    return I2CDevice::readRegister(DS3231_YRS_ADDR);
}
int RealTimeClock::setSeconds(unsigned char seconds){
    return I2CDevice::writeRegister(DS3231_SEC_ADDR, seconds);
}
int RealTimeClock::setMinutes(unsigned char minutes){
    return I2CDevice::writeRegister(DS3231_MIN_ADDR, minutes);
}
int RealTimeClock::setHours(unsigned char hours){
    return I2CDevice::writeRegister(DS3231_HRS_ADDR, hours);
}
int RealTimeClock::setDay(unsigned char day){
    return I2CDevice::writeRegister(DS3231_DAY_ADDR, day);
}
int RealTimeClock::setDate(unsigned char date){
    return I2CDevice::writeRegister(DS3231_DTE_ADDR, date);
}
int RealTimeClock::setMonth(unsigned char month){
    return I2CDevice::writeRegister(DS3231_MON_ADDR, month);
}
int RealTimeClock::setYear(unsigned char year){
    return I2CDevice::writeRegister(DS3231_YRS_ADDR, year);
}
void RealTimeClock::readDateTime() {
    this->seconds = readSeconds();
    this->minutes = readMinutes();
    this->hours = readHours();
    this->day = readDay();
    this->date = readDate();
    this->month = readMonth();
    this->year = readYear();
}

void RealTimeClock::displayDateTime() {
    readDateTime();
    DateTimeParser dtp;
    // display the date
    cout << "The date is ";
    // cout << dtp.getDayName(bcdToDecimal(this->day)) << " the ";
    cout << FRMT_WIDTH(bcdToDecimal(this->date)) << "-";
    cout << FRMT_WIDTH(bcdToDecimal(this->month)) << "-";
    cout << FRMT_WIDTH(bcdToDecimal(this->year)) + 2000 << endl;
    // display the time
    cout << endl << "The time is ";
    cout << FRMT_WIDTH(bcdToDecimal(this->hours)) << ":";
    cout << FRMT_WIDTH(bcdToDecimal(this->minutes)) << ":";
    cout << FRMT_WIDTH(bcdToDecimal(this->seconds)) << endl << endl;
    
}

void RealTimeClock::setDateTime(char *datetimeString) {
    DateTimeParser dtp;
    dtp.parseDateTime(datetimeString);
    setSeconds(decimalToBcd(dtp.getSeconds()));
    setMinutes(decimalToBcd(dtp.getMinutes()));
    setHours(decimalToBcd(dtp.getHour()));
    setDay(decimalToBcd(dtp.DayStoI(dtp.getDay())));
    setDate(decimalToBcd(dtp.getDate()));
    setMonth(decimalToBcd(dtp.getMonth()));
    setYear(decimalToBcd(dtp.getYear() - 2000));
}

// Set alarm 1
int RealTimeClock::setAlarm1Seconds(unsigned char seconds){
    return I2CDevice::writeRegister(DS3231_ALRM1_SEC_ADDR, seconds);
}
int RealTimeClock::setAlarm1Minutes(unsigned char minutes){
    return I2CDevice::writeRegister(DS3231_ALRM1_MIN_ADDR, minutes);
}
int RealTimeClock::setAlarm1Hours(unsigned char hours){
    return I2CDevice::writeRegister(DS3231_ALRM1_HRS_ADDR, hours);
}
int RealTimeClock::setAlarm1DyDt(unsigned char day){
    return I2CDevice::writeRegister(DS3231_ALRM1_DYDT_ADDR, day);
}
// Set alarm 2
int RealTimeClock::setAlarm2Minutes(unsigned char minutes){
    return I2CDevice::writeRegister(DS3231_ALRM2_MIN_ADDR, minutes);
}
int RealTimeClock::setAlarm2Hours(unsigned char hours){
    return I2CDevice::writeRegister(DS3231_ALRM2_HRS_ADDR, hours);
}
int RealTimeClock::setAlarm2DyDt(unsigned char day){
    return I2CDevice::writeRegister(DS3231_ALRM2_DYDT_ADDR, day);
}

int RealTimeClock::setDyDt(char* dydt, string day) {

    string dydtStr(dydt);
    DateTimeParser dtp;
  
    if (dydtStr == "dy") {
        return dtp.DayStoI(day) + bcdToDecimal(0x40);
    } else if (dydtStr == "dt") {
        return stoi(day);
    } else {
        cout << "Please enter dy for alarm by day, or dt for alarm by date" << endl << endl;
        return 0;
    }
}

void RealTimeClock::setAlarm(char *dydt, char *alarmTimeString, char *alarmNumber) {
    int secs, mins, hrs, intDydt;

    DateTimeParser dtp;
    dtp.parseAlarmTime(alarmTimeString);

    secs = dtp.getSeconds();
    mins = dtp.getMinutes();
    hrs = dtp.getHour();
    intDydt = setDyDt(dydt, dtp.getDay());

    if (*alarmNumber == '1') {
        setAlarm1Seconds(decimalToBcd(secs));
        setAlarm1Minutes(decimalToBcd(mins));
        setAlarm1Hours(decimalToBcd(hrs));
        setAlarm1DyDt(decimalToBcd(intDydt));
    } else if (*alarmNumber == '2') {
        setAlarm2Minutes(decimalToBcd(dtp.getMinutes()));
        setAlarm2Hours(decimalToBcd(dtp.getHour()));
        setAlarm2DyDt(decimalToBcd(intDydt));
    }
}

void RealTimeClock::enableOutput() {
    // Set the output bit
}