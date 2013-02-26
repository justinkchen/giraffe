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
#include <FAppUiApp.h>
#include "MainForm.h"
#include "SceneRegister.h"

using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Scenes;

MainForm::MainForm(void)
	: __pList(null)
{
}

MainForm::~MainForm(void)
{
}

bool
MainForm::Initialize(void)
{
	Construct(FORM_STYLE_NORMAL| FORM_STYLE_HEADER| FORM_STYLE_INDICATOR| FORM_STYLE_FOOTER);
	return true;
}

result
MainForm::OnInitializing(void)
{
	Header* pHeader = GetHeader();
	pHeader->SetTitleText(L"UI CONTROLS");
	if (!CreateMainList())
	{
		return false;
	}

	Footer* pFooter = GetFooter();
	pFooter->SetBackButton();
	SetFormBackEventListener(this);

	return E_SUCCESS;
}

bool
MainForm::CreateMainList(void)
{
	__pList = new (std::nothrow) ListView();
	__pList->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height), true, false);
	__pList->SetItemProvider(*this);
	__pList->AddListViewItemEventListener(*this);
	AddControl(*__pList);
	return true;
}

void
MainForm::OnListViewItemStateChanged(ListView& view, int index, int elementId, ListItemStatus status)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	if(status == LIST_ITEM_STATUS_SELECTED)
	{
		switch (index)
		{
			case 0:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_ANIMATION_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 1:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_BUTTON_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 2:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_CHECK_BUTTON_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 3:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_COLOR_PICKER_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 4:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_MENU_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 5:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_CUSTOM_BUTTON_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 6:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_DATE_TIME_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 7:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_EDIT_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 8:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_EXPANDABLE_EDIT_AREA_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 9:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_ENRICHED_TEXT_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 10:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_GALLERY_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 11:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_GROUPED_LISTVIEW_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 12:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_NAVIGATION_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 13:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_ICON_LISTVIEW_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 14:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_LISTVIEW_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 15:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_MSG_BOX_POPUP_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 16:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_OVERLAYKEYPAD_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 17:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_PROGRESS_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 18:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_PANEL_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 19:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_SEARCHBAR_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 20:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_SLIDER_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 21:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_SPLIT_PANEL_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 22:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_TABBAR_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 23:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_TABLEVIER_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 24:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_TEXTBOX_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
			case 25:
				pSceneManager->GoForward(ForwardSceneTransition(SCENE_QUICK_PANEL_FRAME_FORM, SCENE_TRANSITION_ANIMATION_TYPE_LEFT));
				break;
		}
	}
}

void
MainForm::OnListViewItemSwept(ListView& listView, int index, SweepDirection direction)
{
}

void
MainForm::OnListViewContextItemStateChanged(ListView& listView, int index, int elementId, ListContextItemStatus state)
{
}

void
MainForm::OnItemReordered(ListView& listView, int oldIndex, int newIndex)
{
}

int
MainForm::GetItemCount(void)
{
	return 26;
}

bool
MainForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;

}

ListItemBase*
MainForm::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem* pItem = new (std::nothrow) CustomItem();
	pItem->Construct(Tizen::Graphics::Dimension(itemWidth, 112), style);
	Rectangle mainListItemRect(26, 32, GetClientAreaBounds().width, 50);

	switch(index)
	{
	  case 0:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"Animation", true);
	      break;
	  case 1:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"Button", true);
	      break;
	  case 2:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"CheckButton", true);
	      break;
	  case 3:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"ColorPicker", true);
	      break;
	  case 4:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"ContextMenu", true);
	      break;
	  case 5:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"CustomButton", true);
	      break;
	  case 6:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"EditDate, EditTime", true);
	      break;
	  case 7:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"EditField, EditArea", true);
	      break;
	  case 8:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"ExpandableEditArea", true);
	      break;
	  case 9:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"EnrichedText", true);
	      break;
	  case 10:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"Gallery", true);
	      break;
	  case 11:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"GroupedListView", true);
	      break;
	  case 12:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"Header,  Footer", true);
	      break;
	  case 13:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"IconListView", true);
	      break;
	  case 14:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"ListView", true);
	      break;
	  case 15:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"MessageBox, Popup", true);
	      break;
	  case 16:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"OverlayKeypad", true);
	      break;
	  case 17:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"Progress", true);
	      break;
	  case 18:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"ScrollPanel, Panel", true);
	      break;
	  case 19:
		 pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"SearchBar", true);
		 break;
	  case 20:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"Slider", true);
	      break;
	  case 21:
		pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"SplitPanel", true);
		break;
	  case 22:
		 pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"TabBar", true);
		 break;
	  case 23:
		 pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"TableView", true);
		 break;
	  case 24:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"TextBox", true);
	      break;
	  case 25:
	      pItem->AddElement(mainListItemRect, ID_FORMAT_STRING, L"QuickPanelFrame", true);
	      break;
	  default:
		  break;
	}
	return pItem;
}

void
MainForm::OnFormBackRequested(Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}
