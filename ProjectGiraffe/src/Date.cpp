/*
 * Date.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#include "Date.h"

using namespace Tizen::Base;

Date::Date() {
	// TODO Auto-generated constructor stub

}

Date::~Date() {
	// TODO Auto-generated destructor stub
}

char *Date::monthString() {
	char *monthString = null;
	switch (_month) {
		case 0:
			monthString = "January";
			break;
		case 1:
			monthString = "February";
			break;
		case 2:
			monthString = "March";
			break;
		case 3:
			monthString = "April";
			break;
		case 4:
			monthString = "May";
			break;
		case 5:
			monthString = "June";
			break;
		case 6:
			monthString = "July";
			break;
		case 7:
			monthString = "August";
			break;
		case 8:
			monthString = "September";
			break;
		case 9:
			monthString = "October";
			break;
		case 10:
			monthString = "November";
			break;
		case 11:
			monthString = "December";
			break;
		default:
			monthString = "Invalid";
			break;
	}
	return monthString;
}

String Date::dayString() {
	String dayString;
	dayString.Format(20, L"%s %d, %d", monthString(), _day, _year);
	return dayString;
}

String Date::timeString() {
	String timeString;
	int shouldUseAM = _hour < 12;
	unsigned int adjustedHour = _hour - (shouldUseAM ? 0 : 12);
	timeString.Format(10, L"%d:%d %s", adjustedHour, _minute, shouldUseAM ? L"AM" : L"PM");
	return timeString;
}
