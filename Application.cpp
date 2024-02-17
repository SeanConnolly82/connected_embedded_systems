#include "RealTimeClock.h"

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {

    int alarm, mode;

    // TODO: Add command line argument for alarm number and mode
    //       Include day or date in the alarm time string

    RealTimeClock rtc(1,0x68);
    if (argc > 2 && strcmp(argv[1], "set-time") == 0) {
        rtc.setDateTime(argv[2]);
    } else if (argc > 2 && strcmp(argv[1], "set-alarm") == 0) {
        rtc.setAlarmTime(argv[2],1);
    }
    rtc.displayDateTime();

    return 0;
}
