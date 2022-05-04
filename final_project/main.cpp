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
void showWelcomeMsg();
void showMenu();
int  userChoice();
bool validMonth(int monthInput);
void doUserChoice(int option, vector<AirQuality>& airQualityCollection);
Time getValidTime();
int getValidInputMonth();
int getValidInputYear();
int getValidInputDay(int inputYear, int inputMonth);
void doCalOrDis(int option, int yearInput, int monthInput,vector<AirQuality>& airQualityCollection);
void doCalThanAvg(int option, int yearInput, int monthInput, vector<AirQuality>& airQualityCollection, vector<AirQuality>& absHumidHigherThanAvg);
void doFindTempAndHum(Date inputDate, Time inputTime, double &currentTemp, double &currentRelHumidity, vector<AirQuality>& airQualityCollection);


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
    showWelcomeMsg();
    showMenu();
    int res = userChoice();
    int EXIT = -1;
    while (res != EXIT)
    {
        doUserChoice(res, airQualityCollection);
        cout << endl;
        showMenu();
        res = userChoice();
        if (res == EXIT)
        {
            break;
        }
    }
    return 0;
}

/**
 * Read and process data from csv file
 * @param inFile input stream to operate on files
 * @param fields vector stores each line info
 * @param airQualityCollection vector stores AirQuality objects
 */
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

/**
 * Convert string to Date object
 * @param inputStr input string of Date info
 * @return Date object
 */
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

/**
 * Convert string to Time object
 * @param inputStr input string of Time info
 * @return Time object
 */
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

/**
 * Calculate average temperature for that month
 * @param yearInput target year
 * @param monthInput target month
 * @param airQualityCollection vector stores AirQuality objects
 * @return average temperature for that month
 */
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

/**
  * Calculate average relative humidity for that month
  * @param yearInput target year
  * @param monthInput target month
  * @param airQualityCollection vector stores AirQuality objects
  * @return average relative humidity for that month
  */
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

/**
 * Calculate average absolute humidity for that month
 * @param yearInput target year
 * @param monthInput target month
 * @param airQualityCollection vector stores AirQuality objects
 * @return average absolute humidity for that month
 */
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

/**
 * Find the temperature, and relative humidity at that date and time
 * @param dateInput target date
 * @param timeInput target time
 * @param currentTemp temperature at that date and time
 * @param currentRelHumidity relative humidity at that date and time
 * @param airQualityCollection vector stores AirQuality objects
 */
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

/**
 * Find the highest temperature for that month
 * @param yearInput target year
 * @param monthInput target month
 * @param airQualityCollection vector stores AirQuality objects
 * @return highest temperature for that month
 */
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

/**
 * Find the highest relative humidity for that month
 * @param yearInput target year
 * @param monthInput target month
 * @param airQualityCollection vector stores AirQuality objects
 * @return highest relative humidity for that month
 */
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

/**
 * Find the highest absolute humidity for that month
 * @param yearInput target year
 * @param monthInput target month
 * @param airQualityCollection vector stores AirQuality objects
 * @return highest absolute humidity for that month
 */
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

/**
 * Find AirQuality objects with temperature higher than the average temperature for that month
 * @param yearInput target year
 * @param monthInput target month
 * @param airQualityCollection vector stores AirQuality objects
 * @param tempHigherThanAvg vector stores AirQuality objects with temperature higher than the average temperature for that month
 */
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

/**
 * Find AirQuality objects with relative humidity higher than the average relative humidity for that month
 * @param yearInput target year
 * @param monthInput target month
 * @param airQualityCollection vector stores AirQuality objects
 * @param relHumidHigherThanAvg vector stores AirQuality objects with relative humidity higher than the average relative humidity for that month
 */
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

/**
 * Find AirQuality objects with absolute humidity higher than the average absolute humidity for that month
 * @param yearInput target year
 * @param monthInput target month
 * @param airQualityCollection vector stores AirQuality objects
 * @param absHumidHigherThanAvg vector stores AirQuality objects with absolute humidity higher than the average absolute humidity for that month
 */
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

/**
 * Show welcome message to the users
 */
void showWelcomeMsg()
{
    cout << endl;
    cout << "Welcome to the Air Quality Processor!" << endl;
    cout << endl;
}

/**
 * Show menu to the users
 */
void showMenu()
{
    cout << "******************************************************************************" << endl;
    cout << "*                                 MENU                                       *" << endl;
    cout << "* 0.  Display the average temperature for a certain month.                   *" << endl;
    cout << "* 1.  Display the average relative humidity for a certain month.             *" << endl;
    cout << "* 2.  Display the average absolute humidity temperature for a certain month. *" << endl;
    cout << "* 3.  Display the temperature and temperature at a certain date and time.    *" << endl;
    cout << "* 4.  Display the highest temperature for a certain month.                   *" << endl;
    cout << "* 5.  Display the highest relative humidity value for a certain month.       *" << endl;
    cout << "* 6.  Display the highest absolute humidity for a certain month.             *" << endl;
    cout << "* 7.  Display temperature higher than the average for a certain month.       *" << endl;
    cout << "* 8.  Display relative humidity higher than the average for a certain month. *" << endl;
    cout << "* 9. Display absolute humidity higher than the average for a certain month. *" << endl;
    cout << "*                                                                            *" << endl;
    cout << "******************************************************************************" << endl;
}

/**
 * valid user's choice, if the user input a letter instead an integer,
 * or the user input a number greater than 10 or less than -1,
 * will print out the error message and let the user re-enter the value
 * @return a valid choice
 */
int userChoice()
{
    cout << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Please select your option by enter the No." << endl
         << "Enter -1 when you finished." << endl;
    int MAX_OPTION = 10;
    bool selecting = true;
    while (selecting)
    {
        int userInput;
        cin >> userInput;
        while (cin.fail())
        {
            cin.clear();
            int const IGNORE_SIZE = 9999999;
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "ERROR: " << endl;
            cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
            showMenu();
            cin >> userInput;
        }
        if (userInput >= -1 && userInput <= MAX_OPTION)
        {
            selecting = false;
            return userInput;
        }
        else
        {
            cout << "ERROR: " << endl;
            cout << "Invalid option. Option out of range. Please Re-enter." << endl;
            showMenu();
        }
    }
    return -1;
}

/**
 * Validation check for the month input
 * The month should be in range of [1, 12], inclusive
 * @param monthInput - the month need to be checked
 * @return true if the input value is a valid month
 */
bool validMonth(int monthInput)
{
    int MIN_MONTH = 1;
    int MAX_MONTH = 12;
    return (monthInput >= MIN_MONTH && monthInput <= MAX_MONTH);
}


/**
 * validation check for the input time
 * the valid hour should be in range of [0,24], inclusive
 * the valid minutes and second should both
 * be in range of [0, 59], inclusive
 * @param h - the input hour
 * @param m - the input minutes
 * @param s - the input seconds
 * @return true if the input is a valid time
 */
bool validTime(int h, int m, int s)
{
    int MIN_TIME = 0;
    int MAX_HOUR = 24;
    int MAX_MIN_SEC = 59;
    bool hourValidity = ((h >= MIN_TIME) && (h <= MAX_HOUR));
    bool minValidity = ((m >= MIN_TIME) && (m <= MAX_MIN_SEC));
    bool secValidity = ((s >= MIN_TIME ) && (s <= MAX_MIN_SEC));
    return (hourValidity && minValidity && secValidity);
}

/**
 * Get a time from the user. will ask the user to enter
 * the value of hour, minutes, and seconds separately.
 * Will call validTime function to check whether the input is valid
 * If there is an letter or the number is out of the range, will
 * ask the user to input again.
 * @return a valid time
 */
Time getValidTime()
{
    bool invalid = true;
    while (invalid)
    {
        int inputHour, inputMin, inputSec;
        cout << "Please enter the value of hour." << endl;
        cin >> inputHour;
        while (cin.fail())
        {
            cin.clear();
            int const IGNORE_SIZE = 9999999;
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "ERROR: " << endl;
            cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
            cin >> inputHour;
        }
        cout << "Please enter the value of minutes." << endl;
        cin >> inputMin;
        while (cin.fail())
        {
            cin.clear();
            int const IGNORE_SIZE = 9999999;
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "ERROR: " << endl;
            cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
            cin >> inputMin;
        }
        cout << "Please enter the value of seconds." << endl;
        cin >> inputSec;
        while (cin.fail())
        {
            cin.clear();
            int const IGNORE_SIZE = 9999999;
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "ERROR: " << endl;
            cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
            cin >> inputSec;
        }
        if (validTime(inputHour, inputMin, inputSec))
        {
            invalid = false;
            return Time(inputSec, inputMin, inputHour);
        }
        else
        {
            cout << "Invalid combination, please Re-enter." << endl;
        }
    }
    return Time();
}

/**
 * Get a valid year from the user
 * @return a valid year
 */
int getValidInputYear()
{
    int yearInput;
    cout << "Please enter a year: " << endl;
    cin >> yearInput;
    while (cin.fail())
    {
        cin.clear();
        int const IGNORE_SIZE = 9999999;
        cin.ignore(IGNORE_SIZE, '\n');
        cout << "ERROR: " << endl;
        cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
        cin >> yearInput;
    }
    return yearInput;
}

/**
 * get a valid month from the user
 * @return a valid month
 */
int getValidInputMonth()
{
    int monthInput;
    cout << "Please enter a month: " << endl;
    cin >> monthInput;
    while (cin.fail())
    {
        cin.clear();
        int const IGNORE_SIZE = 9999999;
        cin.ignore(IGNORE_SIZE, '\n');
        cout << "ERROR: " << endl;
        cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
        cin >> monthInput;
    }
    while (!validMonth(monthInput)) {
        cout << "Month should be in range of [1, 12], inclusive" << endl;
        cout << "Please re-enter." << endl;
        cin >> monthInput;
        while (cin.fail()) {
            cin.clear();
            int const IGNORE_SIZE = 9999999;
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "ERROR: " << endl;
            cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
            cin >> monthInput;
        }
    }
    return monthInput;
}

/**
 * validation check for the day of the date
 * will take into consideration of different day in each month and the
 * leap year.
 * @param inputYear - the year user enter
 * @param inputMonth - the month user enter
 * @param inputDay - the day user enter
 * @return - true if the day is in a valid day for the certain month and year
 */
bool validDay(int inputYear, int inputMonth, int inputDay) {
    int validDay[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((inputYear % 4 == 0) && (inputYear % 100 != 0) || (inputYear % 400 == 0))
    {
        int februaryIndex = 2;
        validDay[februaryIndex] = 29;
    }
    int SHIFT = 1;
    return ((inputDay > 0) && (inputDay <= (validDay[(inputMonth) - SHIFT])));
}

/**
 * get a valid day from the user
 * will call the function validDAy to check whether there is a certion day
 * in a certain month
 * @return a valid day
 */
int getValidInputDay(int inputYear, int inputMonth) {
    int dayInput;
    cout << "Please enter a day: " << endl;
    cin >> dayInput;
    while (cin.fail())
    {
        cin.clear();
        int const IGNORE_SIZE = 9999999;
        cin.ignore(IGNORE_SIZE, '\n');
        cout << "ERROR: " << endl;
        cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
        cin >> dayInput;
    }
    while (!validDay(inputYear,inputMonth,dayInput)) {
        cout << "Input day is not valid, there is no " << dayInput << " in the month of " << inputMonth << endl;
        cout << "Please re-enter." << endl;
        cin >> dayInput;
        while (cin.fail()) {
            cin.clear();
            int const IGNORE_SIZE = 9999999;
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "ERROR: " << endl;
            cout << "Invalid option. Only number accepted. Please Re-enter." << endl;
            cin >> dayInput;
        }
    }
    return dayInput;
}

/**
 * call different function based on the user's choice
 * @param option - the valid user's choice
 * @param airQualityCollection - the dataSet need to be handled
 */
void doUserChoice(int option, vector<AirQuality>& airQualityCollection)
{
    int EXIT = -1;
    if (option == EXIT)
    {
        return;
        // exit from the function
    }
    int yearInput = getValidInputYear();
    int monthInput = getValidInputMonth();
    if (option == 3)
    {
        int dayInput = getValidInputDay(yearInput, monthInput);
        Date curDay = Date(dayInput, monthInput, yearInput);
        Time curTime = getValidTime();
        double curTemp, curRelHumidity;
        doFindTempAndHum(curDay, curTime, curTemp, curRelHumidity, airQualityCollection);
    }
    else
    {
        if (option == 0 || option == 1 || option == 2 ||
            option == 4 || option == 5 || option == 6)
        {

            doCalOrDis(option, yearInput, monthInput, airQualityCollection);
        }
        else
        {
            vector<AirQuality> res;
            doCalThanAvg(option, yearInput, monthInput, airQualityCollection, res);
        }
    }
}

/**
 * Calculation or display. Will be called if the user's choice is
 * 0,1,2,4,5,or 6.
 * @param option - the choice
 * @param yearInput - year
 * @param monthInput - month
 * @param airQualityCollection - the data set
 */
void doCalOrDis(int option, int yearInput, int monthInput,vector<AirQuality>& airQualityCollection)
{
    double res;
    int NO_RECORD_CAL = 0;
    int NO_RECORD_DIS = -100;
    switch (option) {
        case 0:
            res = calculateAvgTemp(yearInput, monthInput, airQualityCollection);
            if (res == NO_RECORD_CAL)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The average temperature is: " << res << endl;
            }
            break;
        case 1:
            res = calculateRelHumidity(yearInput, monthInput, airQualityCollection);
            if (res == NO_RECORD_CAL)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The average relative humidity is: " << res << endl;
            }
            break;
        case 2:
            res = calculateAbsHumidity(yearInput, monthInput, airQualityCollection);
            if (res == NO_RECORD_CAL)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The average absolute humidity is: " << res << endl;
            }
            break;
        case 4:
            res = displayMaxTemp(yearInput, monthInput, airQualityCollection);
            if (res == NO_RECORD_DIS)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The highest temperature is: " << res << endl;
            }
            break;
        case 5:
            res = displayMaxRelHumidity(yearInput, monthInput, airQualityCollection);
            if (res == NO_RECORD_DIS)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The highest relative humidity is: " << res << endl;
            }
            break;
        case 6:
            res = displayMaxAbsHumidity(yearInput, monthInput, airQualityCollection);
            if (res == NO_RECORD_DIS)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The highest absolute humidity is: " << res << endl;
            }
            break;
    }
}

/**
 * calculation certain data greater than average
 * @param option - user's choice
 * @param yearInput - year
 * @param monthInput - month
 * @param airQualityCollection - dataSet
 * @param res - temporary container
 */
void doCalThanAvg(int option, int yearInput, int monthInput, vector<AirQuality>& airQualityCollection, vector<AirQuality>& res)
{
    switch (option) {
        case 7:
            findTempHigherThanAvg(yearInput, monthInput, airQualityCollection, res);
            if (res.size() == 0)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The dates and times when temperature is higher than the average are listed below: " << endl;
                for (int i = 0; i < res.size(); i++)
                {
                    cout << "Date: " << setw(2) << res[i].getDate() << setw(10)
                         << "Time: " << setw(2) << res[i].getTime() << setw(18)
                         << "Temperature: " << res[i].getTemp() << endl;
                }
            }
            break;
        case 8:
            findRelHumidHigherThanAvg(yearInput, monthInput, airQualityCollection, res);
            if (res.size() == 0)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The dates and times when relative humidity is higher than the average are listed below: " << endl;
                for (int i = 0; i < res.size(); i++)
                {
                    cout << "Date: " << setw(2) << res[i].getDate() << setw(10)
                         << "Time: " << setw(2) << res[i].getTime() << setw(24)
                         << "Relative Humidity: " << res[i].getRelativeHumidity() << endl;
                }
            }
            break;
        case 9:
            findAbsHumidHigherThanAvg(yearInput, monthInput, airQualityCollection, res);
            if (res.size() == 0)
            {
                cout << "No records found." << endl;
            }
            else
            {
                cout << "The dates and times when absolute humidity is higher than the average are listed below: " << endl;
                for (int i = 0; i < res.size(); i++)
                {
                    cout << "Date: " << setw(2) << res[i].getDate() << setw(10)
                         << "Time: " << setw(2) << res[i].getTime() << setw(24)
                         << "Absolute Humidity: " << res[i].getAbsHumidity() << endl;
                }
            }
            break;
    }
}

/**
 * Find a exertion data.
 * @param inputDate - input date
 * @param inputTime - input time
 * @param currentTemp - current temp
 * @param currentRelHumidity - current relative humidity
 * @param airQualityCollection - dataSet
 */
void doFindTempAndHum(Date inputDate, Time inputTime, double &currentTemp, double &currentRelHumidity, vector<AirQuality>& airQualityCollection)
{
    displayTempAndRelHumidity(inputDate, inputTime, currentTemp, currentRelHumidity,airQualityCollection);
    if (currentTemp == 0 && currentRelHumidity == 0)
    {
        cout << "No records found." << endl;
    }
    else
    {
        cout << "At that date and time, temp is: " << currentTemp << ", rel humid is: " << currentRelHumidity << endl;
    }
}

