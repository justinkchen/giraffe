/*
 * Date.h
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#ifndef DATE_H_
#define DATE_H_

#include <FBase.h>

class Date {
public:
	Date();
	virtual ~Date();

	// Utility Functions
	Tizen::Base::String dayString(); // Return strings like "March 10, 2013"
	Tizen::Base::String timeString(); // return strings like "11:30 PM"

	// Accessors
	unsigned int year() { return _year; }
	void setYear(unsigned int year) { _year = year; }
	unsigned int month() { return _month; }
	void setMonth(unsigned int month) { _month = month; }
	unsigned int day() { return _day; }
	void setDay(unsigned int day) { _day = day; }
	unsigned int minute() { return _minute; }
	void setMinute(unsigned int minute) { _minute = minute; }
	unsigned int second() { return _second; }
	void setSecond(unsigned int second) { _second = second; }

private:
	unsigned int _year;
	unsigned int _month;
	unsigned int _day;
	unsigned int _hour;
	unsigned int _minute;
	unsigned int _second;

	char *monthString(); // Parse month into its name
};

#endif /* DATE_H_ */