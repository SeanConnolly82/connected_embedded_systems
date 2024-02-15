#include "I2CDevice.h"
#include "RealTimeClock.h"
#include<iostream>
#include<iomanip>

using namespace std;

#define FRMT_WIDTH(x) setw(2) << setfill('0') << int(x)

RealTimeClock::RealTimeClock(unsigned int bus, unsigned int device):I2CDevice(bus,device){
    std::cout << "RTC created\n";
}
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
    return I2CDevice::readRegister(DS3231_MON_ADDR);
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
    cout << endl << "The time is ";
    cout << FRMT_WIDTH(bcdToDecimal(this->hours)) << ":";
    cout << FRMT_WIDTH(bcdToDecimal(this->minutes)) << ":";
    cout << FRMT_WIDTH(bcdToDecimal(this->seconds)) << endl;
    cout << "The date is ";
    cout << this->weekday[(bcdToDecimal(this->day))-1] << " the ";
    cout << FRMT_WIDTH(bcdToDecimal(this->date)) << "-";
    cout << FRMT_WIDTH(bcdToDecimal(this->month)) << "-";
    cout << FRMT_WIDTH(bcdToDecimal(this->year)) + 2000 << endl;
}