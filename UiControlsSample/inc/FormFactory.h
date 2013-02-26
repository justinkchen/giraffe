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

#ifndef _FORM_FACTORY_H_
#define _FORM_FACTORY_H_

#include <FUi.h>

// Use 'extern' to eliminate duplicate data allocation.
extern const wchar_t* FORM_ANIMATION;
extern const wchar_t* FORM_BUTTON;
extern const wchar_t* FORM_CHECK_BUTTON;
extern const wchar_t* FORM_COLOR_PICKER;
extern const wchar_t* FORM_CUSTOM_BUTTON;
extern const wchar_t* FORM_DATA_BIDING;
extern const wchar_t* FORM_DATE_TIME;
extern const wchar_t* FORM_EDIT_DATE;
extern const wchar_t* FORM_EDIT;
extern const wchar_t* FORM_EDIT_TIME;
extern const wchar_t* FORM_ENRICHED_TEXT;
extern const wchar_t* FORM_EXPANDABLE_EDIT_AREA;
extern const wchar_t* FORM_GALLERY;
extern const wchar_t* FORM_GROUPED_LISTVIEW;
extern const wchar_t* FORM_ICON_LISTVIEW;
extern const wchar_t* FORM_LISTVIEW;
extern const wchar_t* FORM_MAIN;
extern const wchar_t* FORM_MENU;
extern const wchar_t* FORM_MSG_BOX_POPUP;
extern const wchar_t* FORM_NAVIGATION;
extern const wchar_t* FORM_QUICK_PANEL_FRAME;
extern const wchar_t* FORM_OVERLAYKEYPAD;
extern const wchar_t* FORM_PANEL;
extern const wchar_t* FORM_PROGRESS;
extern const wchar_t* FORM_RADIOGROUP;
extern const wchar_t* FORM_SEARCHBAR;
extern const wchar_t* FORM_SLIDER;
extern const wchar_t* FORM_SPLIT_PANEL;
extern const wchar_t* FORM_TABBAR;
extern const wchar_t* FORM_TABLEVIEW;
extern const wchar_t* FORM_TEXTBOX;


class FormFactory
	: public Tizen::Ui::Scenes::IFormFactory
{
public:
	FormFactory(void);
	virtual ~FormFactory(void);

	virtual Tizen::Ui::Controls::Form* CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId);
};

#endif // _FORM_FACTORY_H_
