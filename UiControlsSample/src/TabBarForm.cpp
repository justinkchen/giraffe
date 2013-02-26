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
#include "TabBarForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Media;

const int ITEM_COUNT = 14;

TabBarForm::TabBarForm(void)
	: __pTabBar(null)
	, __pheaderLeftItemBitmap(null)
	, __pLeftItemBitmap(null)
	, __pRightItemBitmap(null)
	, __pLogLabel(null)
	, __headerTypeIndex(0)
	, __footerTypeIndex(0)
	, __startY(0)
	, __isTranslucent(false)
	, __isVisible(true)
	, __isOpened(false)
	, __isAdded(false)
{
}
TabBarForm::~TabBarForm(void)
{
}

result
TabBarForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	delete __pLeftItemBitmap;
	delete __pRightItemBitmap;
	return r;
}
bool
TabBarForm::Initialize(void)
{
	Form::Construct(L"IDF_FORM_TABBAR");
	return true;
}

result
TabBarForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

    __pTabBar = static_cast<TabBar *>(GetControl("IDC_TABBAR"));

	 TabBarItem tabBarItem1;
	 TabBarItem tabBarItem2;
	 TabBarItem tabBarItem3;
	 TabBarItem tabBarItem4;
	 TabBarItem tabBarItem5;

	 tabBarItem1.Construct(L"1", ID_TABBAR_ITEM1);
	 tabBarItem2.Construct(L"2", ID_TABBAR_ITEM2);
	 tabBarItem3.Construct(L"3", ID_TABBAR_ITEM3);
	 tabBarItem4.Construct(L"4", ID_TABBAR_ITEM4);
	 tabBarItem5.Construct(L"5", ID_TABBAR_ITEM5);

	__pTabBar->AddItem(tabBarItem1);
	__pTabBar->AddItem(tabBarItem2);
	__pTabBar->AddItem(tabBarItem3);
	__pTabBar->AddItem(tabBarItem4);
	__pTabBar->AddItem(tabBarItem5);
	__pTabBar->AddActionEventListener(*this);
	AddControl(*__pTabBar);

	return r;
}
void
TabBarForm::SetFooterStyle(int footerType)
{

}
bool
TabBarForm::CreateMainList(void)
{
	return true;
}

void
TabBarForm::SetHeaderStyle(int headerType)
{

}
void
TabBarForm::AlignControls()
{
	int indent = 0;
	Rectangle rc = GetClientAreaBounds();

	if(__isTranslucent == true && __isVisible == true)
	{
		indent = __startY;
		if (GetHeader()->GetStyle() == HEADER_STYLE_SEGMENTED_WITH_TITLE && GetHeader()->IsVisible() == true)
		{
			indent += 16;
		}
	}
	else
	{
		indent = 0;
	}

	__pTabBar->SetPosition(0, indent);

}

void
TabBarForm::OnActionPerformed(const Control& source, int actionId)
{

}

void
TabBarForm::OnListViewContextItemStateChanged(ListView& listView, int index, int elementId, ListContextItemStatus status)
{
	// TODO: Add your implementation codes here

}

void
TabBarForm::OnListViewItemLongPressed(ListView& listView, int index, int elementId, bool& invokeListViewItemCallback)
{
	// TODO: Add your implementation codes here

}

void
TabBarForm::OnListViewItemStateChanged(ListView& listView, int index, int elementId, ListItemStatus status)
{

}

void
TabBarForm::OnListViewItemSwept(ListView& listView, int index, SweepDirection direction)
{

}
