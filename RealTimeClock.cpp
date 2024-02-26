#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>

#include "I2CDevice.h"
#include "RealTimeClock.h"

using namespace std;

/**
 * @brief Constructor for the RealTimeClock class, inheriting from I2CDevice.
 * @param bus The I2C bus number.
 * @param device The I2C device address.
 */
RealTimeClock::RealTimeClock(unsigned int bus, unsigned int device):I2CDevice(bus,device){}

/**
 * @brief Convert Binary-Coded Decimal (BCD) to decimal.
 * @param bcdValue The BCD value to convert.
 * @return The decimal equivalent.
 */
unsigned char RealTimeClock::bcdToDecimal(unsigned char bcdValue) {
    return ((bcdValue & 0xF0) >> 4) * 10 + (bcdValue & 0x0F);
}

/**
 * @brief Convert decimal to Binary-Coded Decimal (BCD).
 * @param decimalValue The decimal value to convert.
 * @return The BCD equivalent.
 */
unsigned char RealTimeClock::decimalToBcd(unsigned char decimalValue) {
    return ((decimalValue / 10) << 4) | (decimalValue % 10);
}

/**
 * @brief Set a specific bit in a byte to 1.
 * @param byte The byte to modify.
 * @param position The position of the bit to set.
 */
void RealTimeClock::setBitToOne(unsigned char &byte, int position) {
    byte |= (1 << position);
}
/**
 * @brief Set a specific bit in a byte to 0.
 * @param byte The byte to modify.
 * @param position The position of the bit to set.
 */
void RealTimeClock::setBitToZero(unsigned char &byte, int position) {
    byte &= ~(1 << position);
}

/**
 * @brief Converts a 2s complement binary value to its integer equivalent
 * @param binaryValue The binary value from the register.
 * @return The integer decimal value equivalent.
 */
int RealTimeClock::binaryToDecimal(unsigned char binaryValue) {

    int value = static_cast<int>(binaryValue);
    // Check the sign bit
    bool isNegative = (value & 0x80) != 0;
    // If negative, find magnitude by 1's complement and add 1
    if (isNegative) {
        value = -(static_cast<int>(~value) + 1);
    }
    return value;
}

/**
 * @brief Convert a binary integer and binary fraction to a decimal number.
 * @param binaryInt 8-bit binary integer part.
 * @param binaryFraction 8-bit binary fraction part.
 * @return The decimal representation of the binary number.
 */
double RealTimeClock::binaryFractionToDecimal(unsigned char binaryInt, unsigned char binaryFraction) {
    double result = 0.0;
    // Convert integer part
    int integerPart = this->binaryToDecimal(binaryInt);
    // Convert fractional part
    for (int i = 7; i >= 0; --i) {
        result += ((binaryFraction >> (7 - i)) & 1) * pow(2, -(i + 1));
    }
    return integerPart + result;
}

/**
 * @brief Read the seconds from the Real-Time Clock (RTC).
 * @return The seconds value.
 */
unsigned char RealTimeClock::readSeconds(){
    return I2CDevice::readRegister(DS3231_SEC_ADDR);
}

/**
 * @brief Read the minutes from the Real-Time Clock (RTC).
 * @return The minutes value.
 */
unsigned char RealTimeClock::readMinutes(){
    return I2CDevice::readRegister(DS3231_MIN_ADDR);
}

/**
 * @brief Read the hours from the Real-Time Clock (RTC).
 * @return The hours value.
 */
unsigned char RealTimeClock::readHours(){
    return I2CDevice::readRegister(DS3231_HRS_ADDR);
}

/**
 * @brief Read the day from the Real-Time Clock (RTC).
 * @return The day value.
 */
unsigned char RealTimeClock::readDay(){
    return I2CDevice::readRegister(DS3231_DAY_ADDR);
}

/**
 * @brief Read the date from the Real-Time Clock (RTC).
 * @return The date value.
 */
unsigned char RealTimeClock::readDate(){
    return I2CDevice::readRegister(DS3231_DTE_ADDR);
}

/**
 * @brief Read the month from the Real-Time Clock (RTC).
 * @return The month value.
 */
unsigned char RealTimeClock::readMonth(){
    return I2CDevice::readRegister(DS3231_MON_ADDR);
}

/**
 * @brief Read the year from the Real-Time Clock (RTC).
 * @return The year value.
 */
unsigned char RealTimeClock::readYear(){
    return I2CDevice::readRegister(DS3231_YRS_ADDR);
}

/**
 * @brief Read the temperature MSB from the Real-Time Clock (RTC).
 * @return The temperature MSB value.
 */
unsigned char RealTimeClock::readTempMSB() {
    return I2CDevice::readRegister(DS3231_TEMP_MSB);
}

/**
 * @brief Read the temperature LSB from the Real-Time Clock (RTC).
 * @return The temperature LSB value.
 */
unsigned char RealTimeClock::readTempLSB() {
    return I2CDevice::readRegister(DS3231_TEMP_LSB);
}

/**
 * @brief Set the seconds in the Real-Time Clock (RTC).
 * @param seconds The seconds value to set.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setSeconds(unsigned char seconds){
    return I2CDevice::writeRegister(DS3231_SEC_ADDR, seconds);
}

/**
 * @brief Set the minutes in the Real-Time Clock (RTC).
 * @param minutes The minutes value to set.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setMinutes(unsigned char minutes){
    return I2CDevice::writeRegister(DS3231_MIN_ADDR, minutes);
}

/**
 * @brief Set the hours in the Real-Time Clock (RTC).
 * @param hours The hours value to set.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setHours(unsigned char hours){
    return I2CDevice::writeRegister(DS3231_HRS_ADDR, hours);
}

/**
 * @brief Set the day in the Real-Time Clock (RTC).
 * @param day The day value to set.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setDay(unsigned char day){
    return I2CDevice::writeRegister(DS3231_DAY_ADDR, day);
}

/**
 * @brief Set the date in the Real-Time Clock (RTC).
 * @param date The date value to set.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setDate(unsigned char date){
    return I2CDevice::writeRegister(DS3231_DTE_ADDR, date);
}

/**
 * @brief Set the month in the Real-Time Clock (RTC).
 * @param month The month value to set.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setMonth(unsigned char month){
    return I2CDevice::writeRegister(DS3231_MON_ADDR, month);
}

/**
 * @brief Set the year in the Real-Time Clock (RTC).
 * @param year The year value to set.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setYear(unsigned char year){
    return I2CDevice::writeRegister(DS3231_YRS_ADDR, year);
}

/**
 * @brief Set the date and time in the Real-Time Clock (RTC).
 *
 * This function sets the date and time in the RTC by converting the provided
 * values to Binary-Coded Decimal (BCD) format and then calling the respective
 * set functions for seconds, minutes, hours, day, date, month, and year.
 *
 * @param secs The seconds value to set.
 * @param mins The minutes value to set.
 * @param hrs The hours value to set.
 * @param day The day value to set.
 * @param date The date value to set.
 * @param month The month value to set.
 * @param year The year value to set.
 */

void RealTimeClock::setDateTime(int secs, int mins, int hrs, int day, int date, int month, int year) {
    this->setSeconds(this->decimalToBcd(secs));
    this->setMinutes(this->decimalToBcd(mins));
    this->setHours(this->decimalToBcd(hrs));
    this->setDay(this->decimalToBcd(day));
    this->setDate(this->decimalToBcd(date));
    this->setMonth(this->decimalToBcd(month));
    this->setYear(this->decimalToBcd(year));
}

/**
 * @brief Set the seconds for Alarm 1 in the RTC.
 * @param seconds The seconds value to set for Alarm 1.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setAlarm1Seconds(unsigned char seconds){
    return I2CDevice::writeRegister(DS3231_ALRM1_SEC_ADDR, seconds);
}

/**
 * @brief Set the minutes for Alarm 1 in the RTC.
 * @param minutes The minutes value to set for Alarm 1.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setAlarm1Minutes(unsigned char minutes){
    return I2CDevice::writeRegister(DS3231_ALRM1_MIN_ADDR, minutes);
}

/**
 * @brief Set the hours for Alarm 1 in the RTC.
 * @param hours The hours value to set for Alarm 1.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setAlarm1Hours(unsigned char hours){
    return I2CDevice::writeRegister(DS3231_ALRM1_HRS_ADDR, hours);
}

/**
 * @brief Set the day or date for Alarm 1 in the RTC.
 * @param day The day or date value to set for Alarm 1.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setAlarm1DyDt(unsigned char day){
    return I2CDevice::writeRegister(DS3231_ALRM1_DYDT_ADDR, day);
}

/**
 * @brief Set the minutes for Alarm 2 in the RTC.
 * @param minutes The minutes value to set for Alarm 2.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setAlarm2Minutes(unsigned char minutes){
    return I2CDevice::writeRegister(DS3231_ALRM2_MIN_ADDR, minutes);
}

/**
 * @brief Set the hours for Alarm 2 in the RTC.
 * @param hours The hours value to set for Alarm 2.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setAlarm2Hours(unsigned char hours){
    return I2CDevice::writeRegister(DS3231_ALRM2_HRS_ADDR, hours);
}

/**
 * @brief Set the day or date for Alarm 2 in the RTC.
 * @param day The day or date value to set for Alarm 2.
 * @return 0 if successful, 1 if there was an error.
 */
int RealTimeClock::setAlarm2DyDt(unsigned char day){
    return I2CDevice::writeRegister(DS3231_ALRM2_DYDT_ADDR, day);
}

/**
 * @brief Set an alarm in the Real-Time Clock (RTC) based on user input.
 *
 * This function allows the user to set an alarm in the RTC by providing the alarm type ('dy' or 'dt'),
 * the alarm number ('1' or '2'), and the time components (seconds, minutes, hours, and day/date).
 * It clears any existing alarm of the specified type, sets the new alarm parameters, and enables
 * the interrupt on the INT/SQW output pin for the specified alarm.
 *
 * @param dydt A string indicating 'dy' for alarm by day or 'dt' for alarm by date.
 * @param alarmNumber A character indicating Alarm 1 or Alarm 2.
 * @param secs The seconds value for the alarm.
 * @param mins The minutes value for the alarm.
 * @param hrs The hours value for the alarm.
 * @param intDydt The day or date value for the alarm.
 */
void RealTimeClock::setAlarm(char* dydt, char* alarmNumber, int secs, int mins, int hrs, int dayNumber) {

    unsigned char dydtValue;

    if (strcmp(dydt, "dy") == 0) {
        dydtValue = decimalToBcd(dayNumber) | 0x40;
    } else if (strcmp(dydt, "dt") == 0) {
        dydtValue = decimalToBcd(dayNumber);
    }

    if (*alarmNumber == '1') {
        // clear existing alarm
        this->clearAlarm(1);
        this->setAlarm1Seconds(this->decimalToBcd(secs));
        this->setAlarm1Minutes(this->decimalToBcd(mins));
        this->setAlarm1Hours(this->decimalToBcd(hrs));
        this->setAlarm1DyDt(dydtValue);
    } else if (*alarmNumber == '2') {
        // clear existing alarm
        this->clearAlarm(2);
        this->setAlarm2Minutes(this->decimalToBcd(mins));
        this->setAlarm2Hours(this->decimalToBcd(hrs));
        this->setAlarm2DyDt(dydtValue);
        secs = 0; // seconds always 0 for alarm 2
    } else {
        cout << "Please select either alarm 1 or 2";
    }
}

/**
 * @brief Clear a specific alarm in the RTC.
 * @param flag The alarm number to clear (1 or 2).
 */
void RealTimeClock::clearAlarm(int flag) {
    
    unsigned char status;
    status = I2CDevice::readRegister(DS3231_STATUS);
    setBitToZero(status, flag - 1);
    I2CDevice::writeRegister(DS3231_STATUS, status);
}

/**
 * @brief Enable the interrupt for a specific alarm in the RTC.
 * @param alarmNumber A character indicating Alarm 1 or Alarm 2.
 */
void RealTimeClock::enableInterrupt(char* alarmNumber) {

    unsigned char control;
    int alarmEnbaleFlag, intcn;

    if (*alarmNumber == '1') alarmEnbaleFlag = 0;
    if (*alarmNumber == '2') alarmEnbaleFlag = 1;
    intcn = 2;

    control = I2CDevice::readRegister(DS3231_CONTROL);
    this->setBitToOne(control, alarmEnbaleFlag);
    this->setBitToOne(control, intcn);
    I2CDevice::writeRegister(DS3231_CONTROL, control);
}

/**
 * @brief Output a square wave on the INT/SQW pin based on user input.
 * @param level A character indicating the level of the square wave (1 to 4).
 */
void RealTimeClock::outputSquareWave(char* level) {

    unsigned char control;
    int intcn = 2;

    if (this->setSquareWaveFrequency(*level)) {
        control = I2CDevice::readRegister(DS3231_CONTROL);
        this->setBitToZero(control, intcn);
        I2CDevice::writeRegister(DS3231_CONTROL, control);
    }
}

/**
 * @brief Set the square wave frequency based on user input.
 * @param level A character indicating the level of the square wave (1 to 4).
 * @return 1 if successful, 0 if there was an error.
 */
int RealTimeClock::setSquareWaveFrequency(const char& level) {

    unsigned char control;
    int rs1 =3, rs2 = 4;
    control = I2CDevice::readRegister(DS3231_CONTROL);
    
    switch (level) {
        case '1':
            this->setBitToZero(control, rs1);
            this->setBitToZero(control, rs2);
            break;
        case '2':
            this->setBitToOne(control, rs1);
            this->setBitToZero(control, rs2);
            break;
        case '3':
            this->setBitToZero(control, rs1);
            this->setBitToOne(control, rs2);
            break;
        case '4':
            this->setBitToOne(control, rs1);
            this->setBitToOne(control, rs2);
            break;
        default:
            cout << "Please choose a level 1-4 for square wave output" << endl;
            return 0;
    }
    I2CDevice::writeRegister(DS3231_CONTROL, control);
    return 1;
}

/**
 * @brief Stop the square wave output on the INT/SQW pin.
 */
void RealTimeClock::stopSquareWave() {

    unsigned char control;
    int intcn = 2;
    control = I2CDevice::readRegister(DS3231_CONTROL);
    this->setBitToOne(control, intcn);
    I2CDevice::writeRegister(DS3231_CONTROL, control);
}