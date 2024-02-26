#include "RealTimeClock.h"

class Application:public RealTimeClock {
public:
    Application(unsigned int bus, unsigned int device);
    virtual void setDateTime(char* dateTimeString);
    virtual void displayTemperature();
    virtual void displayDateTime();
    virtual void setAlarm(char* dydt, char* alarmTimeString, char* alarmNumber);
};