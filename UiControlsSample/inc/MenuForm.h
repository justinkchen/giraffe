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
#ifndef _MENU_FORM_H_
#define _MENU_FORM_H_

#include <FApp.h>
#include "BaseForm.h"

class MenuForm
	: public BaseForm
{
public:
	MenuForm(void);
	virtual ~MenuForm(void);

	virtual bool Initialize(void);
	void CreateContextMenuListStyle(void);
	void CreateContextMenuGridStyle(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

private:
	static const int ID_BUTTON_CONTEXT_LIST = 101;
	static const int ID_BUTTON_CONTEXT_GRID = 103;
	static const int ID_BUTTON_OPTION = 104;
	static const int ID_BUTTON_CONTEXT_ICON_TEXT = 105;
	static const int ID_CONTEXT_ITEM1 = 200;
	static const int ID_CONTEXT_ITEM2 = 201;
	static const int ID_CONTEXT_ITEM3 = 202;
	static const int ID_CONTEXT_ITEM4 = 203;
	static const int ID_CONTEXT_ITEM5 = 204;
	static const int ID_CONTEXT_ITEM6 = 205;


	Tizen::Ui::Controls::ContextMenu* __pContextMenuIcon;
	Tizen::Ui::Controls::ContextMenu* __pContextMenuIconText;
	Tizen::Ui::Controls::ContextMenu* __pContextMenuGrid;
	Tizen::Ui::Controls::Label* __pLabelLog;
}; // MenuForm

#endif // _MENU_FORM_H_
