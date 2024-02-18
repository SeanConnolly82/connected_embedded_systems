#include "RealTimeClock.h"

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {

    int alarm;

    RealTimeClock rtc(1,0x68);
    if (argc > 2 && strcmp(argv[1], "set-time") == 0) {
        rtc.setDateTime(argv[2]);
    } else if (argc > 2 && strcmp(argv[1], "set-alarm") == 0) {
        rtc.setAlarm(argv[2], argv[3], argv[4]);
    }
    rtc.displayDateTime();

    return 0;
}
