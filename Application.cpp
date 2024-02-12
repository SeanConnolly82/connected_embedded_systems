#include<iostream>
#include<iomanip>
#include "I2CDevice.h"
using namespace std;
 
#define DS3231_SEC_ADDR 0x00
#define DS3231_MIN_ADDR 0x01

#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)
                 
class RealTimeClock:public EE513::I2CDevice {
private:
    int seconds;
    int minutes;
    int hours;
public:
    RealTimeClock(unsigned int bus, unsigned int device):I2CDevice(bus,device){
        cout << "RTC created\n";
    }
    unsigned char readMinutes(){
        return I2CDevice::readRegister(DS3231_MIN_ADDR);
    }
};

int main() {
    RealTimeClock rtc(1,0x68);
    unsigned char mins = rtc.readMinutes();
    cout << HEX(mins) << endl;
    return 0;
}