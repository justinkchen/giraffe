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
#ifndef _EDIT_FORM_H_
#define _EDIT_FORM_H_

#include "BaseForm.h"

class EditForm
	: public BaseForm
	, public Tizen::Ui::ITextEventListener
{
public:
	EditForm(void);
	virtual ~EditForm(void);

	virtual bool Initialize(void);
	virtual result OnInitializing(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);

private:
	static const int ID_BUTTON_OK = 201;
	static const int ID_BUTTON_CLEAR = 202;

	Tizen::Ui::Controls::EditArea* __pEditArea;
	Tizen::Ui::Controls::EditField* __pEditField;
	Tizen::Ui::Controls::EditField* __pEditFieldDisable;

}; // EditForm

#endif // _EDIT_FORM_H_
