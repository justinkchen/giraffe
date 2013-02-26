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

#include <new>
#include "FormFactory.h"
#include "AnimationForm.h"
#include "ButtonForm.h"
#include "CheckButtonForm.h"
#include "ColorPickerForm.h"
#include "EditForm.h"
#include "MainForm.h"
#include "MenuForm.h"
#include "MsgBoxPopupForm.h"
#include "OverlayKeypadForm.h"
#include "PanelForm.h"
#include "ProgressForm.h"
#include "SliderForm.h"
#include "NavigationForm.h"
#include "DateTimeForm.h"
#include "ListViewForm.h"
#include "GroupedListViewForm.h"
#include "IconListViewForm.h"
#include "SearchBarForm.h"
#include "EnrichedTextForm.h"
#include "ExpandableEditAreaForm.h"
#include "GalleryForm.h"
#include "TextBoxForm.h"
#include "CustomButtonForm.h"
#include "SplitPanelForm.h"
#include "TableViewForm.h"
#include "TabBarForm.h"
#include "QuickPanelFrameForm.h"

using namespace Tizen::Ui::Scenes;


// Definitions of extern.
const wchar_t* FORM_ANIMATION = L"Form_Animation";
const wchar_t* FORM_BUTTON = L"Form_Button";
const wchar_t* FORM_CHECK_BUTTON = L"Form_CheckButton";
const wchar_t* FORM_COLOR_PICKER = L"Form_ColorPicker";
const wchar_t* FORM_CUSTOM_BUTTON = L"Form_CustomButton";
const wchar_t* FORM_TABBAR = L"Form_TabBar";
const wchar_t* FORM_DATE_TIME = L"Form_DateTime";
const wchar_t* FORM_EDIT = L"Form_Edit";
const wchar_t* FORM_ENRICHED_TEXT = L"Form_EnrichedText";
const wchar_t* FORM_EXPANDABLE_EDIT_AREA = L"Form_ExpandableEditArea";
const wchar_t* FORM_GALLERY = L"Form_Gallery";
const wchar_t* FORM_GROUPED_LISTVIEW = L"Form_GroupedListView";
const wchar_t* FORM_ICON_LISTVIEW = L"Form_IconListView";
const wchar_t* FORM_LISTVIEW = L"Form_ListView";
const wchar_t* FORM_MAIN = L"Form_Main";
const wchar_t* FORM_MENU = L"Form_Menu";
const wchar_t* FORM_MSG_BOX_POPUP = L"Form_MsgBox";
const wchar_t* FORM_NAVIGATION = L"Form_Navigation";
const wchar_t* FORM_QUICK_PANEL_FRAME = L"Form_QuickPanelFrame";
const wchar_t* FORM_OVERLAYKEYPAD = L"Form_OverlayKeypad";
const wchar_t* FORM_PANEL = L"Form_Panel";
const wchar_t* FORM_PROGRESS = L"Form_Progress";
const wchar_t* FORM_SEARCHBAR = L"Form_SearchBar";
const wchar_t* FORM_SLIDER = L"Form_Slider";
const wchar_t* FORM_SPLIT_PANEL = L"Form_SplitPanel";
const wchar_t* FORM_TABLEVIEW = L"Form_TableView";
const wchar_t* FORM_TEXTBOX = L"Form_TextBox";

FormFactory::FormFactory(void)
{
}

FormFactory::~FormFactory(void)
{
}

Tizen::Ui::Controls::Form*
FormFactory::CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	Tizen::Ui::Controls::Form* pNewForm = null;
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	if (formId == FORM_ANIMATION)
	{
		AnimationForm* pAnimationForm = new (std::nothrow) AnimationForm();
		pAnimationForm->Initialize();
		pNewForm = pAnimationForm;
	}
	else if (formId == FORM_BUTTON)
	{
		ButtonForm* pButtonForm = new (std::nothrow) ButtonForm();
		pButtonForm->Initialize();
		pNewForm = pButtonForm;
	}
	else if (formId == FORM_CHECK_BUTTON)
	{
		CheckButtonForm* pCheckButtonForm = new (std::nothrow) CheckButtonForm();
		pCheckButtonForm->Initialize();
		pNewForm = pCheckButtonForm;
	}
	else if (formId == FORM_COLOR_PICKER)
	{
		ColorPickerForm* pColorPickerForm = new (std::nothrow) ColorPickerForm();
		pColorPickerForm->Initialize();
		pNewForm = pColorPickerForm;
	}
	else if (formId == FORM_CUSTOM_BUTTON)
	{
		CustomButtonForm* pCustomButtonForm = new (std::nothrow) CustomButtonForm();
		pCustomButtonForm->Initialize();
		pNewForm = pCustomButtonForm;
	}
	else if (formId == FORM_TABBAR)
	{
		TabBarForm* pTabBarForm = new (std::nothrow) TabBarForm();
		pTabBarForm->Initialize();
		pNewForm = pTabBarForm;
	}
	else if (formId == FORM_DATE_TIME)
	{
		DateTimeForm* pDateTimeForm = new (std::nothrow) DateTimeForm();
		pDateTimeForm->Initialize();
		pNewForm = pDateTimeForm;
	}
	else if (formId == FORM_EDIT)
	{
		EditForm* pEditForm = new (std::nothrow) EditForm();
		pEditForm->Initialize();
		pNewForm = pEditForm;
	}
	else if (formId == FORM_ENRICHED_TEXT)
	{
		EnrichedTextForm* pEnrichedTextForm = new (std::nothrow) EnrichedTextForm();
		pEnrichedTextForm->Initialize();
		pNewForm = pEnrichedTextForm;
	}
	else if (formId == FORM_EXPANDABLE_EDIT_AREA)
	{
		ExpandableEditAreaForm* pExpandableEditAreaForm = new (std::nothrow) ExpandableEditAreaForm();
		pExpandableEditAreaForm->Initialize();
		pNewForm = pExpandableEditAreaForm;
	}
	else if (formId == FORM_GALLERY)
	{
		GalleryForm* pGalleryForm = new (std::nothrow) GalleryForm();
		pGalleryForm->Initialize();
		pNewForm = pGalleryForm;
	}
	else if (formId == FORM_GROUPED_LISTVIEW)
	{
		GroupedListViewForm* pGroupedListViewForm = new (std::nothrow) GroupedListViewForm();
		pGroupedListViewForm->Initialize();
		pNewForm = pGroupedListViewForm;
	}
	else if (formId == FORM_ICON_LISTVIEW)
	{
		IconListViewForm* pIconListViewForm = new (std::nothrow) IconListViewForm();
		pIconListViewForm->Initialize();
		pNewForm = pIconListViewForm;
	}
	else if (formId == FORM_LISTVIEW)
	{
		ListViewForm* pListViewForm = new (std::nothrow) ListViewForm();
		pListViewForm->Initialize();
		pNewForm = pListViewForm;
	}
	else if (formId == FORM_MAIN)
	{
		MainForm* pMainForm = new (std::nothrow) MainForm();
		pMainForm->Initialize();
		pNewForm = pMainForm;
	}
	else if (formId == FORM_MENU)
	{
		MenuForm* pMenuForm = new (std::nothrow) MenuForm();
		pMenuForm->Initialize();
		pNewForm = pMenuForm;
	}
	else if (formId == FORM_MSG_BOX_POPUP)
	{
		MsgBoxPopupForm* pMsgBoxPopupForm = new (std::nothrow) MsgBoxPopupForm();
		pMsgBoxPopupForm->Initialize();
		pNewForm = pMsgBoxPopupForm;
	}
	else if (formId == FORM_NAVIGATION)
	{
		NavigationForm* pNavigationForm = new (std::nothrow) NavigationForm();
		pNavigationForm->Initialize();
		pNewForm = pNavigationForm;
	}
	else if (formId == FORM_OVERLAYKEYPAD)
	{
		OverlayKeypadForm* pOverlayKeypadForm = new (std::nothrow) OverlayKeypadForm();
		pOverlayKeypadForm->Initialize();
		pNewForm = pOverlayKeypadForm;
	}
	else if (formId == FORM_PANEL)
	{
		PanelForm* pPanelForm = new (std::nothrow) PanelForm();
		pPanelForm->Initialize();
		pNewForm = pPanelForm;
	}
	else if (formId == FORM_PROGRESS)
	{
		ProgressForm* pProgressForm = new (std::nothrow) ProgressForm();
		pProgressForm->Initialize();
		pNewForm = pProgressForm;
	}
	else if (formId == FORM_SEARCHBAR)
	{
		SearchBarForm* pSearchBarForm = new (std::nothrow) SearchBarForm();
		pSearchBarForm->Initialize();
		pNewForm = pSearchBarForm;
	}
	else if (formId == FORM_SLIDER)
	{
		SliderForm* pSliderForm = new (std::nothrow) SliderForm();
		pSliderForm->Initialize();
		pNewForm = pSliderForm;
	}
	else if (formId == FORM_SPLIT_PANEL)
	{
		SplitPanelForm* pSplitPanelForm = new (std::nothrow) SplitPanelForm();
		pSplitPanelForm->Initialize();
		pNewForm = pSplitPanelForm;
	}
	else if (formId == FORM_TABLEVIEW)
	{
		TableViewForm* pTableViewForm = new (std::nothrow) TableViewForm();
		pTableViewForm->Initialize();
		pNewForm = pTableViewForm;
	}
	else if (formId == FORM_TEXTBOX)
	{
		TextBoxForm* pTextBoxForm = new (std::nothrow) TextBoxForm();
		pTextBoxForm->Initialize();
		pNewForm = pTextBoxForm;
	}
	else if (formId == FORM_QUICK_PANEL_FRAME)
	{
		QuickPanelFrameForm* pQuickPanelFrameForm = new (std::nothrow) QuickPanelFrameForm();
		pQuickPanelFrameForm->Initialize();
		pNewForm = pQuickPanelFrameForm;
	}

	return pNewForm;
}
