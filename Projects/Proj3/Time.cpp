//
// File: Time.cpp
// Author: Robert Rose
// Date: 3/28/16
// Section: 03
// E-mail: robrose2@umbc.edu
// Description:
// This is the class implementation for the Time object that keeps track of
// train times. It allows for addition, comparison and printing.

#include<iostream>
#include<string>
using namespace std;

#include "Time.h"

Time::Time() :
		m_hours(0), m_minutes(0) {
}

Time::Time(const int hours, const int minutes) {
	if (validTime(hours, minutes)) {
		m_hours = hours;
		m_minutes = minutes;
	} else {
		m_hours = 0;
		m_minutes = 0;
	}
}

ostream &operator<<(ostream &output, const Time &time) {
	// Using ternary operators to zero pad.
	output << time.m_hours << (time.m_minutes < 10 ? ":0" : ":")
			<< time.m_minutes;
	return output;
}

Time Time::operator+(const int &minutes) const {
	int newHours = m_hours;
	int newMinutes = m_minutes + minutes;

	// Check for minute overflow
	if (newMinutes >= 60) {
		newMinutes -= 60;
		newHours += 1;
	}

	// Check for hour overflow and that it isn't midnight.
	if (newHours >= 24 && newMinutes != 0) {
		newHours -= 24;
	}

	return Time(newHours, newMinutes);
}

bool Time::operator<(const Time &compareTo) const {
	if (m_hours < compareTo.m_hours) {
		return true;
	} else if (m_hours > compareTo.m_hours) {
		return false;
	} else if (m_minutes < compareTo.m_minutes) {
		return true;
	} else {
		return false;
	}
}

bool Time::validTime(const int hours, const int minutes) const {
	// Check to make sure minutes is from 0-59
	if (minutes >= 0 && minutes < 60) {
		//Check to see if it's midnight.
		if (minutes == 0 && hours == 24) {
			return true;
		} else if (hours >= 0 && hours < 24) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
