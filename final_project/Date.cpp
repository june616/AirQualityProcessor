#include <iostream>
#include "Date.h"

using namespace std;

// default constructor
Date::Date()
{
    day = 1;
    month = 1;
    year = 2000;
}

// specific constructor
Date::Date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}


// destructor
Date::~Date() {

}

// setters
void Date::setDay(int d)
{
    day = d;
}

void Date::setMonth(int m)
{
    month = m;
}

void Date::setYear(int y)
{
    year = y;
}

void Date::setDmy(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

// getters
int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

// printf
void Date::print() const
{
    cout << day << "/"
         << month << "/"
         << year;
}

// ostream operator
ostream& operator << (ostream& osObject, const Date& date1) //creating an instance of a date class, i.e. date1
{
    osObject << date1.day
             << "/" << date1.month
             << "/" << date1.year;
    return osObject;
}

// istream operator
istream& operator >> (istream& isObject, Date& date1)
{
    isObject >> date1.day >> date1.month >> date1.year;
    return isObject;
}

// Overloading "equal to" operator
bool Date::operator==(const Date& otherDate) const
{
    if (day == otherDate.day && month == otherDate.month
        && year == otherDate.year)
        return true;
    else
        return false;
}

// Overloading "not equal to" operator
bool Date::operator!=(const Date& otherDate) const
{
    return !(*this == otherDate);
}

// Overloading "less than or equal to" operator 
bool Date::operator<=(const Date& otherDate) const
{
    return (*this < otherDate || *this == otherDate);
}

// Overloading "less than" operator
bool Date::operator<(const Date& otherDate) const
{
    if ((year < otherDate.year) ||
        (year == otherDate.year && month < otherDate.month) ||
        (year == otherDate.year && month == otherDate.month && day < otherDate.day))
        return true;
    else
        return false;
}

// Overloading "greater than or equal to" operator
bool Date::operator>=(const Date& otherDate) const
{
    return !(*this < otherDate);
}

// Overloading "greater than" operator
bool Date::operator>(const Date& otherDate) const
{
    return !(*this <= otherDate);
}