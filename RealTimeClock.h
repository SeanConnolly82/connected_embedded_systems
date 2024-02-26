#include <cstring>
#include <string>
#include "I2CDevice.h"

using namespace std;

// datetime registers
#define DS3231_SEC_ADDR 0x00
#define DS3231_MIN_ADDR 0x01
#define DS3231_HRS_ADDR 0x02
#define DS3231_DAY_ADDR 0x03
#define DS3231_DTE_ADDR 0x04
#define DS3231_MON_ADDR 0x05
#define DS3231_YRS_ADDR 0x06

// alarm 1 registers
#define DS3231_ALRM1_SEC_ADDR 0x07
#define DS3231_ALRM1_MIN_ADDR 0x08
#define DS3231_ALRM1_HRS_ADDR 0x09
#define DS3231_ALRM1_DYDT_ADDR 0x0A

// alarm 2 registers
#define DS3231_ALRM2_MIN_ADDR 0x0B
#define DS3231_ALRM2_HRS_ADDR 0x0C
#define DS3231_ALRM2_DYDT_ADDR 0x0D

// control and status registers
#define DS3231_CONTROL 0x0E
#define DS3231_STATUS 0x0F

// temperature registers
#define DS3231_TEMP_MSB 0x11
#define DS3231_TEMP_LSB 0x12

/**
 * @class RealTimeClock
 * @brief Derived class of I2CDevice that provides an API to the functionality available in  DS3231 realtime clock
 */
class RealTimeClock:public EE513::I2CDevice {
private:
    virtual void setBitToOne(unsigned char &byte, int position);
    virtual void setBitToZero(unsigned char &byte, int position);
    virtual int binaryToDecimal(unsigned char binaryValue);
public:
    RealTimeClock(unsigned int bus, unsigned int device);
    virtual unsigned char readSeconds();
    virtual unsigned char readMinutes();
    virtual unsigned char readHours();
    virtual unsigned char readDay();
    virtual unsigned char readDate();
    virtual unsigned char readMonth();
    virtual unsigned char readYear();
    virtual unsigned char readTempMSB();
    virtual unsigned char readTempLSB();
    virtual int setSeconds(unsigned char second);
    virtual int setMinutes(unsigned char mintues);
    virtual int setHours(unsigned char hours);
    virtual int setDay(unsigned char day);
    virtual int setDate(unsigned char date);
    virtual int setMonth(unsigned char month);
    virtual int setYear(unsigned char year);
    virtual void setDateTime(int secs, int mins, int hrs, int day, int date, int month, int year);
    virtual int setAlarm1Seconds(unsigned char second);
    virtual int setAlarm1Minutes(unsigned char mintues);
    virtual int setAlarm1Hours(unsigned char hours);
    virtual int setAlarm1DyDt(unsigned char day);
    virtual int setAlarm2Minutes(unsigned char mintues);
    virtual int setAlarm2Hours(unsigned char hours);
    virtual int setAlarm2DyDt(unsigned char date);
    virtual void setAlarm(char* dydt, char* alarmNumber, int secs, int mins, int hrs, int intDydt);
    virtual void clearAlarm(int flag);
    virtual void enableInterrupt(char* alarmNumber);
    virtual void outputSquareWave(char* level);
    virtual int setSquareWaveFrequency(const char& level);
    virtual void stopSquareWave();
    virtual unsigned char bcdToDecimal(unsigned char bcdValue);
    virtual unsigned char decimalToBcd(unsigned char decimalValue);
    virtual double binaryFractionToDecimal(unsigned char binaryInt, unsigned char binaryFraction);
};