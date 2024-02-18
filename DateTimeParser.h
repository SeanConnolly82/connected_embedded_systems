#include <cstring>
#include <sstream>

using namespace std;

class DateTimeParser {
public:
    DateTimeParser();
    void parseDateTime(const string& datetimeString);
    void parseAlarmTime(const string& alarmTimeString);
    virtual string getDay();
    virtual int DayStoI(string dayName);
    virtual string DayItoS(int dayNumber);
    //virtual string getDyDt();
    virtual int getDate();
    virtual int getMonth();
    virtual int getYear();
    virtual int getHour();
    virtual int getMinutes();
    virtual int getSeconds();

private:
    const char* daysArr[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    string day;
    int date;
    int month;
    int year;
    int hour;
    int minutes;
    int seconds;
};
