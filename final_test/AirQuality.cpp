//
// Created by hycwy on 4/10/2022.
//

#include "AirQuality.h"

AirQuality::AirQuality() {
    temp = 0.0;
    relativeHumidity = 0.0;
    absHumidity = 0.0;
}

AirQuality::AirQuality(double t, double r, double a) {
    temp = t;
    relativeHumidity = r;
    absHumidity = a;
}

AirQuality::AirQuality(Date dateInput, Time timeInput, double t, double r, double a) {
    date.setDmy(dateInput.getDay(),dateInput.getMonth(),dateInput.getYear());
    time.setSmh(timeInput.getSec(), timeInput.getMin(), timeInput.getHour());
    temp = t;
    relativeHumidity = r;
    absHumidity = a;
}

void AirQuality::setDate(Date d) {
    date.setDmy(d.getDay(), d.getMonth(), d.getYear());
}

void AirQuality::setTime(Time t) {
    time.setSmh(t.getSec(), t.getMin(), t.getHour());
}

void AirQuality::setTemp(double t) {
    temp = t;
}

void AirQuality::setRelativeHumidity(double r) {
    relativeHumidity = r;
}

void AirQuality::setAbsHumidity(double a) {
    absHumidity = a;
}

Date AirQuality::getDate() {
    return date;
}

Time AirQuality::getTime() {
    return time;
}

double AirQuality::getAbsHumidity() {
    return absHumidity;
}

double AirQuality::getRelativeHumidity() {
    return relativeHumidity;
}

double AirQuality::getTemp() {
    return temp;
}