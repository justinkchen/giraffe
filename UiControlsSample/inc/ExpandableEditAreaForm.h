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
#ifndef _EXPANDABLEEDITAREA_FORM_H_
#define _EXPANDABLEEDITAREA_FORM_H_

#include "BaseForm.h"

class ExpandableEditAreaForm
	: public BaseForm
	, public Tizen::Ui::IKeypadEventListener
	, public Tizen::Ui::Controls::IExpandableEditAreaEventListener
{
public:
	ExpandableEditAreaForm(void);
	virtual ~ExpandableEditAreaForm(void);

	virtual bool Initialize(void);
	void LayoutHeader(void);
	void LayoutContent(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnKeypadActionPerformed(Tizen::Ui::Control& source, Tizen::Ui::KeypadAction keypadAction);
	virtual void OnKeypadClosed(Tizen::Ui::Control& source);
	virtual void OnKeypadOpened(Tizen::Ui::Control& source);
	virtual void OnKeypadWillOpen(Tizen::Ui::Control& source);
	virtual void OnKeypadBoundsChanged(Tizen::Ui::Control& source);
	virtual void OnExpandableEditAreaLineAdded(Tizen::Ui::Controls::ExpandableEditArea& source, int newLineCount);
	virtual void OnExpandableEditAreaLineRemoved(Tizen::Ui::Controls::ExpandableEditArea& source, int newLineCount);

private:
	static const int ID_HEADER_BUTTON_SEND = 601;
	static const int PANEL_HEIGHT = 120;
	static const int LEFT_MARGIN = 45;
	static const int RIGHT_MARGIN = 45;
	static const int TOP_MARGIN = 45;
	static const int BOTTOM_MARGIN = 45;
	static const int EXPANDABLEEDITAREA_RIGHT_MARGIN = 180;
	static const int EXPANDABLEEDITAREA_HEIGHT = 90;
	static const int ID_FOOTER_BUTTON_BACK = 100;

	Tizen::Ui::Controls::ExpandableEditArea* __pExpandableEdit;
	Tizen::Ui::Controls::Panel* __pPanel;
	Tizen::Ui::Controls::Label* __pLabel;
	Tizen::Graphics::Rectangle __prevBounds;
}; // ExpandableEditAreaForm

#endif // _EXPANDABLEEDITAREA_FORM_H_
