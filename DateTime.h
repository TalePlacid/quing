#ifndef DATETIME_H 
#define DATETIME_H
#include <ctime>
#include <string>
#include <cstdint>
using namespace std;

typedef int64_t Int;

enum WeekDay : Int {
    SUN,
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT
};

class DateTime{
public:
    DateTime();
    DateTime(Int year, Int month, Int day, Int hour = 0, Int minute = 0, Int second = 0);
    DateTime(string dateTime);
    ~DateTime();
    DateTime(const DateTime& source);
    DateTime& operator=(const DateTime& source);

    static DateTime Now();

    string ToString() const;
    string ToCode() const;
    bool IsEqual(const DateTime& other) const;
    bool IsNotEqual(const DateTime& other) const;
    bool IsLesserThan(const DateTime& other) const;
    bool IsGreaterThan(const DateTime& other) const;

    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;

    Int GetYear() const;
    Int GetMonth() const;
    Int GetDay() const;
    Int GetHour() const;
    Int GetMinute() const;
    Int GetSecond() const;
    WeekDay GetWeekDay() const;
private:
    Int year;
    Int month;
    Int day;
    Int hour;
    Int minute;
    Int second;
    WeekDay weekDay;
};

inline Int DateTime::GetYear() const{
    return this->year;
}

inline Int DateTime::GetMonth() const{
    return this->month;
}

inline Int DateTime::GetDay() const{
    return this->day;
}

inline Int DateTime::GetHour() const{
    return this->hour;
}

inline Int DateTime::GetMinute() const{
    return this->minute;
}


inline Int DateTime::GetSecond() const{
    return this->second;
}

inline WeekDay DateTime::GetWeekDay() const{
    return this->weekDay;
}

#endif // DATETIME_H
