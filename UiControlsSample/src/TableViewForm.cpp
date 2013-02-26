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
#include "TableViewForm.h"

using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Base;

const wchar_t VOLUME_MIN_BITMAP[] = L"00_volume_icon_min.png";
const wchar_t VOLUME_MAX_BITMAP[] = L"00_volume_icon_max.png";
const wchar_t VIBRATION_MIN_BITMAP[] = L"00_volume_icon_Vibrat_min.png";
const wchar_t VIBRATION_MAX_BITMAP[] = L"00_volume_icon_Vibrat_max.png";

const int GROUP_COUNT = 4;

TableViewForm::TableViewForm(void)
 	: __pList(null)
 	, __pItem(null)
 	, __pMinSoundBitmap(null)
 	, __pMaxSoundBitmap(null)
 	, __pMinVibrationBitmap(null)
 	, __pMaxVibrationBitmap(null)
{
}

TableViewForm::~TableViewForm(void)
{
}

bool
TableViewForm::Initialize(void)
{
	Construct(L"IDF_FORM_TABLEVIEW");
	return true;
}

result
TableViewForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	GetBitmap();
	CreateTableView();

	return r;
}

result
TableViewForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	delete __pMaxSoundBitmap;
	delete __pMinSoundBitmap;
	delete __pMinVibrationBitmap;
	delete __pMaxVibrationBitmap;
	delete __pItem;

	return r;
}

void
TableViewForm::GetBitmap(void)
{
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	__pMinSoundBitmap = pAppResource->GetBitmapN(VOLUME_MIN_BITMAP);
	__pMaxSoundBitmap = pAppResource->GetBitmapN(VOLUME_MAX_BITMAP);
	__pMinVibrationBitmap = pAppResource->GetBitmapN(VIBRATION_MIN_BITMAP);
	__pMaxVibrationBitmap = pAppResource->GetBitmapN(VIBRATION_MAX_BITMAP);

}

void
TableViewForm::CreateTableView(void)
{
	__pList = static_cast <GroupedTableView*> (GetControl("IDC_GROUPEDTABLEVIEW"));
	__pList->SetItemProvider(this);
	__pList->AddGroupedTableViewItemEventListener(*this);
	AddControl(*__pList);
}

int
TableViewForm::GetGroupCount(void)
{
	return GROUP_COUNT;
}

int
TableViewForm::GetItemCount(int groupIndex)
{
	int itemCount = 0;

	switch(groupIndex)
	{
	case ID_GROUP_INDEX_MAIN:
		itemCount = 2;
		break;
	case ID_GROUP_INDEX_VOLUME:
		itemCount = 4;
		break;
	case ID_GROUP_INDEX_VIBRATION:
		itemCount = 2;
		break;
	default:
		break;
	}

	return itemCount;
}

TableViewGroupItem*
TableViewForm::CreateGroupItem(int groupIndex, int itemWidth)
{
	TableViewGroupItem* pItem = new (std::nothrow) TableViewGroupItem();
	String text(L"");

	if (groupIndex == ID_GROUP_INDEX_MAIN)
	{
		pItem->Construct(Dimension(itemWidth, 10));
		return pItem;
	}

	pGroupNameLabel = new (std::nothrow) Label();

	int defaultGroupItemHeight = GetDefaultGroupItemHeight();

	switch (groupIndex)
	{
		case ID_GROUP_INDEX_VOLUME:
		{
			pItem->Construct(Dimension(itemWidth, defaultGroupItemHeight));
			text = L"Volume";
			pGroupNameLabel->Construct(Rectangle(0, 0, itemWidth, defaultGroupItemHeight), text);
		}
		break;
	case ID_GROUP_INDEX_VIBRATION:
		{
			pItem->Construct(Dimension(itemWidth, defaultGroupItemHeight));
			text = L"Vibration";
			pGroupNameLabel->Construct(Rectangle(0, 0, itemWidth, defaultGroupItemHeight), text);
		}
		break;
	case ID_GROUP_INDEX_INFORMATION:
		{
			pItem->Construct(Dimension(itemWidth, 170));
			text = "Adjust volume and intensity for sounds when dialing, using keypad, tapping the screen, pressing hardkeys,"
					" and locking and unlocking device";
			pGroupNameLabel->Construct(Rectangle(0, 0, itemWidth, 160), text);
		}
		break;
	}

	pGroupNameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pItem->AddControl(*pGroupNameLabel);
	return pItem;
}

bool
TableViewForm::DeleteGroupItem(int groupIndex, TableViewGroupItem* pItem)
{
	delete pItem;

	return true;
}

TableViewItem*
TableViewForm::CreateItem(int groupIndex, int itemIndex, int itemWidth)
{
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new (std::nothrow) TableViewItem();

	Label* pGroupNameLable = null;
	Label* pSoundLabelMin = null;
	Label* pSoundLabelMax = null;
	Label* pVibrationLabelMin = null;
	Label* pVibrationLabelMax = null;
	Slider* pSlider = null;

	int defaultItemHeight = GetDefaultItemHeight();

	if (groupIndex == ID_GROUP_INDEX_MAIN)
	{
		style = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING;
		pItem->Construct(Tizen::Graphics::Dimension(720, 112), style);

		pGroupNameLable = new (std::nothrow) Label();

		if (itemIndex == ID_GROUP_INDEX_MAIN_ITEM_SOUNDS)
		{
			pGroupNameLable->Construct(Rectangle(0, -9, 240, 130), L"Sounds   ");
			pGroupNameLable->SetTextConfig(44,LABEL_TEXT_STYLE_NORMAL);
		}
		else
		{
			pGroupNameLable->Construct(Rectangle(0, -9, 240, 130), L"Vibration");
			pGroupNameLable->SetTextConfig(44,LABEL_TEXT_STYLE_NORMAL);
		}
		pItem->AddControl(*pGroupNameLable);
	}

	else if (groupIndex == ID_GROUP_INDEX_VOLUME)
	{
		pItem->Construct(Tizen::Graphics::Dimension(720, defaultItemHeight), style);

		pSlider = new (std::nothrow) Slider();
		pSoundLabelMin = new (std::nothrow) Label();
		pSoundLabelMin->Construct(Rectangle(20, 80, 45, 45), L"");

		pSoundLabelMax = new (std::nothrow) Label();
		pSoundLabelMax->Construct(Rectangle(650, 80, 45, 45), L"");

		pSlider->Construct(Rectangle(50, 0, 610, 150), BACKGROUND_STYLE_NONE, true, 0, 15);
		pSlider->SetValue(5);
		pSlider->SetName("IDC_SLIDER_VOLUME");
		pSlider->SetEnabled(false);

		switch (itemIndex)
		{
		case 0:
			pSlider->SetTitleText("Incoming call");
			break;
		case 1:
			pSlider->SetTitleText("Notification");
			break;
		case 2:
			pSlider->SetTitleText("Media");
			break;
		case 3:
			pSlider->SetTitleText("System");
			break;
		}
		pItem->AddControl(*pSlider);
		pItem->AddControl(*pSoundLabelMin);
		pItem->AddControl(*pSoundLabelMax);

		pItem->SetIndividualSelectionEnabled(pSlider, true);
		pItem->SetIndividualSelectionEnabled(pSoundLabelMin, true);
		pItem->SetIndividualSelectionEnabled(pSoundLabelMax, true);

	}

	else if (groupIndex == ID_GROUP_INDEX_VIBRATION)
	{
		pSlider = new (std::nothrow) Slider();
		pVibrationLabelMin = new (std::nothrow) Label();
		pVibrationLabelMin->Construct(Rectangle(20, 80, 45, 45), L"");

		pVibrationLabelMax = new (std::nothrow) Label();
		pVibrationLabelMax->Construct(Rectangle(650, 80, 45, 45), L"");
		pItem->Construct(Tizen::Graphics::Dimension(720, defaultItemHeight), style);
		pSlider->Construct(Rectangle(50, 0, 610, 150), BACKGROUND_STYLE_NONE, true, 0, 15);
		pSlider->SetValue(5);
		pSlider->SetName("IDC_SLIDER_VIBRATION");
		pSlider->SetEnabled(false);

		switch (itemIndex)
		{
		case 0:
			pSlider->SetTitleText("Notification");
			break;
		case 1:
			pSlider->SetTitleText("Haptic feedback");
			break;
		}

		pItem->AddControl(*pSlider);
		pItem->AddControl(*pVibrationLabelMin);
		pItem->AddControl(*pVibrationLabelMax);

		pItem->SetIndividualSelectionEnabled(pSlider, true);
		pItem->SetIndividualSelectionEnabled(pVibrationLabelMin, true);
		pItem->SetIndividualSelectionEnabled(pVibrationLabelMax, true);

	}

	return pItem;
}

void
TableViewForm::UpdateItem(int groupIndex, int itemIndex, TableViewItem* pItem)
{
	Control* pSlider = NULL;

	switch (groupIndex)
	{
		case 1:
			pSlider = pItem->GetControl("IDC_SLIDER_VOLUME", true);
			break;
		case 2:
			pSlider = pItem->GetControl("IDC_SLIDER_VIBRATION", true);
			break;
		default:
			break;
	}
	if(pSlider->IsEnabled() == true)
	{
		pSlider->SetEnabled(false);
	}
	else
	{
		pSlider->SetEnabled(true);
	}
}

void
TableViewForm::UpdateGroupItem(int groupIndex, TableViewGroupItem* pItem)
{

}

int
TableViewForm::GetDefaultItemHeight(void)
{
	return 150;
}

int
TableViewForm::GetDefaultGroupItemHeight(void)
{
	return 60;
}

bool
TableViewForm::DeleteItem(int groupIndex, int itemIndex, TableViewItem* pItem)
{
	delete pItem;

	return true;
}

void
TableViewForm::OnGroupedTableViewGroupItemStateChanged(GroupedTableView& tableView, int groupIndex, TableViewGroupItem* pItem, TableViewItemStatus status)
{

}
void
TableViewForm::OnGroupedTableViewItemStateChanged(GroupedTableView& tableView, int groupIndex, int itemIndex, TableViewItem* pItem, TableViewItemStatus status)
{
	int itemCount = 0;
	switch (status)
	{
	case TABLE_VIEW_ITEM_STATUS_CHECKED:
		if (itemIndex == ID_GROUP_INDEX_MAIN_ITEM_SOUNDS)
		{
			itemCount = __pList->GetItemCountAt(ID_GROUP_INDEX_VOLUME);
			for (int i = 0; i < itemCount; i ++)
			{
				__pList->RefreshItem(ID_GROUP_INDEX_VOLUME, i, TABLE_VIEW_REFRESH_TYPE_ITEM_MODIFY);
			}

		}
		else
		{
			itemCount = __pList->GetItemCountAt(ID_GROUP_INDEX_VIBRATION);
			for (int i = 0; i < itemCount ; i ++)
			{
				__pList->RefreshItem(ID_GROUP_INDEX_VIBRATION, i, TABLE_VIEW_REFRESH_TYPE_ITEM_MODIFY);
			}
		}
		break;

	case TABLE_VIEW_ITEM_STATUS_UNCHECKED:
		if (itemIndex == ID_GROUP_INDEX_MAIN_ITEM_SOUNDS)
		{
			itemCount = __pList->GetItemCountAt(ID_GROUP_INDEX_VOLUME);
			for (int i = 0; i < itemCount ; i ++)
			{
				__pList->RefreshItem(ID_GROUP_INDEX_VOLUME, i, TABLE_VIEW_REFRESH_TYPE_ITEM_MODIFY);
			}
		}
		else
		{
			itemCount = __pList->GetItemCountAt(ID_GROUP_INDEX_VIBRATION);
			for (int i = 0; i < itemCount ; i ++)
			{
				__pList->RefreshItem(ID_GROUP_INDEX_VIBRATION, i, TABLE_VIEW_REFRESH_TYPE_ITEM_MODIFY);
			}
		}
		break;
	default:
		break;
	}
	Invalidate(true);
}

void
TableViewForm::OnGroupedTableViewContextItemActivationStateChanged(GroupedTableView& tableView, int groupIndex, int itemIndex, TableViewContextItem* pContextItem, bool activated)
{
}
