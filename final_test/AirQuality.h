//
// Created by hycwy on 4/10/2022.
//
#ifndef FINAL_PROJECT_AIR_QUALITY_H
#define FINAL_PROJECT_AIR_QUALITY_H

#include "Date.h"
#include "Date.cpp"
#include "Time.h"
#include "Time.cpp"


class AirQuality {
public:
    AirQuality();

    AirQuality(Date dateInput, Time timeInput, double t, double r, double a);

    AirQuality(double t, double r, double a);

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
#endif
