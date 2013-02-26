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

#ifndef _SCENE_REGISTER_H_
#define _SCENE_REGISTER_H_

// Use 'extern' to eliminate duplicate data allocation.
extern const wchar_t* SCENE_ANIMATION_FORM;
extern const wchar_t* SCENE_BUTTON_FORM;
extern const wchar_t* SCENE_CHECK_BUTTON_FORM;
extern const wchar_t* SCENE_COLOR_PICKER_FORM;
extern const wchar_t* SCENE_CUSTOM_BUTTON_FORM;
extern const wchar_t* SCENE_DATA_BIDING_FORM;
extern const wchar_t* SCENE_DATE_TIME_FORM;
extern const wchar_t* SCENE_EDIT_DATE_FORM;
extern const wchar_t* SCENE_EDIT_FORM;
extern const wchar_t* SCENE_EDIT_TIME_FORM;
extern const wchar_t* SCENE_ENRICHED_TEXT_FORM;
extern const wchar_t* SCENE_EXPANDABLE_EDIT_AREA_FORM;
extern const wchar_t* SCENE_GALLERY_FORM;
extern const wchar_t* SCENE_GROUPED_LISTVIEW_FORM;
extern const wchar_t* SCENE_ICON_LISTVIEW_FORM;
extern const wchar_t* SCENE_LISTVIEW_FORM;
extern const wchar_t* SCENE_MAIN_FORM;
extern const wchar_t* SCENE_MENU_FORM;
extern const wchar_t* SCENE_MSG_BOX_POPUP_FORM;
extern const wchar_t* SCENE_NAVIGATION_FORM;
extern const wchar_t* SCENE_QUICK_PANEL_FRAME_FORM;
extern const wchar_t* SCENE_OVERLAYKEYPAD_FORM;
extern const wchar_t* SCENE_PANEL_FORM;
extern const wchar_t* SCENE_PROGRESS_FORM;
extern const wchar_t* SCENE_RADIOGROUP_FORM;
extern const wchar_t* SCENE_SEARCHBAR_FORM;
extern const wchar_t* SCENE_SLIDER_FORM;
extern const wchar_t* SCENE_SPLIT_PANEL_FORM;
extern const wchar_t* SCENE_TABBAR_FORM;
extern const wchar_t* SCENE_TABLEVIER_FORM;
extern const wchar_t* SCENE_TEXTBOX_FORM;
extern const wchar_t* SCENE_QUICKPANEL_FORM;

class SceneRegister
{
public:
	static void RegisterAllScenes(void);

private:
	SceneRegister(void);
	~SceneRegister(void);
};

#endif // _SCENE_REGISTER_H_
