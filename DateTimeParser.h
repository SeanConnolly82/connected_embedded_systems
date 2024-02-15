#include <cstring>
#include <sstream>

using namespace std;

class DateTimeParser {
public:
    DateTimeParser(const string& datetimeString);
    virtual string getDay();
    virtual int getDate();
    virtual int getMonth();
    virtual int getYear();
    virtual int getHour();
    virtual int getMinutes();
    virtual int getSeconds();

private:
    string day;
    int date;
    int month;
    int year;
    int hour;
    int minutes;
    int seconds;
};
