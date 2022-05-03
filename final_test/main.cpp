//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include "vector"
//#include "string"
//#include "Date.h"
//#include "Time.h"
//#include "AirQuality.h"
//
//
//int main() {
//
//    Date date = Date(1,1,2022);
//    int day = date.getDay();
//    //Expected to be 1, actually get 1
//    cout << day << endl;
//
//    int month = date.getMonth();
//    //Expected to be 1, actually get 1
//    cout << month << endl;
//
//    int year = date.getYear();
//    //Expected to be 2022, actually get 2022
//    cout << year << endl;
//
//    date.setDay(10);
//    date.setMonth(10);
//    date.setYear(2023);
//
//    day = date.getDay();
//    //Expected to be 10, actually get 10
//    cout << day << endl;
//
//    month = date.getMonth();
//    //Expected to be 10, actually get 10
//    cout << month << endl;
//
//    year = date.getYear();
//    //Expected to be 2023, actually get 2023
//    cout << year << endl;
//
//    date.setDmy(12,12,2020);
//    //Expected to be 12/12/2020, actually get 12/12/2020
//    date.print();
//    cout << endl;
//
//    Date date1 = Date(21,12,2022);
//    Date date2 = Date(20,12,2022);
//
//    bool checker1 = date1 > date2;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker1 << endl;
//
//    Date date3 = Date(22,1,2022);
//    bool checker6 = date1 > date3;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker6 << endl;
//
//    Date date4 = Date(22,12,2021);
//
//    bool checker7 = date1 > date4;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker7 << endl;
//
//    bool checker2 = date1 >= date1;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker2 << endl;
//
//    bool checker3 = date1 <= date1;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker3 << endl;
//
//    bool checker4 = date2 < date1;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker4 << endl;
//
//    bool checker5 = date1 == date1;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker5 << endl;
//
//    bool checker8 = date1 != date3;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker8 << endl;
//
//    return 0;
//}
//
//
//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include "vector"
//#include "string"
//#include "Date.h"
//#include "Time.h"
//#include "AirQuality.h"
//
//
//int main() {
//
//    Time time = Time(1,1,3);
//
//    int sec = time.getSec();
//    //Expected to be 1, actually get 1
//    cout << sec << endl;
//
//    int min = time.getMin();
//    //Expected to be 1, actually get 1
//    cout << min << endl;
//
//    int hour = time.getHour();
//    //Expected to be 3, actually get 3
//    cout << hour << endl;
//
//    time.setSec(10);
//    time.setMin(10);
//    time.setHour(2);
//
//    sec = time.getSec();
//    //Expected to be 10, actually get 10
//    cout << sec << endl;
//
//    min = time.getMin();
//    //Expected to be 10, actually get 10
//    cout << min << endl;
//
//    hour = time.getHour();
//    //Expected to be 2, actually get 2
//    cout << hour << endl;
//
//    time.setSmh(12,12,2);
//    //Expected to be 12:12:2, actually get 12:12:2
//    time.print();
//    cout << endl;
//
//    Time time1 = Time(10,10,10);
//    Time time2 = Time(9,10,10);
//
//    bool checker1 = time1 > time2;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker1 << endl;
//
//    bool checker2 = time1 >= time2;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker2 << endl;
//
//    Time time3 = Time(10,9,10);
//    bool checker3 = time1 > time3;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker3 << endl;
//
//    Time time4 = Time(10,9,9);
//    bool checker4 = time1 > time4;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker4 << endl;
//
//    bool checker5 = time1 != time3;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker5 << endl;
//
//    bool checker6 = time1 == time1;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker6 << endl;
//
//    Time time7 = Time(12,10,10);
//    bool checker7 = time1 < time7;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker7 << endl;
//
//    Time time8 = Time(1,12,10);
//    bool checker8 = time1 < time8;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker8 << endl;
//
//    Time time9 = Time(12,10,11);
//    bool checker9 = time1 < time9;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker9 << endl;
//
//    bool checker10 = time7 <= time7;
//    cout << boolalpha;
//    //Expected to be true, actually get true
//    cout << checker10 << endl;
//
//    return 0;
//}
