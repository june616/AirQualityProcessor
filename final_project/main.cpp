#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "vector"
#include "string"
#include "Date.h"
#include "Date.cpp"
#include "Time.h"
#include "Time.cpp"
#include "AirQuality.h"
#include "AirQuality.cpp"
using namespace std;

// int main() {
//     ifstream inFile;
//     string line;
//     string word;
//
//     vector<vector<string>> content;
//     vector<string> row;
//
//     inFile.open("AirQualityUCI.csv");
//     if(!inFile) {
//         cout << "File not found." << endl;
//         return 1;
//     }
//
//     while(getline(inFile, line))
//     {
//         row.clear();
//
//         stringstream str(line);
//
//         while(getline(str, word, ','))
//             if(!word.empty()) {
//                 row.push_back(word);
//             }
//
//         content.push_back(row);
//     }
//
//     vector<AirQuality> air;
//     for(int i = 1;  i < content.size(); i++) {
//
//         vector<string> contentItem = content[i];
//         string temp = contentItem[contentItem.size() - 3];
//         string rh = contentItem[contentItem.size() - 2];
//         string ah = contentItem[contentItem.size() - 1];
//         string date = contentItem[0];
//         string time = contentItem[1];
//
//         size_t pos = 0;
//         string token;
//         vector<int> dateVec;
//         while ((pos = date.find("/")) != string::npos) {
//             token = date.substr(0, pos);
//             if(!token.empty()) {
//                 int temp = stoi(token);
//                 dateVec.push_back(temp);
//             }
//
//             date.erase(0, pos + 1);
//         }
//
//         size_t pos1 = 0;
//         string token1;
//         vector<int> timeVec;
//         while ((pos1 = time.find(":")) != string::npos) {
//             token1 = time.substr(0, pos1);
//             if(!token1.empty()) {
//                 int temp = stoi(token1);
//
//                 timeVec.push_back(temp);
//             }
//
//             time.erase(0, pos1 + 1);
//         }
//
//         Date theDate = Date(dateVec[1],dateVec[0],dateVec[2]);
//
//         Time theTime = Time(timeVec[2],timeVec[1],timeVec[0]);
//
//         AirQuality airQuality = AirQuality(stod(temp),stod(rh),stod(ah));
//         airQuality.setDate(theDate);
//         airQuality.setTime(theTime);
//         air.push_back(airQuality);
//     }
//
//     int monthInput;
//     double totalTemp = 0.0;
//     int count = 0;
//     cout << "Please enter month to calculate the average temperature." << endl;
//     cin >> monthInput;
//
//     // avg temperature
//     for(int i = 0; i < air.size(); i++) {
//         if(air[i].getDate().getMonth() == monthInput) {
//             totalTemp += air[i].getTemp();
//             count++;
//         }
//     }
//     double avgTemp = totalTemp / count;
//     cout << "The average temperature for month " << monthInput << " is " << avgTemp << " F" << endl;
//
//     // avg relative humidity
//     double totalRelativeHumidity = 0.0;
//     count = 0;
//     cout << "Please enter month to calculate the average relative humidity." << endl;
//     cin >> monthInput;
//     for(int i = 0; i < air.size(); i++) {
//         if(air[i].getDate().getMonth() == monthInput) {
//             totalRelativeHumidity += air[i].getRelativeHumidity();
//             count++;
//         }
//     }
//     double avgRelativeHumidity = totalRelativeHumidity / count;
//     cout << "The average relative humidity for month " << monthInput << " is " << avgRelativeHumidity << endl;
//
//     // avg absolute humidity
//     double totalAbsHumidity = 0.0;
//     count = 0;
//     cout << "Please enter month to calculate the average absolute humidity." << endl;
//     cin >> monthInput;
//     for(int i = 0; i < air.size(); i++) {
//         if(air[i].getDate().getMonth() == monthInput) {
//             totalAbsHumidity += air[i].getAbsHumidity();
//             count++;
//         }
//     }
//     double avgAbsHumidity = totalAbsHumidity / count;
//     cout << "The average absolute humidity for month " << monthInput << " is " << avgAbsHumidity << endl;
//
//     inFile.close();
//     return 0;
// }

void getData(ifstream &inFile, vector<string>& fields, vector<AirQuality>& airQualityCollection);
Date processDate(string inputStr);
Time processTime(string inputStr);

int main()
{
    ifstream myFile("test.csv");

    if (!myFile.is_open())
    {
        cout << "File not found." << endl;
        return 1;
    }

    vector<string> fields;
    vector<AirQuality> airQualityCollection;
    getData(myFile, fields, airQualityCollection);

    for (int i = 0; i < airQualityCollection.size(); i++){
        cout << airQualityCollection.at(i) << endl;
    }
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

    static const int DAY_IDX = 0;
    static const int MONTH_IDX = 1;
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

