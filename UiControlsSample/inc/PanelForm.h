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
#ifndef _PANEL_FORM_H_
#define _PANEL_FORM_H_

#include "BaseForm.h"

class PanelForm
	: public BaseForm
{
public:
	PanelForm(void);
	virtual ~PanelForm(void);

	virtual bool Initialize(void);
	virtual result OnInitializing(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

private:
	static const int ID_BUTTON_SCROLL_PANEL = 501;
	static const int ID_BUTTON_PANEL = 502;

	Tizen::Ui::Controls::Label* __pLabelLog;
}; // PanelForm

#endif // _PANEL_FORM_H_
