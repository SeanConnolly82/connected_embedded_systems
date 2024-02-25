#include "RealTimeClock.h"

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {

    int alarm;

    RealTimeClock rtc(1,0x68);

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
