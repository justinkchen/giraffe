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
#ifndef _MSG_BOX_POPUP_FORM_H_
#define _MSG_BOX_POPUP_FORM_H_

#include "BaseForm.h"

class MsgBoxPopupForm
	: public BaseForm
	, Tizen::Ui::IProgressPopupEventListener
{
public:
	MsgBoxPopupForm(void);
	virtual ~MsgBoxPopupForm(void);

	virtual bool Initialize(void);
	void ShowMessageBox(void);
	void ShowPopup(void);
	void HidePopup(void);
	void ShowProgressPopup(void);
	void HideProgressPopup(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	//IProgressPopupEventListener
	virtual void OnProgressPopupCanceled(void);

private:
	static const int ID_BUTTON_MESSAGEBOX = 501;
	static const int ID_BUTTON_POPUP = 502;
	static const int ID_BUTTON_CLOSE_POPUP = 503;
	static const int ID_BUTTON_PROGRESSPOPUP = 504;
	static const int ID_BUTTON_CLOSE_PROGRESSPOPUP = 505;

	Tizen::Ui::Controls::Popup* __pPopup;
	Tizen::Ui::Controls::ProgressPopup* __pProgressPopup;
	Tizen::Ui::Controls::Label* __pLabel;
}; // MsgBoxPopupForm

#endif // _MSG_BOX_POPUP_FORM_H_
