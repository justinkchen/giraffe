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
#ifndef _TEXTBOX_FORM_H_
#define _TEXTBOX_FORM_H_

#include "BaseForm.h"

class TextBoxForm
	: public BaseForm
{
public:
	TextBoxForm(void);
	virtual ~TextBoxForm(void);

	virtual bool Initialize(void);
	virtual result OnInitializing(void);

private:
	static const int ID_BUTTON_UP = 301;
	static const int ID_BUTTON_DOWN = 302;
	static const int ID_BUTTON_COLOR = 303;

	Tizen::Ui::Controls::TextBox* __pTextBox;
}; // TextBoxForm

#endif // _TEXTBOX_FORM_H_
