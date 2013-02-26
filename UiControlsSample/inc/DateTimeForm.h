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
#ifndef _DATETIME_FORM_H_
#define _DATETIME_FORM_H_

#include "BaseForm.h"

class DateTimeForm
	: public BaseForm
	, public Tizen::Ui::IDateTimeChangeEventListener
	, public Tizen::Ui::IDateChangeEventListener
	, public Tizen::Ui::ITimeChangeEventListener
{
public:
	DateTimeForm(void);
	virtual ~DateTimeForm(void);

	virtual bool Initialize(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnDateTimeChangeCanceled (const Tizen::Ui::Control &source);
	virtual void OnDateTimeChanged (const Tizen::Ui::Control &source, int year, int month, int day, int hour, int minute);
	virtual void OnDateChanged(const Tizen::Ui::Control& source, int year, int month, int day);
	virtual void OnDateChangeCanceled(const Tizen::Ui::Control& source);
	virtual void OnTimeChanged(const Tizen::Ui::Control& source, int hour, int minute);
	virtual void OnTimeChangeCanceled(const Tizen::Ui::Control& source);

private:
	static const int ID_BUTTON_DATE_ON = 101;
	static const int ID_BUTTON_TIME_ON = 102;
	static const int ID_BUTTON_DATETIME_ON = 103;

	Tizen::Ui::Controls::DateTimePicker* __pDateTimePicker;
	Tizen::Ui::Controls::DatePicker* __pDatePicker;
	Tizen::Ui::Controls::TimePicker* __pTimePicker;
	Tizen::Ui::Controls::EditDate* __pEditDate;
	Tizen::Ui::Controls::EditDate* __pEditDateDisable;
	Tizen::Ui::Controls::EditDate* __pEditDateNotitle;
	Tizen::Ui::Controls::EditTime* __pEditTime;
	Tizen::Ui::Controls::EditTime* __pEditTimeDisable;
	Tizen::Ui::Controls::EditTime* __pEditTimeNotitle;
}; // DateTimeForm

#endif // _DATETIME_FORM_H_
