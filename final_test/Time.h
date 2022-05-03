//
// Created by hycwy on 4/9/2022.
//

#ifndef FINAL_PROJECT_TIME_H
#define FINAL_PROJECT_TIME_H
#include "ostream"

using namespace std;

class Time {

    friend ostream& operator << (ostream&, const Time&); // method overloading
    friend istream& operator >> (istream&, Time&);

public:

    // default constructor
    Time();

    // specific constructor
    Time(int s, int m, int h);

    // setters
    void setSec(int s);
    void setMin(int m);
    void setHour(int h);
    void setSmh(int s, int m, int h);

    // getters
    int getSec() const;
    int getMin() const;
    int getHour() const;

    // printf
    void print() const;

    // Overloading operators
    bool operator<(const Time& otherTime) const;
    bool operator>(const Time& otherTime) const;
    bool operator==(const Time& otherTime) const;
    bool operator<=(const Time& otherTime) const;
    bool operator>=(const Time& otherTime) const;
    bool operator!=(const Time& otherTime) const;

    // Overloading math operations
    Time operator++();
    Time operator++(int);
    Time operator--();
    Time operator--(int);

private:

    // data members
    int sec;
    int min;
    int hour;
};


#endif //FINAL_PROJECT_TIME_H
