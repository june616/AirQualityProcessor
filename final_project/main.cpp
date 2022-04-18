#include <iostream>
#include <fstream>
#include <iomanip>
#include "vector"
#include "string"
#include "Date.h"
#include "Date.cpp"
#include "Time.h"
#include "Time.cpp"
#include "AirQuality.h"
#include "AirQuality.cpp"
using namespace std;

int main() {
    ifstream inFile;
    string line;
    string word;

    vector<vector<string>> content;
    vector<string> row;

    inFile.open("AirQualityUCI.csv");
    if(!inFile) {
        cout << "File not found." << endl;
        return 1;
    }

    while(getline(inFile, line))
    {
        row.clear();

        stringstream str(line);

        while(getline(str, word, ','))
            if(!word.empty()) {
                row.push_back(word);
            }

        content.push_back(row);
    }

    vector<AirQuality> air;
    for(int i = 1;  i < content.size(); i++) {

        vector<string> contentItem = content[i];
        string temp = contentItem[contentItem.size() - 3];
        string rh = contentItem[contentItem.size() - 2];
        string ah = contentItem[contentItem.size() - 1];
        string date = contentItem[0];
        string time = contentItem[1];

        size_t pos = 0;
        string token;
        vector<int> dateVec;
        while ((pos = date.find("/")) != string::npos) {
            token = date.substr(0, pos);
            if(!token.empty()) {
                int temp = stoi(token);
                dateVec.push_back(temp);
            }

            date.erase(0, pos + 1);
        }

        size_t pos1 = 0;
        string token1;
        vector<int> timeVec;
        while ((pos1 = time.find(":")) != string::npos) {
            token1 = time.substr(0, pos1);
            if(!token1.empty()) {
                int temp = stoi(token1);

                timeVec.push_back(temp);
            }

            time.erase(0, pos1 + 1);
        }

        Date theDate = Date(dateVec[1],dateVec[0],dateVec[2]);

        Time theTime = Time(timeVec[2],timeVec[1],timeVec[0]);

        AirQuality airQuality = AirQuality(stod(temp),stod(rh),stod(ah));
        airQuality.setDate(theDate);
        airQuality.setTime(theTime);
        air.push_back(airQuality);
    }

    int monthInput;
    double totalTemp = 0.0;
    int count = 0;
    cout << "Please enter month to calculate the average temperature." << endl;
    cin >> monthInput;

    // avg temperature
    for(int i = 0; i < air.size(); i++) {
        if(air[i].getDate().getMonth() == monthInput) {
            totalTemp += air[i].getTemp();
            count++;
        }
    }
    double avgTemp = totalTemp / count;
    cout << "The average temperature for month " << monthInput << " is " << avgTemp << " F" << endl;

    // avg relative humidity
    double totalRelativeHumidity = 0.0;
    count = 0;
    cout << "Please enter month to calculate the average relative humidity." << endl;
    cin >> monthInput;
    for(int i = 0; i < air.size(); i++) {
        if(air[i].getDate().getMonth() == monthInput) {
            totalRelativeHumidity += air[i].getRelativeHumidity();
            count++;
        }
    }
    double avgRelativeHumidity = totalRelativeHumidity / count;
    cout << "The average relative humidity for month " << monthInput << " is " << avgRelativeHumidity << endl;

    // avg absolute humidity
    double totalAbsHumidity = 0.0;
    count = 0;
    cout << "Please enter month to calculate the average absolute humidity." << endl;
    cin >> monthInput;
    for(int i = 0; i < air.size(); i++) {
        if(air[i].getDate().getMonth() == monthInput) {
            totalAbsHumidity += air[i].getAbsHumidity();
            count++;
        }
    }
    double avgAbsHumidity = totalAbsHumidity / count;
    cout << "The average absolute humidity for month " << monthInput << " is " << avgAbsHumidity << endl;

    inFile.close();
    return 0;
}
