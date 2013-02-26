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

#include "SceneRegister.h"
#include "FormFactory.h"
#include <FUi.h>

using namespace Tizen::Ui::Scenes;

// Definitions of extern.
const wchar_t* SCENE_ANIMATION_FORM = L"Scene_AnimationForm";
const wchar_t* SCENE_BUTTON_FORM = L"Scene_ButtonForm";
const wchar_t* SCENE_CHECK_BUTTON_FORM = L"Scene_CheckButtonForm";
const wchar_t* SCENE_COLOR_PICKER_FORM = L"Scene_ColorPickerForm";
const wchar_t* SCENE_CUSTOM_BUTTON_FORM = L"Scene_CustomButtonForm";
const wchar_t* SCENE_DATE_TIME_FORM = L"Scene_DateTiemForm";
const wchar_t* SCENE_EDIT_DATE_FORM = L"Scene_EditDateForm";
const wchar_t* SCENE_EDIT_FORM = L"Scene_EditForm";
const wchar_t* SCENE_EDIT_TIME_FORM = L"Scene_EditTimeForm";
const wchar_t* SCENE_ENRICHED_TEXT_FORM = L"Scene_EnrichedTextForm";
const wchar_t* SCENE_EXPANDABLE_EDIT_AREA_FORM = L"Scene_ExpandableEditAreaForm";
const wchar_t* SCENE_GALLERY_FORM = L"Scene_GalleryForm";
const wchar_t* SCENE_GROUPED_LISTVIEW_FORM = L"Scene_GroupedListViewForm";
const wchar_t* SCENE_ICON_LISTVIEW_FORM = L"Scene_IconListViewForm";
const wchar_t* SCENE_LISTVIEW_FORM = L"Scene_ListViewForm";
const wchar_t* SCENE_MAIN_FORM = L"Scene_MainForm";
const wchar_t* SCENE_MENU_FORM = L"Scene_MenuForm";
const wchar_t* SCENE_MSG_BOX_POPUP_FORM = L"Scene_MsgboxPopupForm";
const wchar_t* SCENE_NAVIGATION_FORM = L"Scene_NavigationForm";
const wchar_t* SCENE_QUICK_PANEL_FRAME_FORM = L"Scene_QuickPanelFrame";
const wchar_t* SCENE_OVERLAYKEYPAD_FORM = L"Scene_OverlayKeypadForm";
const wchar_t* SCENE_PANEL_FORM = L"Scene_PanelForm";
const wchar_t* SCENE_PROGRESS_FORM = L"Scene_ProgressForm";
const wchar_t* SCENE_RADIOGROUP_FORM = L"Scene_RadioForm";
const wchar_t* SCENE_SEARCHBAR_FORM = L"Scene_SearchBarForm";
const wchar_t* SCENE_SLIDER_FORM = L"Scene_SliderForm";
const wchar_t* SCENE_SPLIT_PANEL_FORM = L"Scene_SplitPanelForm";
const wchar_t* SCENE_TABBAR_FORM = L"Scene_TabBarForm";
const wchar_t* SCENE_TABLEVIER_FORM = L"Scene_TableViewForm";
const wchar_t* SCENE_TEXTBOX_FORM = L"Scene_TextBoxForm";

SceneRegister::SceneRegister(void)
{
}

SceneRegister::~SceneRegister(void)
{
}

void
SceneRegister::RegisterAllScenes(void)
{
	static const wchar_t* PANEL_BLANK = L"";
	static FormFactory formFactory;

	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	pSceneManager->RegisterFormFactory(formFactory);

	pSceneManager->RegisterScene(SCENE_ANIMATION_FORM, FORM_ANIMATION, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_BUTTON_FORM, FORM_BUTTON, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_CHECK_BUTTON_FORM, FORM_CHECK_BUTTON, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_COLOR_PICKER_FORM, FORM_COLOR_PICKER, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_CUSTOM_BUTTON_FORM, FORM_CUSTOM_BUTTON, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_DATE_TIME_FORM, FORM_DATE_TIME, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_EDIT_FORM, FORM_EDIT, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_ENRICHED_TEXT_FORM, FORM_ENRICHED_TEXT, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_EXPANDABLE_EDIT_AREA_FORM, FORM_EXPANDABLE_EDIT_AREA, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_GALLERY_FORM, FORM_GALLERY, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_GROUPED_LISTVIEW_FORM, FORM_GROUPED_LISTVIEW, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_ICON_LISTVIEW_FORM, FORM_ICON_LISTVIEW, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_LISTVIEW_FORM, FORM_LISTVIEW, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_MAIN_FORM, FORM_MAIN, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_MENU_FORM, FORM_MENU, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_MSG_BOX_POPUP_FORM, FORM_MSG_BOX_POPUP, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_NAVIGATION_FORM, FORM_NAVIGATION, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_QUICK_PANEL_FRAME_FORM, FORM_QUICK_PANEL_FRAME, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_OVERLAYKEYPAD_FORM, FORM_OVERLAYKEYPAD, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_PANEL_FORM, FORM_PANEL, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_PROGRESS_FORM, FORM_PROGRESS, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_SEARCHBAR_FORM, FORM_SEARCHBAR, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_SLIDER_FORM, FORM_SLIDER, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_SPLIT_PANEL_FORM, FORM_SPLIT_PANEL, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_TABBAR_FORM, FORM_TABBAR, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_TABLEVIER_FORM, FORM_TABLEVIEW, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_TEXTBOX_FORM, FORM_TEXTBOX, PANEL_BLANK);
	pSceneManager->RegisterScene(SCENE_QUICK_PANEL_FRAME_FORM, FORM_QUICK_PANEL_FRAME, PANEL_BLANK);
}
