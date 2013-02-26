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
#ifndef _OVERLAYKEYPAD_FORM_H_
#define _OVERLAYKEYPAD_FORM_H_

#include "BaseForm.h"

class OverlayKeypadForm
	: public BaseForm
	, public Tizen::Ui::ITextEventListener
	, public Tizen::Ui::IOrientationEventListener
	, public Tizen::Ui::IKeypadEventListener
{
public:
	OverlayKeypadForm(void);
	virtual ~OverlayKeypadForm(void);

	virtual bool Initialize(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);

	virtual void OnOrientationChanged(const Tizen::Ui::Control& source, Tizen::Ui::OrientationStatus orientationStatus);

	virtual void OnKeypadWillOpen(Tizen::Ui::Control& source);
	virtual void OnKeypadOpened(Tizen::Ui::Control& source);
	virtual void OnKeypadClosed(Tizen::Ui::Control& source);
	virtual void OnKeypadActionPerformed(Tizen::Ui::Control& source, Tizen::Ui::KeypadAction keypadAction){};
	virtual void OnKeypadBoundsChanged(Tizen::Ui::Control& source){};

private:
	static const int ID_BUTTON_EDITAREA_CLEAR = 601;
	static const int ID_BUTTON_DONE = 602;
	static const int ID_BUTTON_CANCEL = 603;

	Tizen::Ui::Controls::EditArea* __pEditArea;
	Tizen::Ui::Controls::EditField* __pEditField;
	Tizen::Base::String* __pEditFieldText;
	Tizen::Base::String* __pEditAreaText;
	Tizen::Base::String* __pEditFieldPreText;
	Tizen::Base::String* __pEditAreaPreText;
	Tizen::Ui::Controls::ScrollPanel* __pScrollPanel;
	Tizen::Ui::Controls::HeaderStyle __headerStyle;
}; // OverlayKeypadForm

#endif // _OVERLAYKEYPAD_FORM_H_
