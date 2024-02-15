#include "RealTimeClock.h"

#include<iostream>
#include<iomanip>

using namespace std;

int main() {
    RealTimeClock rtc(1,0x68);
    // rtc.debugDumpRegisters(0x07);
    // unsigned char seconds = RealTimeClock::bcdToDecimal(rtc.readSeconds());
    // cout << endl << "Decimal equivalent: " << static_cast<int>(seconds) << endl;
    
    // // Test of decimal to BCD
    // unsigned char bcdTest = RealTimeClock::decimalToBcd(42);
    // cout << endl << "*** Testing decimal to BCD ***" << endl;
    // cout << "Decimal (no conversion): " << hex << static_cast<int>(42) << endl;
    // cout << "BCD: 0x" << setw(2) << setfill('0') << hex << static_cast<int>(bcdTest) << endl;

    // cout << endl << "*** Testing write register ***" << endl;
    // rtc.writeRegister(0x04, bcdTest);
    // rtc.debugDumpRegisters(0x07);
    rtc.displayDateTime();
    cout << endl;

    return 0;
}
