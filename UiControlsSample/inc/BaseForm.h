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
#ifndef _BASE_FORM_H_
#define _BASE_FORM_H_

#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FBase.h>

class BaseForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
{
public:
	BaseForm(void);
	virtual ~BaseForm(void);

	virtual bool Initialize(void) = 0;
	virtual result OnInitializing(void);
	bool SetFooter(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source) ;

protected:
	static const int ID_EXIT = 100;
}; // BaseForm

#endif // _BASE_FORM_H_
