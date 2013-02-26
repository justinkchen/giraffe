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
#include "NavigationForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Media;
using namespace Tizen::Ui::Scenes;

const int ITEM_COUNT = 15;

NavigationForm::NavigationForm(void)
	: __pTabBar(null)
	, __pheaderLeftItemBitmap(null)
	, __pLeftItemBitmap(null)
	, __pRightItemBitmap(null)
	, __pLogLabel(null)
	, __pList(null)
	, __headerTypeIndex(0)
	, __footerTypeIndex(0)
	, __startY(0)
	, __isTranslucent(false)
	, __isVisible(true)
	, __isOpened(false)
{
}
NavigationForm::~NavigationForm(void)
{
}

result
NavigationForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	delete __pLeftItemBitmap;
	delete __pRightItemBitmap;
	delete __pheaderLeftItemBitmap;
	return r;
}
bool
NavigationForm::Initialize(void)
{
	Form::Construct(L"IDF_FORM_NAVIGATION");
	return true;
}

result
NavigationForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	pHeader->AddActionEventListener(*this);

	Footer* pFooter = GetFooter();
	pFooter->AddActionEventListener(*this);

 	AppResource* pAppResource = Application::GetInstance()->GetAppResource();

 	__pheaderLeftItemBitmap = pAppResource->GetBitmapN(L"alarm_type1.png");
	__pRightItemBitmap = pAppResource->GetBitmapN(L"message_type2.png");
	__pLeftItemBitmap = pAppResource->GetBitmapN(L"alarm_type2.png");

	  Rectangle rc = GetClientAreaBounds();
	if (!CreateMainList())
	{
		return false;
	}

    __startY = rc.y;

    SetHeaderStyle(HEADER_STYLE_0);
    SetFooterStyle(FOOTER_STYLE_0);

	return r;
}
void
NavigationForm::SetFooterStyle(int footerType)
{
	Footer* pFooter = GetFooter();
	pFooter->RemoveAllItems();
	pFooter->RemoveAllButtons();

	switch (footerType)
	{
		case FOOTER_STYLE_0:
		{
			FooterItem  footerItem1;
			footerItem1.Construct(ID_FOOTER_ITEM1);
			footerItem1.SetText(L"1");

			FooterItem  footerItem2;
			footerItem2.Construct(ID_FOOTER_ITEM2);
			footerItem2.SetText(L"2");

			pFooter->SetStyle(FOOTER_STYLE_SEGMENTED_TEXT);
			pFooter->AddItem(footerItem1);
			pFooter->AddItem(footerItem2);
			pFooter->SetBackButton ();
		}
		break;
		case FOOTER_STYLE_1:
		{
			FooterItem  footerItem1;
			footerItem1.Construct(ID_FOOTER_ITEM1);
			footerItem1.SetText(L"1");

			FooterItem  footerItem2;
			footerItem2.Construct(ID_FOOTER_ITEM2);
			footerItem2.SetText(L"2");

			ButtonItem  buttonItem;
			buttonItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_FOOTER_LEFTBUTTON);
			buttonItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, __pLeftItemBitmap);

			pFooter->SetStyle(FOOTER_STYLE_SEGMENTED_TEXT);
			pFooter->SetButton(BUTTON_POSITION_LEFT, buttonItem);
			pFooter->AddItem(footerItem1);
			pFooter->AddItem(footerItem2);
		}
		break;
		case FOOTER_STYLE_2:
		{
			FooterItem  footerItem1;
			footerItem1.Construct(ID_FOOTER_ITEM1);
			footerItem1.SetText(L"1");

			FooterItem  footerItem2;
			footerItem2.Construct(ID_FOOTER_ITEM2);
			footerItem2.SetText(L"2");

			FooterItem  footerItem3;
			footerItem3.Construct(ID_FOOTER_ITEM3);
			footerItem3.SetText(L"3");

			FooterItem  footerItem4;
			footerItem4.Construct(ID_FOOTER_ITEM4);
			footerItem4.SetText(L"4");

			FooterItem  footerItem5;
			footerItem5.Construct(ID_FOOTER_ITEM5);
			footerItem5.SetText(L"5");

			FooterItem  footerItem6;
			footerItem6.Construct(ID_FOOTER_ITEM6);
			footerItem6.SetText(L"6");

			FooterItem  footerItem7;
			footerItem7.Construct(ID_FOOTER_ITEM7);
			footerItem7.SetText(L"7");

			pFooter->SetStyle(FOOTER_STYLE_TAB);
			pFooter->AddItem(footerItem1);
			pFooter->AddItem(footerItem2);
			pFooter->AddItem(footerItem3);
			pFooter->AddItem(footerItem4);
			pFooter->AddItem(footerItem5);
			pFooter->AddItem(footerItem6);
			pFooter->AddItem(footerItem7);
		}
		break;
		case FOOTER_STYLE_3:
		{
			FooterItem  footerItem1;
			footerItem1.Construct(ID_FOOTER_ITEM1);
			footerItem1.SetText(L"Button 1");

			FooterItem  footerItem2;
			footerItem2.Construct(ID_FOOTER_ITEM2);
			footerItem2.SetText(L"Button 2");

			pFooter->SetStyle(FOOTER_STYLE_BUTTON_ICON_TEXT);
			pFooter->SetBackButton();
			pFooter->AddItem(footerItem1);
			pFooter->AddItem(footerItem2);
		}
		break;
	}
}
bool
NavigationForm::CreateMainList(void)
{
	__pList = static_cast <ListView*> (GetControl("IDC_LISTVIEW"));
	__pList->SetItemProvider(*this);
	__pList->AddListViewItemEventListener(*this);
	return true;
}

void
NavigationForm::SetHeaderStyle(int headerType)
{
	Header* pHeader = GetHeader();
	pHeader->RemoveAllButtons();
	pHeader->RemoveAllItems();

	switch (headerType)
	{
		case HEADER_STYLE_0:
		{
			HeaderItem headerLeftItem;
			headerLeftItem.Construct(ID_HEADER_LEFTITEM);
			headerLeftItem.SetText(L"LEFT");

			HeaderItem headerCenterItem;
			headerCenterItem.Construct(ID_HEADER_CENTERITEM);
			headerCenterItem.SetText(L"CENTER");

			HeaderItem headerRightItem;
			headerRightItem.Construct(ID_HEADER_RIGHTITEM);
			headerRightItem.SetText(L"RIGHT");

			pHeader->SetStyle(HEADER_STYLE_SEGMENTED);
			pHeader->AddItem(headerLeftItem);
			pHeader->AddItem(headerCenterItem);
			pHeader->AddItem(headerRightItem);
		}
		break;
		case HEADER_STYLE_1:
		{
			ButtonItem  buttonLeftItem;
			buttonLeftItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_LEFTBUTTON);
			buttonLeftItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, __pLeftItemBitmap);

			ButtonItem  buttonRightItem;
			buttonRightItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_RIGHTBUTTON);
			buttonRightItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, __pRightItemBitmap);

			pHeader->SetStyle(HEADER_STYLE_TITLE);
			pHeader->SetTitleText(L"TITLE");
			pHeader->SetButton(BUTTON_POSITION_LEFT, buttonLeftItem);
			pHeader->SetButton(BUTTON_POSITION_RIGHT, buttonRightItem);
		}
		break;
		case HEADER_STYLE_2:
		{
			ButtonItem  buttonLeftItem;
			buttonLeftItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_LEFTBUTTON);
			buttonLeftItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, __pLeftItemBitmap);

			ButtonItem  buttonRightItem;
			buttonRightItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_RIGHTBUTTON);
			buttonRightItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, __pRightItemBitmap);

			pHeader->SetStyle(HEADER_STYLE_TITLE);
			pHeader->SetTitleText(L"TITLE");
			pHeader->SetDescriptionText(L"description text");
			pHeader->SetButton(BUTTON_POSITION_LEFT, buttonLeftItem);
			pHeader->SetButton(BUTTON_POSITION_RIGHT, buttonRightItem);
		}
		break;
		case HEADER_STYLE_3:
		{
			ButtonItem buttonLeftItem;
			buttonLeftItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_LEFTBUTTON);
			buttonLeftItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, __pLeftItemBitmap);

			ButtonItem  buttonRightItem;
			buttonRightItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_RIGHTBUTTON);
			buttonRightItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, __pRightItemBitmap);

			HeaderItem headerLeftItem;
			headerLeftItem.Construct(ID_HEADER_LEFTITEM);
			headerLeftItem.SetText(L"LEFT");

			HeaderItem headerRightItem;
			headerRightItem.Construct(ID_HEADER_RIGHTITEM);
			headerRightItem.SetText(L"RIGHT");

			pHeader->SetStyle(HEADER_STYLE_SEGMENTED);
			pHeader->AddItem(headerLeftItem);
			pHeader->AddItem(headerRightItem);
			pHeader->SetButton(BUTTON_POSITION_LEFT, buttonLeftItem);
			pHeader->SetButton(BUTTON_POSITION_RIGHT, buttonRightItem);
		}
		break;
		case HEADER_STYLE_4:
		{
			HeaderItem  headerItem1;
			headerItem1.Construct(ID_HEADER_ITEM1);
			headerItem1.SetText(L"1");

			HeaderItem  headerItem2;
			headerItem2.Construct(ID_HEADER_ITEM2);
			headerItem2.SetText(L"2");

			HeaderItem  headerItem3;
			headerItem3.Construct(ID_HEADER_ITEM3);
			headerItem3.SetText(L"3");

			HeaderItem  headerItem4;
			headerItem4.Construct(ID_HEADER_ITEM4);
			headerItem4.SetText(L"4");

			HeaderItem  headerItem5;
			headerItem5.Construct(ID_HEADER_ITEM5);
			headerItem5.SetText(L"5");

			HeaderItem  headerItem6;
			headerItem6.Construct(ID_HEADER_ITEM6);
			headerItem6.SetText(L"6");

			HeaderItem  headerItem7;
			headerItem7.Construct(ID_HEADER_ITEM7);
			headerItem7.SetText(L"7");

			pHeader->SetStyle(HEADER_STYLE_TAB);
			pHeader->AddItem(headerItem1);
			pHeader->AddItem(headerItem2);
			pHeader->AddItem(headerItem3);
			pHeader->AddItem(headerItem4);
			pHeader->AddItem(headerItem5);
			pHeader->AddItem(headerItem6);
			pHeader->AddItem(headerItem7);
		}
		break;
		case HEADER_STYLE_5:
		{
			HeaderItem headerLeftItem;
			headerLeftItem.Construct(ID_HEADER_LEFTITEM);
			headerLeftItem.SetText(L"LEFT");

			HeaderItem headerRightItem;
			headerRightItem.Construct(ID_HEADER_RIGHTITEM);
			headerRightItem.SetText(L"RIGHT");

			pHeader->SetStyle(HEADER_STYLE_SEGMENTED_WITH_TITLE);
			pHeader->SetTitleText(L"TITLE");
			pHeader->AddItem(headerLeftItem);
			pHeader->AddItem(headerRightItem);
		}
		break;
	}
}

void
NavigationForm::OnActionPerformed(const Control& source, int actionId)
{

}

void
NavigationForm::OnListViewContextItemStateChanged(ListView& listView, int index, int elementId, ListContextItemStatus status)
{
	// TODO: Add your implementation codes here

}

void
NavigationForm::OnListViewItemLongPressed(ListView& listView, int index, int elementId, bool& invokeListViewItemCallback)
{
	// TODO: Add your implementation codes here

}

void
NavigationForm::OnListViewItemStateChanged(ListView& listView, int index, int elementId, ListItemStatus status)
{
	// TODO: Add your implementation codes here
	switch (index)
	{
	case 0:
	{
		__headerTypeIndex = 0;
		SetHeaderStyle(__headerTypeIndex);
		break;
	}
	case 1:
	{
		__headerTypeIndex = 1;
		SetHeaderStyle(__headerTypeIndex);
		break;
	}
	case 2:
	{
		__headerTypeIndex = 2;
		SetHeaderStyle(__headerTypeIndex);
		break;
	}
	case 3:
	{
		__headerTypeIndex = 3;
		SetHeaderStyle(__headerTypeIndex);
		break;
	}
	case 4:
	{
		__headerTypeIndex = 4;
		SetHeaderStyle(__headerTypeIndex);
		break;
	}
	case 5:
	{
		__headerTypeIndex = 5;
		SetHeaderStyle(__headerTypeIndex);
		break;
	}
	case 6:
	{
		__footerTypeIndex = 0;
		SetFooterStyle(__footerTypeIndex);
		break;
	}
	case 7:
	{
		__footerTypeIndex = 1;
		SetFooterStyle(__footerTypeIndex);
		break;
	}
	case 8:
	{
		__footerTypeIndex = 3;
		SetFooterStyle(__footerTypeIndex);
		break;
	}
	case 9:
	{
		__footerTypeIndex = 2;
		SetFooterStyle(__footerTypeIndex);
		break;
	}
	case 10:
	{
		result r = SetActionBarsTranslucent(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, false);
		if (r == E_SUCCESS)
		{
			__isTranslucent = false;
		}
		else if (r == E_UNSUPPORTED_OPERATION)
		{
		}
	}
	break;
	case 11:
	{
		result r = SetActionBarsTranslucent(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, true);
		if (r==E_UNSUPPORTED_OPERATION)
		{
		}
	}
	break;
	case 12:
	{
		SetActionBarsVisible(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, false);
		__isVisible = false;
	}
	break;
	case 13:
	{
		SetActionBarsVisible(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, true);
		__isVisible = true;
	}
	break;
	case 14:
	{
		SceneManager* pSceneManager = SceneManager::GetInstance();
		AppAssert(pSceneManager);
		pSceneManager->GoBackward(BackwardSceneTransition());
		break;
	}
	default:
		break;
	}
	Invalidate(true);
}

void
NavigationForm::OnListViewItemSwept(ListView& listView, int index, SweepDirection direction)
{
	// TODO: Add your implementation codes here

}
int
NavigationForm::GetItemCount(void)
{
	return ITEM_COUNT;
}
ListItemBase*
NavigationForm::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem* pItem = new (std::nothrow) CustomItem();
	pItem->Construct(Tizen::Graphics::Dimension(itemWidth, 112), style);
	Rectangle mainListItemRect(26, 32, GetClientAreaBounds().width, 50);

	switch(index)
	{
	  case 0:
	      pItem->AddElement(mainListItemRect, ID_HEADER_STYLE, L"Header Style Segment", true);
	      break;
	  case 1:
	      pItem->AddElement(mainListItemRect, ID_HEADER_STYLE, L"Header Style Title With Icon", true);
	      break;
	  case 2:
	      pItem->AddElement(mainListItemRect, ID_HEADER_STYLE, L"Header Style Title With Description", true);
	      break;
	  case 3:
	      pItem->AddElement(mainListItemRect, ID_HEADER_STYLE, L"Header Style Segment With Icon", true);
	      break;
	  case 4:
	      pItem->AddElement(mainListItemRect, ID_HEADER_STYLE, L"Header Style Tab", true);
	      break;
	  case 5:
	      pItem->AddElement(mainListItemRect, ID_HEADER_STYLE, L"Header Style Segment with Title", true);
	      break;
	  case 6:
	      pItem->AddElement(mainListItemRect, ID_FOOTER_STYLE, L"Footer Style Segment Text", true);
	      break;
	  case 7:
		  pItem->AddElement(mainListItemRect, ID_FOOTER_STYLE, L"Footer Style Segment Text, Icon", true);
		  break;
	  case 8:
		  pItem->AddElement(mainListItemRect, ID_FOOTER_STYLE, L"Footer Style Button Text", true);
		  break;
	  case 9:
		  pItem->AddElement(mainListItemRect, ID_FOOTER_STYLE, L"Footer Style Tab", true);
		  break;
	  case 10:
	      pItem->AddElement(mainListItemRect, ID_TRANSLUCENT, L"Translucent Off", true);
	      break;
	  case 11:
	      pItem->AddElement(mainListItemRect, ID_TRANSLUCENT, L"Translucent On", true);
	      break;
	  case 12:
	      pItem->AddElement(mainListItemRect, ID_VISIBLE, L"Visible Off", true);
	      break;
	  case 13:
	      pItem->AddElement(mainListItemRect, ID_VISIBLE, L"Visible On", true);
	      break;
	  case 14:
	      pItem->AddElement(mainListItemRect, ID_EXIT, L"Back", true);
	      break;
	default:
		break;
	}
	return pItem;
}

bool
NavigationForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}
