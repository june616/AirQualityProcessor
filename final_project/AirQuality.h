//
// Created by hycwy on 4/10/2022.
//
#include "Date.h"
#include "Time.h"


#ifndef FINAL_PROJECT_AIRQUALITY_H
#define FINAL_PROJECT_AIRQUALITY_H

class AirQuality {
    friend ostream& operator << (ostream&, const AirQuality&);
    friend istream& operator >> (istream&, AirQuality&);

public:
    AirQuality();

    AirQuality(Date dateInput, Time timeInput, double t, double r, double a);

    AirQuality(double t, double r, double a);

    ~AirQuality();

    void setDate(Date d);
    void setTime(Time t);
    void setTemp(double t);
    void setRelativeHumidity(double r);
    void setAbsHumidity(double a);

    Date getDate();
    Time getTime();
    double getTemp();
    double getRelativeHumidity();
    double getAbsHumidity();

private:

    // data members
    Date date = Date();
    Time time = Time();
    double temp;
    double relativeHumidity;
    double absHumidity;
};


#endif //FINAL_PROJECT_AIRQUALITY_H
