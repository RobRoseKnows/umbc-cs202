//
// File: Time.h
// Author: Robert Rose
// Date: 3/28/16
// Section: 03
// E-mail: robrose2@umbc.edu
//

#ifndef TIME_H
#define TIME_H

using namespace std;

class Time {

public:
	Time();
	Time(const int hours, const int minutes);
	// Overloads the addition operator
	Time operator+(const int& minutes) const;
	// Returns true if timeL is before timeR
	bool operator<(const Time& compareTo) const;
	friend ostream &operator<<(ostream &outStream, const Time& time);

private:
	int m_hours;
	int m_minutes;
	// Checks to see if the hours and minutes are valid according to ISO-8601.
	bool validTime(const int hours, const int minutes) const;
};

#endif
