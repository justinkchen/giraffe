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
#include "SplitPanelForm.h"
#include <FLocales.h>
#include <FSystem.h>

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::System;

const Color FIRST_BLACKGROUND_COLOR = Color(200, 75, 76, 255);
const Color SECOND_BLACKGROUND_COLOR = Color(212, 209, 204, 255);

SplitPanelForm::SplitPanelForm(void)
	: __pButtonForMaximizingSecondPane(null)
	, __pButtonForRestoringPanes(null)
	, __pSplitPanel(null)
	, __pFirstPane(null)
	, __pSecondPane(null)
{
}

SplitPanelForm::~SplitPanelForm(void)
{
}

bool
SplitPanelForm::Initialize(void)
{
	Construct(L"IDF_FORM_SPLITPANEL");

	return true;
}

result
SplitPanelForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

//create splitpanel
	__pSplitPanel = static_cast <SplitPanel*> (GetControl(L"IDC_SPLITPANEL"));
    AddControl(*__pSplitPanel);
	__pSplitPanel->AddSplitPanelEventListener(*this);

//create firstpane with listview
	__pFirstPane = static_cast <ListView*> (__pSplitPanel->GetPane(SPLIT_PANEL_PANE_ORDER_FIRST));
	__pFirstPane->SetItemProvider(*this);
	__pFirstPane->AddListViewItemEventListener(*this);
	__pSplitPanel->SetDividerPosition(300);
	__pFirstPane->SetBackgroundColor(FIRST_BLACKGROUND_COLOR);

//create second pane with panel
	__pSecondPane = static_cast <Panel*> (__pSplitPanel->GetPane(SPLIT_PANEL_PANE_ORDER_SECOND));
	__pSecondPane->SetBackgroundColor(SECOND_BLACKGROUND_COLOR);

//create label
	__pLabel = new (std::nothrow) Label();
	__pLabel->Construct(Rectangle(75, 15, 270, 120), L"");
	__pSecondPane->AddControl(*__pLabel);

//create button for maximizing second pane
	__pButtonForMaximizingSecondPane = new (std::nothrow) Button();
	__pButtonForMaximizingSecondPane->Construct(Rectangle(75, 150, 270, 120));
	__pButtonForMaximizingSecondPane->SetText(L"Maximize second pane");
	__pButtonForMaximizingSecondPane->SetActionId(ID_BUTTON_SECOND_MAXIMIZE);
	__pButtonForMaximizingSecondPane->AddActionEventListener(*this);
	__pSecondPane->AddControl(*__pButtonForMaximizingSecondPane);

//create button for restoring
	__pButtonForRestoringPanes = new (std::nothrow) Button();
	__pButtonForRestoringPanes->Construct(Rectangle(75, 300, 270, 120));
	__pButtonForRestoringPanes->SetText(L"Restore pane");
	__pButtonForRestoringPanes->SetActionId(ID_BUTTON_RESTORE);
	__pButtonForRestoringPanes->AddActionEventListener(*this);
	__pSecondPane->AddControl(*__pButtonForRestoringPanes);

//rotate
//	SetOrientation(ORIENTATION_AUTOMATIC);

	SetOrientation(ORIENTATION_LANDSCAPE);
	AddOrientationEventListener(*this);

	Invalidate(true);
	return r;
}

void
SplitPanelForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId) {

	case ID_BUTTON_SECOND_MAXIMIZE:
		__pSplitPanel->MaximizePane(SPLIT_PANEL_PANE_ORDER_SECOND);
		break;

	case ID_BUTTON_RESTORE:
		__pSplitPanel->RestorePane();
		break;
	default:
		break;
	}
	Invalidate(true);
}

void
SplitPanelForm::OnOrientationChanged(const Control &source, OrientationStatus orientationStatus)
{
	Rectangle clientRect = GetClientAreaBounds();
	__pSplitPanel->SetBounds(Rectangle(0, 0, clientRect.width, clientRect.height));

	if (orientationStatus == ORIENTATION_STATUS_PORTRAIT)
	{
		__pSplitPanel->MaximizePane(SPLIT_PANEL_PANE_ORDER_SECOND);
	}
	else
	{
		__pSplitPanel->RestorePane();
	}
	Invalidate(true);
}

int
SplitPanelForm::GetItemCount(void)
{
	return 3;
}

ListItemBase*
SplitPanelForm::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem* pItem = new (std::nothrow) CustomItem();
	itemWidth = GetClientAreaBounds().width;
	pItem->Construct(Tizen::Graphics::Dimension(itemWidth, 112), style);

	switch(index)
	{

	  case 0:
	      pItem->AddElement(Rectangle(0, 0, itemWidth, 100), ID_FORMAT_ROTATE, L"  Rotate", 44, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLACK), false);
	      break;
	  case 1:
	      pItem->AddElement(Rectangle(0, 0, itemWidth, 100), ID_FORMAT_MAXIMIZE, L"  Maximize first pane", 44, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLACK), false);
	      break;
	  case 2:
	      pItem->AddElement(Rectangle(0, 0, itemWidth, 100), ID_FORMAT_RESTORE, L"  Restore", 44, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLACK), false);
	      break;
	  default:
		  break;
	}
  	return pItem;
}

void
SplitPanelForm::OnListViewItemStateChanged(ListView& listView, int index, int elementId, ListItemStatus status)
{
	String itemText(L"");

	switch(elementId)
	{
	case ID_FORMAT_ROTATE:
		itemText = L"Rotate";
		if (GetOrientation() == ORIENTATION_LANDSCAPE)
		{
			SetOrientation(ORIENTATION_PORTRAIT);
		}
		else
		{
			SetOrientation(ORIENTATION_LANDSCAPE);
		}
		break;
	case ID_FORMAT_MAXIMIZE:
		itemText = L"Maximize First Pane";
		__pSplitPanel->MaximizePane(SPLIT_PANEL_PANE_ORDER_FIRST);
		break;
	case ID_FORMAT_RESTORE:
		itemText = L"Restore";
		__pSplitPanel->RestorePane();
		break;
	}
	__pLabel->SetText(itemText);
	Invalidate(true);
}

void
SplitPanelForm::OnListViewItemSwept(ListView& listView, int index, SweepDirection direction)
{
}

void
SplitPanelForm::OnListViewContextItemStateChanged(ListView& listView, int index, int elementId, ListContextItemStatus state)
{
}

void
SplitPanelForm::OnItemReordered(ListView& view, int oldIndex, int newIndex)
{
}

bool
SplitPanelForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}

void
SplitPanelForm::OnDividerPositionChanged(SplitPanel& source, int position)
{

}

void
SplitPanelForm::OnDividerDoublePressed(SplitPanel& source)
{

}

