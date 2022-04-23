#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "vector"
#include "string"
#include "Date.h"
#include "Date.cpp"
#include "Time.h"
#include "Time.cpp"
#include "AirQuality.h"
#include "AirQuality.cpp"
using namespace std;

void getData(ifstream &inFile, vector<string>& fields, vector<AirQuality>& airQualityCollection);
Date processDate(string inputStr);
Time processTime(string inputStr);
double calculateAvgTemp(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection);
double calculateRelHumidity(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection);
double calculateAbsHumidity(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection);
void displayTempAndRelHumidity(Date dateInput, Time timeInput, double &currentTemp, double &currentRelHumidity, vector<AirQuality>& airQualityCollection);
double displayMaxTemp(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection);
double displayMaxRelHumidity(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection);
double displayMaxAbsHumidity(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection);
void findTempHigherThanAvg(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection, vector<AirQuality>& tempHigherThanAvg);
void findRelHumidHigherThanAvg(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection, vector<AirQuality>& relHumidHigherThanAvg);
void findAbsHumidHigherThanAvg(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection, vector<AirQuality>& absHumidHigherThanAvg);


int main()
{
    ifstream myFile("AirQualityUCI.csv");

    if (!myFile.is_open())
    {
        cout << "File not found." << endl;
        return 1;
    }

    vector<string> fields;
    vector<AirQuality> airQualityCollection;
    getData(myFile, fields, airQualityCollection);

    // just testing
//    for (int i = 0; i < airQualityCollection.size(); i++){
//        cout << airQualityCollection.at(i) << endl;
//    }

    // option 1-3
    // ps: if cannot find data corresponding to monthInput, return 0, instead of nan
    cout << "avg temp is: " << calculateAvgTemp(4, 3, airQualityCollection) << endl;
    cout << "avg relHumidity is: " << calculateRelHumidity(4, 3, airQualityCollection) << endl;
    cout << "abs relHumidity is: " << calculateAbsHumidity(4, 3, airQualityCollection) << endl;

    // option 4
//    Date d1(10, 3, 4);
//    Time t1(0, 0, 18);
//    double currentTemp, currentRelHumidity;
//    displayTempAndRelHumidity(d1, t1, currentTemp, currentRelHumidity, airQualityCollection);
//    cout << "At that date and time, temp is: " << currentTemp << ", rel humid is: " << currentRelHumidity << endl;

    // if cannot find it, both return 0
//    Date d2(10, 20, 4);
//    Time t2(0, 0, 18);
//    double currentTemp1, currentRelHumidity1;
//    displayTempAndRelHumidity(d2, t2, currentTemp1, currentRelHumidity1, airQualityCollection);
//    cout << "At that date and time, temp is: " << currentTemp1 << ", rel humid is: " << currentRelHumidity1 << endl;

    // option 5-7
    // if cannot find data corresponding to monthInput, return -100
    cout << "max temp is: " << displayMaxTemp(4, 3, airQualityCollection) << endl;
    cout << "max rel is: " << displayMaxRelHumidity(4, 3, airQualityCollection) << endl;
    cout << "max abs is: " << displayMaxAbsHumidity(4, 3, airQualityCollection) << endl;

    // option 8-10
    vector<AirQuality> tempHigherThanAvg;
    findTempHigherThanAvg(4, 3, airQualityCollection, tempHigherThanAvg);
    cout << "Higher than avg temp num: " << tempHigherThanAvg.size() << endl;

    vector<AirQuality>relHumidHigherThanAvg;
    findRelHumidHigherThanAvg(4, 3, airQualityCollection, relHumidHigherThanAvg);
    cout << "Higher than avg rel num: " << relHumidHigherThanAvg.size() << endl;

    vector<AirQuality>absHumidHigherThanAvg;
    findAbsHumidHigherThanAvg(4, 3, airQualityCollection, absHumidHigherThanAvg);
    cout << "Higher than avg abs: " << absHumidHigherThanAvg.size() << endl;

    return 0;

}

void getData(ifstream &inFile, vector<string>& fields, vector<AirQuality>& airQualityCollection)
{
    static const int DATE_IDX = 0;
    static const int TIME_IDX = 1;
    static const int TEMP_IDX = 12;
    static const int REL_HUMID_IDX = 13;
    static const int ABS_HUMID_IDX = 14;

    string strs;
    string delimiter = ",";
    size_t pos;
    // skip the first line
    getline(inFile, strs);
    // read each line, store as strs
    while (getline(inFile, strs))
    {
        size_t size = strs.size() - 1;
        // skip empty line (',,,,')
        if (strs[0] == ',')
        {
            break;
        }
        for (int i = 0; i < size; ++i)
        {
            pos = strs.find(delimiter, i);
            if (pos < size)
            {
                string token = strs.substr(i, pos - i);
                fields.push_back(token);
                i = pos + delimiter.size() - 1;
            }
        }

        // create date object with element in fields vector (index = 0)
        Date dateVal = processDate(fields.at(DATE_IDX));
        // create time object with element in fields vector (index = 1)
        Time timeVal = processTime(fields.at(TIME_IDX));
        // convert other parameters from string to double
        double temperature = stod(fields.at(TEMP_IDX));
        double relHumid = stod(fields.at(REL_HUMID_IDX));
        double absHumid = stod(fields.at(ABS_HUMID_IDX));
        // create AirQuality object, store in airQualityCollection vector
        AirQuality airQualityVal(dateVal, timeVal, temperature, relHumid, absHumid);
        airQualityCollection.push_back(airQualityVal);
        fields.clear();
    }

    inFile.close();
}

Date processDate(string inputStr)
{
    string delimiter = "/";
    size_t pos;
    string strs = inputStr + delimiter;
    size_t size = strs.size();
    vector<int> dateValues;
    // split the input string to 3 substrings, convert to int
    for (int i = 0; i < size; ++i)
    {
        pos = strs.find(delimiter, i);
        if (pos < size)
        {
            string token = strs.substr(i, pos - i);
            int tokenNum = stoi(token);
            dateValues.push_back(tokenNum);
            i = pos + delimiter.size() - 1;
        }
    }

    static const int DAY_IDX = 1;
    static const int MONTH_IDX = 0;
    static const int YEAR_IDX = 2;
    // create date object with elements in dateValues vector
    Date dateVal(dateValues.at(DAY_IDX), dateValues.at(MONTH_IDX), dateValues.at(YEAR_IDX));
    return dateVal;
}

Time processTime(string inputStr)
{
    string delimiter = ":";
    size_t pos;
    string strs = inputStr + delimiter;
    size_t size = strs.size();
    vector<int> timeValues;
    // split the input string to 3 substrings, convert to int
    for (int i = 0; i < size; ++i)
    {
        pos = strs.find(delimiter, i);
        if (pos < size)
        {
            string token = strs.substr(i, pos - i);
            int tokenNum = stoi(token);
            timeValues.push_back(tokenNum);
            i = pos + delimiter.size() - 1;
        }
    }

    static const int HOUR_IDX = 0;
    static const int MIN_IDX = 1;
    static const int SEC_IDX = 2;
    // create Time object with elements in timeVal vector
    Time timeVal(timeValues.at(SEC_IDX), timeValues.at(MIN_IDX), timeValues.at(HOUR_IDX));
    return timeVal;
}

double calculateAvgTemp(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection)
{
    static const double MISS_VALUE = -200;
    double totalTemp = 0;
    int count = 0;
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput){
            if (airQualityCollection[i].getTemp() != MISS_VALUE){
                totalTemp += airQualityCollection[i].getTemp();
                count++;
            }
        }
    }
    double avgTemp = totalTemp / count;

    if (count == 0){
        return 0;
    }
    else{
        return avgTemp;
    }
}

double calculateRelHumidity(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection)
{
    static const double MISS_VALUE = -200;
    double totalHumidity = 0;
    int count = 0;
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput){
            if (airQualityCollection[i].getRelativeHumidity() != MISS_VALUE){
                totalHumidity += airQualityCollection[i].getRelativeHumidity();
                count++;
            }
        }
    }
    double avgHumidity = totalHumidity / count;

    if (count == 0){
        return 0;
    }
    else{
        return avgHumidity;
    }
}


double calculateAbsHumidity(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection)
{
    static const double MISS_VALUE = -200;
    double totalHumidity = 0;
    int count = 0;
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput){
            if (airQualityCollection[i].getAbsHumidity() != MISS_VALUE){
                totalHumidity += airQualityCollection[i].getAbsHumidity();
                count++;
            }
        }
    }
    double avgHumidity = totalHumidity / count;

    if (count == 0){
        return 0;
    }
    else{
        return avgHumidity;
    }
}

void displayTempAndRelHumidity(Date dateInput, Time timeInput, double &currentTemp, double &currentRelHumidity, vector<AirQuality>& airQualityCollection)
{
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (dateInput == airQualityCollection[i].getDate() && timeInput == airQualityCollection[i].getTime()){
            currentTemp = airQualityCollection[i].getTemp();
            currentRelHumidity = airQualityCollection[i].getRelativeHumidity();
            return;
        }
    }
    currentTemp = 0;
    currentRelHumidity = 0;
}

double displayMaxTemp(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection)
{
    static const double THRESHOLD = -100;
    double maxTemp = THRESHOLD;
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput) {
            maxTemp = max(maxTemp, airQualityCollection[i].getTemp());
        }
    }
    return maxTemp;
}

double displayMaxRelHumidity(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection)
{
    static const double THRESHOLD = -100;
    double maxRelHumidity = THRESHOLD;
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput) {
            maxRelHumidity = max(maxRelHumidity, airQualityCollection[i].getRelativeHumidity());
        }
    }
    return maxRelHumidity;
}

double displayMaxAbsHumidity(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection)
{
    static const double THRESHOLD = -100;
    double maxAbsHumidity = THRESHOLD;
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput) {
            maxAbsHumidity = max(maxAbsHumidity, airQualityCollection[i].getAbsHumidity());
        }
    }
    return maxAbsHumidity;
}

void findTempHigherThanAvg(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection, vector<AirQuality>& tempHigherThanAvg)
{
    double avgTemp = calculateAvgTemp(yearInput, monthInput, airQualityCollection);
    // if avg = 0 -> cannot find data corresponding to monthInput
    if (avgTemp == 0)
    {
        return;
    }
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput){
            if (airQualityCollection[i].getTemp() > avgTemp){
                tempHigherThanAvg.push_back(airQualityCollection[i]);
            }
        }
    }
}

void findRelHumidHigherThanAvg(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection, vector<AirQuality>& relHumidHigherThanAvg)
{
    double avgRelHumid = calculateRelHumidity(yearInput, monthInput, airQualityCollection);
    // if avg = 0 -> cannot find data corresponding to monthInput
    if (avgRelHumid == 0)
    {
        return;
    }
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput){
            if (airQualityCollection[i].getRelativeHumidity() > avgRelHumid){
                relHumidHigherThanAvg.push_back(airQualityCollection[i]);
            }
        }
    }
}

void findAbsHumidHigherThanAvg(int yearInput, int monthInput, vector<AirQuality>& airQualityCollection, vector<AirQuality>& absHumidHigherThanAvg)
{
    double avgAbsHumid = calculateAbsHumidity(yearInput, monthInput, airQualityCollection);
    // if avg = 0 -> cannot find data corresponding to monthInput
    if (avgAbsHumid == 0)
    {
        return;
    }
    for (int i = 0; i < airQualityCollection.size(); i++){
        if (airQualityCollection[i].getDate().getYear() == yearInput && airQualityCollection[i].getDate().getMonth() == monthInput){
            if (airQualityCollection[i].getAbsHumidity() > avgAbsHumid){
                absHumidHigherThanAvg.push_back(airQualityCollection[i]);
            }
        }
    }
}

