#include "DateTime.h"
#include <sstream>
#include <iomanip>
using namespace std;

#pragma warning(disable:4996)

DateTime::DateTime(){
    this->year = 1900;
    this->month = 1;
    this->day = 1;
    this->weekDay = MON;
    this->hour = 0;
    this->minute = 0;
    this->second = 0;
}

DateTime::DateTime(Int year, Int month, Int day, Int hour, Int minute, Int second){
    struct tm dateTime = {0,};
    dateTime.tm_year = static_cast<int>(year - 1900);
    dateTime.tm_mon = static_cast<int>(month - 1);
    dateTime.tm_mday = static_cast<int>(day);
    dateTime.tm_hour = static_cast<int>(hour);
    dateTime.tm_min = static_cast<int>(minute);
    dateTime.tm_sec = static_cast<int>(second);
    dateTime.tm_isdst = -1;

    mktime(&dateTime);

    this->year = dateTime.tm_year + 1900;
    this->month = dateTime.tm_mon + 1;
    this->day = dateTime.tm_mday;
    this->hour = dateTime.tm_hour;
    this->minute = dateTime.tm_min;
    this->second = dateTime.tm_sec;
    this->weekDay = static_cast<WeekDay>(dateTime.tm_wday);
}

DateTime::DateTime(string dateTime){
    struct tm dateTime_ = {0,};

    dateTime_.tm_year = stoi(dateTime.substr(0, 4)) - 1900;
    dateTime_.tm_mon = stoi(dateTime.substr(5, 2)) - 1;
    dateTime_.tm_mday = stoi(dateTime.substr(8, 2));
    dateTime_.tm_hour = stoi(dateTime.substr(11, 2));
    dateTime_.tm_min = stoi(dateTime.substr(14, 2));
    dateTime_.tm_sec = stoi(dateTime.substr(17, 2));
    dateTime_.tm_isdst = -1;

    mktime(&dateTime_);

    this->year = dateTime_.tm_year + 1900;
    this->month = dateTime_.tm_mon + 1;
    this->day = dateTime_.tm_mday;
    this->hour = dateTime_.tm_hour;
    this->minute = dateTime_.tm_min;
    this->second = dateTime_.tm_sec;
    this->weekDay = static_cast<WeekDay>(dateTime_.tm_wday);
}

DateTime::~DateTime(){

}

DateTime::DateTime(const DateTime& source){
    this->year = source.year;
    this->month = source.month;
    this->day = source.day;
    this->hour = source.hour;
    this->minute = source.minute;
    this->second = source.second;
    this->weekDay = source.weekDay;
}

DateTime& DateTime::operator=(const DateTime& source){
    this->year = source.year;
    this->month = source.month;
    this->day = source.day;
    this->hour = source.hour;
    this->minute = source.minute;
    this->second = source.second;
    this->weekDay = source.weekDay;

    return *this;
}

DateTime DateTime::Now(){
    time_t now = time(0);
    struct tm now_;
#if defined(_WIN32)
    localtime_s(&now_, &now);
#else
    localtime_r(&now, &now_);
#endif

    DateTime dateTime(static_cast<Int>(now_.tm_year + 1900),
                      static_cast<Int>(now_.tm_mon + 1),
                      static_cast<Int>(now_.tm_mday),
                      static_cast<Int>(now_.tm_hour),
                      static_cast<Int>(now_.tm_min),
                      static_cast<Int>(now_.tm_sec)
                      );

    return dateTime;
}

bool DateTime::IsEqual(const DateTime& other) const{
    bool ret = false;

    if (this->year == other.year
        && this->month == other.month
        && this->day == other.day
        && this->hour == other.hour
        && this->minute == other.minute
        && this->second == other.second){
        ret = true;
    }

    return ret;
}

bool DateTime::IsNotEqual(const DateTime& other) const{
    bool ret = false;

    if (this->year != other.year
        || this->month != other.month
        || this->day != other.day
        || this->hour != other.hour
        || this->minute != other.minute
        || this->second != other.second){
        ret = true;
    }

    return ret;
}

bool DateTime::IsLesserThan(const DateTime& other) const{
    bool ret = false;

    if(this->year < other.year){
        ret = true;
    } else if(this->year == other.year
               && this->month < other.month){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day < other.day){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour < other.hour){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute < other.minute){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute == other.minute
               && this->second < other.second){
        ret = true;
    }

    return ret;
}


bool DateTime::operator==(const DateTime& other) const{
    bool ret = false;

    if (this->year == other.year
        && this->month == other.month
        && this->day == other.day
        && this->hour == other.hour
        && this->minute == other.minute
        && this->second == other.second){
        ret = true;
    }

    return ret;
}

bool DateTime::operator!=(const DateTime& other) const{
    bool ret = false;

    if (this->year != other.year
        || this->month != other.month
        || this->day != other.day
        || this->hour != other.hour
        || this->minute != other.minute
        || this->second != other.second){
        ret = true;
    }

    return ret;
}

bool DateTime::operator<(const DateTime& other) const{
    bool ret = false;

    if(this->year < other.year){
        ret = true;
    } else if(this->year == other.year
               && this->month < other.month){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day < other.day){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour < other.hour){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute < other.minute){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute == other.minute
               && this->second < other.second){
        ret = true;
    }

    return ret;
}

bool DateTime::operator<=(const DateTime& other) const{
    bool ret = false;

    if(this->year < other.year){
        ret = true;
    } else if(this->year == other.year
               && this->month < other.month){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day < other.day){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour < other.hour){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute < other.minute){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute == other.minute
               && this->second <= other.second){
        ret = true;
    }

    return ret;
}

bool DateTime::IsGreaterThan(const DateTime& other) const{
    bool ret = false;

    if(this->year > other.year){
        ret = true;
    } else if(this->year == other.year
               && this->month > other.month){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day > other.day){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour > other.hour){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute > other.minute){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute == other.minute
               && this->second > other.second){
        ret = true;
    }

    return ret;
}

bool DateTime::operator>(const DateTime& other) const{
    bool ret = false;

    if(this->year > other.year){
        ret = true;
    } else if(this->year == other.year
               && this->month > other.month){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day > other.day){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour > other.hour){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute > other.minute){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute == other.minute
               && this->second > other.second){
        ret = true;
    }

    return ret;
}

bool DateTime::operator>=(const DateTime& other) const{
    bool ret = false;

    if(this->year > other.year){
        ret = true;
    } else if(this->year == other.year
               && this->month > other.month){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day > other.day){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour > other.hour){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute > other.minute){
        ret = true;
    } else if(this->year == other.year
               && this->month == other.month
               && this->day == other.day
               && this->hour == other.hour
               && this->minute == other.minute
               && this->second >= other.second){
        ret = true;
    }

    return ret;
}

string DateTime::ToString() const{
    stringstream ss;
    ss << setfill('0')
       << setw(4) << this->year
       << "-"
       << setw(2) << this->month
       << "-"
       << setw(2) << this->day
       << " "
       << setw(2) << this->hour
       << ":"
       << setw(2) << this->minute
       << ":"
       << setw(2) << this->second;

    return ss.str();
}

string DateTime::ToCode() const{
    stringstream ss;
    ss << setfill('0')
       << setw(4) << this->year
       << setw(2) << this->month
       << setw(2) << this->day
       << setw(2) << this->hour
       << setw(2) << this->minute
       << setw(2) << this->second;

    return ss.str();
}
