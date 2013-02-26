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
#include "ListViewForm.h"

using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Media;

const wchar_t LIST_IMAGE_PATH1[] = L"home_type1.png";
const wchar_t LIST_IMAGE_PATH2[] = L"message_type1.png";
const wchar_t LIST_IMAGE_PATH3[] = L"alarm_type1.png";
const wchar_t LIST_IMAGE_PATH4[] = L"call_type1.png";

const int ITEM_COUNT = 100;

ListViewForm::ListViewForm(void)
	: __pList(null)
	, __pLabelLog(null)
	, __pHome(null)
	, __pMsg(null)
	, __pAlarm(null)
	, __pCall(null)
	, __pCustomListElement(null)
	, __pItemContext(null)
{
}

ListViewForm::~ListViewForm(void)
{
}

bool
ListViewForm::Initialize(void)
{
	Construct(L"IDF_FORM_LISTVIEW");
	return true;
}

result
ListViewForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;


	GetBitmap();
	CreateListView();

	// Create Custom Element
	__pCustomListElement = new (std::nothrow) CustomListElement();

	__pItemContext = new (std::nothrow) ListContextItem();
	__pItemContext->Construct();
	__pItemContext->AddElement(ID_CONTEXT_ITEM_1, L"Button 1");
	__pItemContext->AddElement(ID_CONTEXT_ITEM_2, L"Button 2");

	FooterItem footerItem1;
	footerItem1.Construct(ID_REORDER_ON);
	footerItem1.SetText(L"ReOrder On");

	FooterItem footerItem2;
	footerItem2.Construct(ID_REORDER_OFF);
	footerItem2.SetText(L"ReOrder Off");

	Footer* pFooter = GetFooter();
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);
	pFooter->SetBackButton();
	pFooter->AddItem(footerItem1);
	pFooter->AddItem(footerItem2);
	pFooter->AddActionEventListener(*this);

	return r;
}

result
ListViewForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// Deallocate bitmaps
	delete __pHome;
	delete __pMsg;
	delete __pAlarm;
	delete __pCall;
	delete __pItemContext;
	delete __pCustomListElement;
	return r;
}

void
ListViewForm::GetBitmap(void)
{
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	__pHome = pAppResource->GetBitmapN(LIST_IMAGE_PATH1);
	__pMsg = pAppResource->GetBitmapN(LIST_IMAGE_PATH2);
	__pAlarm = pAppResource->GetBitmapN(LIST_IMAGE_PATH3);
	__pCall = pAppResource->GetBitmapN(LIST_IMAGE_PATH4);

}

void
ListViewForm::CreateListView(void)
{
	__pList = new (std::nothrow) ListView();
	__pList->Construct(Rectangle(0, 0, 720, GetClientAreaBounds().height), true, false);
	__pList->SetItemProvider(*this);
	__pList->AddListViewItemEventListener(*this);

	AddControl(*__pList);
}

void
ListViewForm::OnListViewItemStateChanged(ListView& listView, int index, int elementId, ListItemStatus status)
{
	String itemText(L"");

	switch(elementId)
	{
	case ID_FORMAT_STRING:
		itemText.Format(40, L"Item %d: Text Selected", index+1);
		break;
	case ID_FORMAT_BITMAP:
		itemText.Format(40, L"Item %d: Bitmap Selected", index+1);
		break;
	case ID_FORMAT_CUSTOM:
		itemText.Format(40, L"Item %d: Custom Selected", index+1);
		break;
	case ID_FORMAT_NULL:
		itemText.Format(40, L"Item %d: Selected", index+1);
		break;
	}

}

void
ListViewForm::OnListViewItemSwept(ListView& listView, int index, SweepDirection direction)
{
}
void
ListViewForm::OnListViewContextItemStateChanged(ListView& listView, int index, int elementId, ListContextItemStatus state)
{
	String contextItem(L"");
	if (elementId == ID_CONTEXT_ITEM_1)
	{
		contextItem.Format(40, L"ContextItem %d :\n(Test1) Selected", index+1);
	}
	else
	{
		contextItem.Format(40, L"ContextItem %d :\n(Test2) Selected", index+1);
	}

}

void
ListViewForm::OnListViewItemLongPressed(ListView& listView, int index, int elementId, bool& invokeListViewItemCallback)
{

	String itemText(L"");

	switch(elementId)
	{
	case ID_FORMAT_STRING:
		itemText.Format(40, L"Item %d: Text Selected", index+1);
		break;
	case ID_FORMAT_BITMAP:
		itemText.Format(40, L"Item %d: Bitmap Selected", index+1);
		break;
	case ID_FORMAT_CUSTOM:
		itemText.Format(40, L"Item %d: Custom Selected", index+1);
		break;
	case ID_FORMAT_NULL:
		itemText.Format(40, L"Item %d: Selected", index+1);
		break;
	}

}

int
ListViewForm::GetItemCount(void)
{
	return ITEM_COUNT;
}

ListItemBase*
ListViewForm::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem* pItem = new (std::nothrow) CustomItem();
	Rectangle firstElementRect(26, 27, 60, 60);//(10, 20, 60, 60);
	Rectangle secondElementRect(96, 32, 150, 50);//(80, 25, 150, 50);
	Dimension itemDimension(itemWidth,112);
	Rectangle markStyleCustomElementRect(275, 20, 180, 80);
	Rectangle customElementRect(350, 20, 180, 80);

	switch (index % 5)
	{
	case 0:
		style = LIST_ANNEX_STYLE_NORMAL;
		pItem->Construct(itemDimension, style);
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pHome, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Home", true);
		break;
	case 1:
		style = LIST_ANNEX_STYLE_MARK;
		pItem->Construct(itemDimension, style);
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pMsg, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Msg", true);
		break;
	case 2:
		style = LIST_ANNEX_STYLE_ONOFF_SLIDING;
		pItem->Construct(itemDimension, style);
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pAlarm, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Alarm", true);
		break;
	case 3:
		style = LIST_ANNEX_STYLE_DETAILED;
		pItem->Construct(itemDimension, style);
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pCall, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Call", true);
		break;
	case 4:
		style = LIST_ANNEX_STYLE_RADIO;
		pItem->Construct(itemDimension, style);
		pItem->AddElement(firstElementRect, ID_FORMAT_BITMAP, *__pAlarm, null, null);
		pItem->AddElement(secondElementRect, ID_FORMAT_STRING, L"Alarm", true);
		break;
	default:
		break;
	}
	if (style == LIST_ANNEX_STYLE_MARK)
	{
		pItem->AddElement(markStyleCustomElementRect, ID_FORMAT_CUSTOM, *(static_cast<ICustomElement *>(__pCustomListElement)));
	}
	else
	{
		pItem->AddElement(customElementRect, ID_FORMAT_CUSTOM, *(static_cast<ICustomElement *>(__pCustomListElement)));
	}
	pItem->SetContextItem(__pItemContext);

	return pItem;
}

bool
ListViewForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}

void
ListViewForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_REORDER_ON:
		__pList->BeginReorderingMode();
		break;
	case ID_REORDER_OFF:
		__pList->EndReorderingMode();
		break;
	default:
		break;
	}
}


