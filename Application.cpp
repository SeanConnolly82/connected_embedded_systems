#include<iostream>
#include<iomanip>
#include "I2CDevice.h"
using namespace std;
 
#define DS3231_SEC_ADDR 0x00
#define DS3231_MIN_ADDR 0x01

unsigned char bcdToDecimal(unsigned char bcdValue) {
    return ((bcdValue & 0xF0) >> 4) * 10 + (bcdValue & 0x0F);
}

unsigned char decimalToBcd(unsigned char decimalValue) {
    return ((decimalValue / 10) << 4) | (decimalValue % 10);
}

class RealTimeClock:public EE513::I2CDevice {
private:
    int seconds;
    int minutes;
    int hours;
public:
    RealTimeClock(unsigned int bus, unsigned int device):I2CDevice(bus,device){
        cout << "RTC created\n";
    }
    unsigned char readSeconds(){
        return I2CDevice::readRegister(DS3231_SEC_ADDR);
    }
    unsigned char readMinutes(){
        return I2CDevice::readRegister(DS3231_MIN_ADDR);
    }
};

int main() {
    RealTimeClock rtc(1,0x68);
    rtc.debugDumpRegisters(0x07);
    unsigned char seconds = bcdToDecimal(rtc.readSeconds());
    cout << endl << "Decimal equivalent: " << static_cast<int>(seconds) << endl;
    
    // Test of decimal to BCD
    unsigned char bcdTest = decimalToBcd(6);
    cout << endl << "*** Testing decimal to BCD ***" << endl;
    cout << "Decimal (no conversion): " << hex << static_cast<int>(42) << endl;
    cout << "BCD: 0x" << hex << static_cast<int>(bcdTest) << endl;

    cout << endl << "*** Testing write register ***" << endl;
    rtc.writeRegister(0x04, bcdTest);
    rtc.debugDumpRegisters(0x07);

    return 0;
}
