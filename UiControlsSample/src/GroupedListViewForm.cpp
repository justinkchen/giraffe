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
#include "GroupedListViewForm.h"

using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Media;

const wchar_t LIST_IMAGE_PATH1[] = L"home_type3.png";
const wchar_t LIST_IMAGE_PATH2[] = L"message_type3.png";
const wchar_t LIST_IMAGE_PATH3[] = L"alarm_type3.png";
const wchar_t LIST_IMAGE_PATH4[] = L"call_type3.png";

const int GROUP_INDEX0 = 0;
const int GROUP_INDEX1 = 1;
const int GROUP_INDEX2 = 2;

GroupedListViewForm::GroupedListViewForm(void)
	: __pList(null)
	, __pHome(null)
	, __pMsg(null)
	, __pAlarm(null)
	, __pCall(null)
	, __pCustomGroupedListElement(null)
	, __pItemContext(null)
{
}

GroupedListViewForm::~GroupedListViewForm(void)
{
}

bool
GroupedListViewForm::Initialize(void)
{
	Construct(L"IDF_FORM_GROUPEDLISTVIEW");
	return true;
}

result
GroupedListViewForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	GetBitmap();
	CreateGroupedListView();

	// Create Custom Element
	__pCustomGroupedListElement = new (std::nothrow) CustomGroupedListElement();

	__pItemContext = new (std::nothrow) ListContextItem();
	__pItemContext->Construct();
	__pItemContext->AddElement(ID_CONTEXT_ITEM_1, L"Button 1");
	__pItemContext->AddElement(ID_CONTEXT_ITEM_2, L"Button 2");

	return r;
}

result
GroupedListViewForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// Deallocate bitmaps
	delete __pHome;
	delete __pMsg;
	delete __pAlarm;
	delete __pCall;
	delete __pItemContext;
	delete __pCustomGroupedListElement;

	return r;
}

void
GroupedListViewForm::GetBitmap(void)
{
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	__pHome = pAppResource->GetBitmapN(LIST_IMAGE_PATH1);
	__pMsg = pAppResource->GetBitmapN(LIST_IMAGE_PATH2);
	__pAlarm = pAppResource->GetBitmapN(LIST_IMAGE_PATH3);
	__pCall = pAppResource->GetBitmapN(LIST_IMAGE_PATH4);
}

void
GroupedListViewForm::CreateGroupedListView(void)
{
	__pList = static_cast <GroupedListView*> (GetControl(L"IDC_GROUPEDLISTVIEW"));
	__pList->SetItemProvider(*this);
	__pList->SetFastScrollIndex(L"ABC", false);
	__pList->AddFastScrollListener(*this);
	__pList->AddGroupedListViewItemEventListener(*this);
	AddControl(*__pList);
}

void
GroupedListViewForm::OnFastScrollIndexSelected(Control& source, Tizen::Base::String& index)
{
	if( !index.CompareTo(L"A" ))
	{
		__pList->ScrollToItem(GROUP_INDEX0, -1);
	}
	else if( !index.CompareTo(L"B"))
	{
		__pList->ScrollToItem(GROUP_INDEX1, -1);
	}
	else
	{
		__pList->ScrollToItem(GROUP_INDEX2, -1);
	}

	Invalidate(true);
}

void
GroupedListViewForm::OnGroupedListViewItemStateChanged(GroupedListView& listView, int groupIndex, int itemIndex, int elementId, ListItemStatus state)
{
	String itemText(L"");
	switch(elementId)
	{
	case ID_FORMAT_STRING:
		itemText.Format(40, L"[Group %d Item %d]\nText Selected", groupIndex+1, itemIndex+1);
		break;
	case ID_FORMAT_BITMAP:
		itemText.Format(40, L"[Group %d Item %d]\nBitmap Selected", groupIndex+1, itemIndex+1);
		break;
	case ID_FORMAT_CUSTOM:
		itemText.Format(40, L"[Group %d Item %d]\nCustom Selected", groupIndex+1, itemIndex+1);
		break;
	case ID_FORMAT_NULL:
	itemText.Format(40, L"[Group %d Item %d]\nSelected", groupIndex+1, itemIndex+1);
		break;
	}

}

void
GroupedListViewForm::OnGroupedListViewContextItemStateChanged(GroupedListView& listView, int groupIndex, int itemIndex, int elementId, ListContextItemStatus state)
{
	String contextItem(L"");
	if (elementId  == ID_CONTEXT_ITEM_1)
	{
		contextItem.Format(40, L"ContextItem %d :\n(Test1) Selected", itemIndex+1);
	}
	else
	{
		contextItem.Format(40, L"ContextItem %d :\n(Test2) Selected", itemIndex+1);
	}

}

void
GroupedListViewForm::OnGroupedListViewItemSwept(GroupedListView& listView, int groupIndex,  int itemIndex, SweepDirection direction)
{
}

void
GroupedListViewForm::OnGroupedListViewItemLongPressed(GroupedListView& listView, int groupIndex, int itemIndex, int elementId, bool &  invokeListViewItemCallback  )
{
	String itemText(L"");
	switch(elementId)
	{
	case ID_FORMAT_STRING:
		itemText.Format(40, L"[Group %d Item %d]\nText Selected", groupIndex+1, itemIndex+1);
		break;
	case ID_FORMAT_BITMAP:
		itemText.Format(40, L"[Group %d Item %d]\nBitmap Selected", groupIndex+1, itemIndex+1);
		break;
	case ID_FORMAT_CUSTOM:
		itemText.Format(40, L"[Group %d Item %d]\nCustom Selected", groupIndex+1, itemIndex+1);
		break;
	case ID_FORMAT_NULL:
		itemText.Format(40, L"[Group %d Item %d]\nSelected", groupIndex+1, itemIndex+1);
		break;
	}

}

int
GroupedListViewForm::GetGroupCount(void)
{
	return 3;
}

int
GroupedListViewForm::GetItemCount(int groupIndex)
{
	int itemCount = 0;
	switch(groupIndex)
	{
	case GROUP_INDEX0:
		itemCount = 7;
		break;
	case GROUP_INDEX1:
		itemCount = 5;
		break;
	case GROUP_INDEX2:
		itemCount = 3;
		break;
	default:
		break;
	}
	return itemCount;
}

GroupItem*
GroupedListViewForm::CreateGroupItem(int groupIndex, int itemWidth)
{
	GroupItem* pItem = new (std::nothrow) GroupItem();
	pItem->Construct(Dimension(itemWidth, 48));
	String text(L"");
	switch (groupIndex)
	{
	case GROUP_INDEX0:
		text = L"GroupA";
		break;
	case GROUP_INDEX1:
		 text = L"GroupB";
		break;
	case GROUP_INDEX2:
		 text = L"GroupC";
		break;
	}
	pItem->SetElement(text, null);
	return pItem;
}

ListItemBase*
GroupedListViewForm::CreateItem(int groupIndex, int itemIndex, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem* pItem = new (std::nothrow) CustomItem();
	pItem->Construct(Tizen::Graphics::Dimension(itemWidth, 112), style);

	Rectangle firstElementRect(26, 27, 60, 60);
	Rectangle secondElementRect(150, 32, 150, 50);
	Rectangle customElementRect(360, 20, 180, 80);

	switch (itemIndex % 4)
	{
	case 0:
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pHome, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Home", true);
		break;
	case 1:
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pMsg, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Msg", true);
		break;
	case 2:
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pAlarm, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Alarm", true);
		break;
	case 3:
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pCall, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Call", true);
		break;
	default:
		break;
	}
	pItem->AddElement(customElementRect, ID_FORMAT_CUSTOM, *(static_cast<ICustomElement*>(__pCustomGroupedListElement)));
	pItem->SetContextItem(__pItemContext);

	return pItem;
}

bool
GroupedListViewForm::DeleteItem(int groupIndex, int itemIndex, Controls::ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}

bool
GroupedListViewForm::DeleteGroupItem(int groupIndex, Controls::GroupItem* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}
