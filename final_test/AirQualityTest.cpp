#include <iostream>
#include "AirQuality.h"

int main()
{
    // No.1 Default constructor test
    AirQuality a;
    cout << "Actual:"
         << a.getTemp() << " "
         << a.getRelativeHumidity() << " "
         << a.getAbsHumidity() << endl;
    cout << "Expect:0 0 0" << endl;

    // No.2 Constructor with temp, relativeHumidity, absHumidity
    AirQuality b(12.2, 40.1, 50.3);
    cout << "Actual:"
         << b.getTemp() << " "
         << b.getRelativeHumidity() << " "
         << b.getAbsHumidity() << endl;
    cout << "Expect:12.2 40.1 50.3" << endl;

    // No.3 Constructor with all parameters.
    Date d;
    Time t;
    AirQuality c(d, t, 1.1, 2.2, 3.3);
    cout << "Actual:"
         << c.getDate() << " "
         << c.getTime() << " "
         << c.getTemp() << " "
         << c.getRelativeHumidity() << " "
         << c.getAbsHumidity() << endl;
    cout << "Expect:1/1/2000 1/1/1 1.1 2.2 3.3" << endl;

    // No.4 setDate
    Date d2(15, 3, 2022);
    AirQuality a1;
    cout << "Actual:"
         << a1.getDate() << endl;
    cout << "Expect:1/1/2000" << endl;
    a1.setDate(d2);
    cout << "Actual:"
         << a1.getDate() << endl;
    cout << "Expect:15/3/2022" << endl;

    // No.5 setTime
    Time t2(40,20,15);
    AirQuality a2;
    cout << "Actual:"
         << a2.getTime() << endl;
    cout << "Expect:1/1/1" << endl;
    a2.setTime(t2);
    cout << "Actual:"
         << a2.getTime() << endl;
    cout << "Expect:40/20/15" << endl;

    // No.6 setTemp
    AirQuality a3;
    a3.setTemp(15);
    cout << "Actual:" << a3.getTemp() << endl;
    cout << "Expect:15" << endl;

    // No.7 setRelativeHumidity;
    AirQuality a4;
    a4.setRelativeHumidity(20);
    cout << "Actual:" << a4.getRelativeHumidity() << endl;
    cout << "Expect:20" << endl;

    // No.8 setAbsHumidity
    AirQuality a5;
    a5.setAbsHumidity(35);
    cout << "Actual:" << a5.getAbsHumidity() << endl;
    cout << "Expect:35" << endl;

    // No.9 getAbsHumidity
    cout << "Actual:" << a5.getAbsHumidity() << endl;
    cout << "Expect:35" << endl;

    // No.10 getRelativeHumidity
    cout << "Actual:" << a4.getRelativeHumidity() << endl;
    cout << "Expect:20" << endl;

    // No.11 getTemp
    cout << "Actual:" << a3.getTemp() << endl;
    cout << "Expect:15" << endl;
}
