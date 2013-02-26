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
#include "IconListViewForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Media;
using namespace Tizen::App;

const wchar_t LIST_IMAGE_PATH1[] = L"home_type3.png";
const wchar_t LIST_IMAGE_PATH2[] = L"message_type3.png";
const wchar_t LIST_IMAGE_PATH3[] = L"alarm_type3.png";
const wchar_t LIST_IMAGE_PATH4[] = L"00_icon_more_ef.png";
const int ITEM_COUNT = 200;


IconListViewForm::IconListViewForm(void)
	: __pLabelLog(null)
	, __pHome(null)
	, __pMsg(null)
	, __pAlarm(null)
	, __pMore(null)
{
}

IconListViewForm::~IconListViewForm(void)
{
}

bool
IconListViewForm::Initialize(void)
{
	Construct(L"IDF_FORM_ICONLISTVIEW");
	return true;
}

result
IconListViewForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	FooterItem  footerItem1;
	footerItem1.Construct(ID_FOOTER_VERTICAL);
	footerItem1.SetText(L"Vertical");

	FooterItem  footerItem2;
	footerItem2.Construct(ID_FOOTER_HORIZONTAL);
	footerItem2.SetText(L"Horizontal");

	Footer* pFooter = GetFooter();
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_ICON_TEXT);
	pFooter->SetBackButton();
	pFooter->AddItem(footerItem1);
	pFooter->AddItem(footerItem2);

	pFooter->AddActionEventListener(*this);

	GetBitmap();
	CreateIconListView();

	return r;
}

result
IconListViewForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	// Deallocate bitmaps
	delete __pHome;
	delete __pMsg;
	delete __pAlarm;
	delete __pMore;
	return r;
}

void
IconListViewForm::GetBitmap(void)
{
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();

	__pHome = pAppResource->GetBitmapN(LIST_IMAGE_PATH1);
	__pMsg = pAppResource->GetBitmapN(LIST_IMAGE_PATH2);
	__pAlarm = pAppResource->GetBitmapN(LIST_IMAGE_PATH3);
	__pMore = pAppResource->GetBitmapN(LIST_IMAGE_PATH4);

}

void
IconListViewForm::CreateIconListView(void)
{
	Rectangle clientArea = this->GetClientAreaBounds();
	Dimension itemSize;
	clientArea.x = clientArea.y = 0;
	__pVerticalIconList = static_cast <IconListView*> (GetControl(L"IDC_ICONLISTVIEW_VERTICAL"));
	__pVerticalIconList->SetItemBorderStyle(ICON_LIST_VIEW_ITEM_BORDER_STYLE_OUTLINE);
	__pVerticalIconList->SetItemProvider(*this);
	__pVerticalIconList->AddIconListViewItemEventListener(*this);
	AddControl(*__pVerticalIconList);

	__pHorizontalIconList = static_cast <IconListView*> (GetControl(L"IDC_ICONLISTVIEW_HORIZONTAL"));
	__pHorizontalIconList->SetItemBorderStyle(ICON_LIST_VIEW_ITEM_BORDER_STYLE_OUTLINE);
	__pHorizontalIconList->SetItemProvider(*this);
	__pHorizontalIconList->AddIconListViewItemEventListener(*this);
	AddControl(*__pHorizontalIconList);

	__pVerticalIconList->SetShowState(true);
	__pHorizontalIconList->SetShowState(false);
}

void
IconListViewForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_FOOTER_HORIZONTAL:
	{
		__pVerticalIconList->SetShowState(false);
		__pHorizontalIconList->SetShowState(true);
	}
		break;
	case ID_FOOTER_VERTICAL:
	{
		__pVerticalIconList->SetShowState(true);
		__pHorizontalIconList->SetShowState(false);
	}
		break;
	default :
		break;
	}
	Invalidate(true);
}

int
IconListViewForm::GetItemCount(void)
{
	return ITEM_COUNT;
}

IconListViewItem*
IconListViewForm::CreateItem(int index)
{
	String itemText(L"");
	IconListViewItem* pIconListview = new (std::nothrow) IconListViewItem();
	switch (index % 3)
	{
	case 0:
		itemText = L"Home";
		pIconListview->Construct(*__pHome, &itemText);
		break;
	case 1:
		itemText = L"Msg";
		pIconListview->Construct(*__pMsg, &itemText);
		break;
	case 2:
		itemText = L"Call";
		pIconListview->Construct(*__pAlarm, &itemText);
		break;
	}
	return pIconListview;
}

bool
IconListViewForm::DeleteItem(int index, IconListViewItem* pItem)
{
	delete pItem;
	return true;
}

void
IconListViewForm::OnIconListViewItemStateChanged(IconListView& view, int index, IconListViewItemStatus status)
{
	String itemText(L"");
	itemText.Format(20, L"Item %d Selected", index + 1);
}


