/*
 * Date.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#include "Date.h"
#include "HTTPConnection.h" // TODO: maybe find a better place for the parameter names to live.

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

Date::Date() :
		_year(0),
		_month(0),
		_day(0),
		_hour(0),
		_minute(0),
		_second(0) {}

Date::Date(Tizen::Base::Collection::HashMap *dictionary)
{
	if (dictionary) {
		Double *dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameYear));
		if (dblValue) _year = dblValue->ToInt();
		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameMonth));
		if (dblValue) _month = dblValue->ToInt();
		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameDay));
		if (dblValue) _day = dblValue->ToInt();
		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameHour));
		if (dblValue) _hour = dblValue->ToInt();
		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameMinute));
		if (dblValue) _minute = dblValue->ToInt();
		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameSecond));
		if (dblValue) _second = dblValue->ToInt();
	}
}

Date::~Date() {}

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

HashMap *Date::parameterDictionary()
{
	HashMap *parameters = new HashMap(SingleObjectDeleter);
	parameters->Construct();
	parameters->Add(new String(kHTTPParamNameLongitude), new Double(0.0));
	parameters->Add(new String(kHTTPParamNameYear), new Double(_year));
	parameters->Add(new String(kHTTPParamNameMonth), new Double(_month));
	parameters->Add(new String(kHTTPParamNameDay), new Double(_day));
	parameters->Add(new String(kHTTPParamNameHour), new Double(_hour));
	parameters->Add(new String(kHTTPParamNameMinute), new Double(_minute));
	parameters->Add(new String(kHTTPParamNameSecond), new Double(_second));
	return parameters;
}

