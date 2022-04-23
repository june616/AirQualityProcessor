#include <iostream>
#include "Time.h"

using namespace std;

// default constructor
Time::Time()
{
    sec = 1;
    min = 1;
    hour = 1;
}

// specific constructor
Time::Time(int s, int m, int h)
{
    sec = s;
    min = m;
    hour = h;
}

// destructor
Time::~Time() {

}

// setters
void Time::setSec(int s)
{
    sec = s;
}

void Time::setMin(int m)
{
    min = m;
}

void Time::setHour(int h)
{
    hour = h;
}

void Time::setSmh(int s, int m, int h)
{
    sec = s;
    min = m;
    hour = h;
}

// getters
int Time::getSec() const
{
    return sec;
}

int Time::getMin() const
{
    return min;
}

int Time::getHour() const
{
    return hour;
}

// printf
void Time::print() const
{
    cout << sec << "/"
         << min << "/"
         << hour;
}

// ostream operator
ostream& operator << (ostream& osObject, const Time& time1) //creating an instance of a date class, i.e. date1
{
    if (time1.min == 0 && time1.sec == 0){
        osObject << time1.hour
                 << ":" << "00"
                 << ":" << "00";
    }
    else {
        osObject << time1.hour
                 << ":" << time1.min
                 << ":" << time1.sec;
    }
    return osObject;
}

// istream operator
istream& operator >> (istream& isObject, Time& time1)
{
    isObject >> time1.hour >> time1.min >> time1.sec;
    return isObject;
}

// Overloading "equal to" operator
bool Time::operator==(const Time& otherTime) const
{
    if (sec == otherTime.sec && min == otherTime.min
        && hour == otherTime.hour)
        return true;
    else
        return false;
}

// Overloading "not equal to" operator
bool Time::operator!=(const Time& otherTime) const
{
    return !(*this == otherTime);
}

// Overloading "less than or equal to" operator 
bool Time::operator<=(const Time& otherTime) const
{
    return (*this < otherTime || *this == otherTime);
}

// Overloading "less than" operator
bool Time::operator<(const Time& otherTime) const
{
    if ((hour < otherTime.hour) ||
        (hour == otherTime.hour && min < otherTime.min) ||
        (hour == otherTime.hour && min == otherTime.min && sec < otherTime.sec))
        return true;
    else
        return false;
}

// Overloading "greater than or equal to" operator
bool Time::operator>=(const Time& otherTime) const
{
    return !(*this < otherTime);
}

// Overloading "greater than" operator
bool Time::operator>(const Time& otherTime) const
{
    return !(*this <= otherTime);
}