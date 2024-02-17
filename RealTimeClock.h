#include "I2CDevice.h"

using namespace std;

#define DS3231_SEC_ADDR 0x00
#define DS3231_MIN_ADDR 0x01
#define DS3231_HRS_ADDR 0x02
#define DS3231_DAY_ADDR 0x03
#define DS3231_DTE_ADDR 0x04
#define DS3231_MON_ADDR 0x05
#define DS3231_YRS_ADDR 0x06

#define DS3231_ALRM_SEC_ADDR 0x07
#define DS3231_ALRM_MIN_ADDR 0x08
#define DS3231_ALRM_HRS_ADDR 0x09
#define DS3231_ALRM_DYDT_ADDR 0x0A


class RealTimeClock:public EE513::I2CDevice {
private:
    unsigned char seconds;
    unsigned char minutes;
    unsigned char hours;
    unsigned char day;
    unsigned char date;
    unsigned char month;
    unsigned char year;
    const char* weekday[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; 
public:
    RealTimeClock(unsigned int bus, unsigned int device);
    virtual unsigned char bcdToDecimal(unsigned char bcdValue);
    virtual unsigned char decimalToBcd(unsigned char decimalValue);
    virtual unsigned char readSeconds();
    virtual unsigned char readMinutes();
    virtual unsigned char readHours();
    virtual unsigned char readDay();
    virtual unsigned char readDate();
    virtual unsigned char readMonth();
    virtual unsigned char readYear();
    virtual void readDateTime();
    virtual void displayDateTime();
    virtual int setSeconds(unsigned char second);
    virtual int setMinutes(unsigned char mintues);
    virtual int setHours(unsigned char hours);
    virtual int setDay(unsigned char day);
    virtual int setDate(unsigned char date);
    virtual int setMonth(unsigned char month);
    virtual int setYear(unsigned char year);
    virtual void setDateTime(char *datetimeString);
    virtual int setAlarmSeconds(unsigned char second);
    virtual int setAlarmMinutes(unsigned char mintues);
    virtual int setAlarmHours(unsigned char hours);
    virtual int setAlarmDay(unsigned char day);
    //virtual int setAlarmDate(unsigned char date);
    virtual void setAlarmTime(char *datetimeString, int alarmNumber);
};