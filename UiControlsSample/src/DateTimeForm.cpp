//
// Tizen native SDK
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "DateTimeForm.h"
#include <FLocales.h>
#include <FSystem.h>

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::System;

const int LABEL_HEIGHT = 100;

DateTimeForm::DateTimeForm(void)
	: __pDateTimePicker(null)
	, __pDatePicker(null)
	, __pTimePicker(null)
	, __pEditDate(null)
	, __pEditDateDisable(null)
	, __pEditDateNotitle(null)
	, __pEditTime(null)
	, __pEditTimeDisable(null)
	, __pEditTimeNotitle(null)
{
}

DateTimeForm::~DateTimeForm(void)
{
}

bool
DateTimeForm::Initialize(void)
{
	Construct(L"IDF_FORM_DATETIME");

	return true;
}

result
DateTimeForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	__pEditDateDisable = static_cast<EditDate*>(GetControl("IDC_EDITDATE_DISABLE", true));
	__pEditDateDisable->SetCurrentDate();
	__pEditDateDisable->SetEnabled(false);
	__pEditDateDisable->AddDateChangeEventListener(*this);

	__pEditDate = static_cast<EditDate*>(GetControl("IDC_EDITDATE", true));
	__pEditDate->SetCurrentDate();
	__pEditDate->AddDateChangeEventListener(*this);

	__pEditDateNotitle = static_cast<EditDate*>(GetControl("IDC_EDITDATE_NO_TITLE", true));
	__pEditDateNotitle->SetCurrentDate();
	__pEditDateNotitle->AddDateChangeEventListener(*this);

	__pEditTimeDisable = static_cast<EditTime*>(GetControl("IDC_EDITTIME_DISABLE", true));
	__pEditTimeDisable->SetCurrentTime();
	__pEditTimeDisable->SetEnabled(false);
	__pEditTimeDisable->AddTimeChangeEventListener(*this);

	__pEditTime = static_cast<EditTime*>(GetControl("IDC_EDITTIME", true));
	__pEditTime->SetCurrentTime();
	__pEditTime->AddTimeChangeEventListener(*this);

	__pEditTimeNotitle = static_cast<EditTime*>(GetControl("IDC_EDITTIME_NO_TITLE", true));
	__pEditTimeNotitle->SetCurrentTime();
	__pEditTimeNotitle->AddTimeChangeEventListener(*this);

	__pDateTimePicker = new (std::nothrow) DateTimePicker();
	__pDateTimePicker->Construct();
	__pDateTimePicker->AddDateTimeChangeEventListener(*this);

	__pDatePicker = new (std::nothrow) DatePicker();
	__pDatePicker->Construct();
	__pDatePicker->AddDateChangeEventListener(*this);

	__pTimePicker = new (std::nothrow) TimePicker();
	__pTimePicker->Construct();
	__pTimePicker->AddTimeChangeEventListener(*this);

	Button* pButtonDatePicker = static_cast<Button*>(GetControl("IDC_BUTTON_DATEPICKER", true));
	if(pButtonDatePicker)
	{
		pButtonDatePicker->SetActionId(ID_BUTTON_DATE_ON);
		pButtonDatePicker->AddActionEventListener(*this);
	}
	Button* pButtonTimePicker = static_cast<Button*>(GetControl("IDC_BUTTON_TIMEPICKER", true));
	if(pButtonTimePicker)
	{
		pButtonTimePicker->SetActionId(ID_BUTTON_TIME_ON);
		pButtonTimePicker->AddActionEventListener(*this);
	}
	Button* pButtonDateTimePicker = static_cast<Button*>(GetControl("IDC_BUTTON_DATETIMEPICKER", true));
	if(pButtonDateTimePicker)
	{
		pButtonDateTimePicker->SetActionId(ID_BUTTON_DATETIME_ON);
		pButtonDateTimePicker->AddActionEventListener(*this);
	}
	return r;
}

result
DateTimeForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	delete __pDateTimePicker;
	delete __pDatePicker;
	delete __pTimePicker;

	return r;
}

 void
DateTimeForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_BUTTON_DATE_ON:
		__pDatePicker->Show();
		break;
	case ID_BUTTON_TIME_ON:
		__pTimePicker->Show();
		break;
	case ID_BUTTON_DATETIME_ON:
		__pDateTimePicker->Show();
		break;
	default:
		break;
	}
}

void
DateTimeForm::OnDateTimeChanged(const Control &source, int year, int month, int day, int hour, int minute)
{
	String formattedString;
	DateTime datetime;
	Locale locale(LANGUAGE_ENG, COUNTRY_GB);

	if (__pDateTimePicker)
	{
		datetime = __pDateTimePicker->GetDateTime();
		__pEditDate->SetDate(datetime);
		__pEditDateNotitle->SetDate(datetime);
		__pEditDateDisable->SetDate(datetime);
		__pEditTime->SetTime(datetime);
		__pEditTimeNotitle->SetTime(datetime);
		__pEditTimeDisable->SetTime(datetime);
	}
	Invalidate(true);
}

void
DateTimeForm::OnDateTimeChangeCanceled(const Control &source)
{

}

void
DateTimeForm::OnDateChanged(const Control& source, int year, int month, int day)
{
	String formattedString;
	DateTime date;
	Locale locale(LANGUAGE_ENG, COUNTRY_GB);

	if(__pDatePicker == &source)
	{
		date = __pDatePicker->GetDate();
		__pEditDate->SetDate(date);
		__pEditDateNotitle->SetDate(date);
		__pEditDateDisable->SetDate(date);
	}
	else
	{
		date = __pEditDate->GetDate();
		__pDatePicker->SetDate(date);
	}

	Invalidate(true);
}

void
DateTimeForm::OnDateChangeCanceled(const Control& source)
{
}
void
DateTimeForm::OnTimeChanged(const Control& source, int hour, int minute)
{
	String formattedString;
	DateTime time;
	Locale locale(LANGUAGE_ENG, COUNTRY_GB);

	if(__pTimePicker == &source)
	{
		time = __pTimePicker->GetTime();
		__pEditTime->SetTime(time);
		__pEditTimeNotitle->SetTime(time);
		__pEditTimeDisable->SetTime(time);
	}
	else
	{
		time = __pEditTime->GetTime();
		__pTimePicker->SetTime(time);
	}

	Invalidate(true);
}

void
DateTimeForm::OnTimeChangeCanceled(const Control& source)
{

}


