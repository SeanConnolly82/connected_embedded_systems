#include <cstring>
#include <sstream>

using namespace std;

/**
 * @class DateTimeParser
 * @brief Generic datetime parser to break a datetime string into its constituent time components
 */

class DateTimeParser {
public:
    DateTimeParser();
    void parseDateTime(const string& datetimeString);
    void parseAlarmTime(const string& alarmTimeString);
    virtual string getDayName();
    virtual string dayItoS(int dayNumber);
    virtual int dayStoI(string dayName);
    virtual int getDayNumber();
    virtual int getDate();
    virtual int getMonth();
    virtual int getYear();
    virtual int getHour();
    virtual int getMinutes();
    virtual int getSeconds();

private:
    const char* daysArr[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    string dayName;
    int dayNumber;
    int date;
    int month;
    int year;
    int hour;
    int minutes;
    int seconds;
};
