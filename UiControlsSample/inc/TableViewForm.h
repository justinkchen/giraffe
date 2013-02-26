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
#ifndef _TABLEVIEW_FORM_H_
#define _TABLEVIER_FORM_H_

#include <FApp.h>
#include "BaseForm.h"

class TableViewForm
	: public BaseForm
	, public Tizen::Ui::Controls::IGroupedTableViewItemEventListener
	, public Tizen::Ui::Controls::IGroupedTableViewItemProvider
{
public:
	TableViewForm(void);
	virtual ~TableViewForm(void);

	virtual bool Initialize(void);
	void GetBitmap(void);
	void CreateTableView(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	//IGroupedTableViewItemProvider
	virtual int GetGroupCount(void);
	virtual int GetItemCount(int groupIndex);
	virtual Tizen::Ui::Controls::TableViewGroupItem* CreateGroupItem(int groupIndex, int itemWidth);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int groupIndex, int itemIndex, int itemWidth);
	virtual bool DeleteItem(int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual bool DeleteGroupItem(int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem);
	virtual void UpdateItem(int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateGroupItem(int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem);
	virtual int GetDefaultItemHeight(void);
	virtual int GetDefaultGroupItemHeight(void);

	//tableview event

	virtual void OnGroupedTableViewGroupItemStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
	virtual void OnGroupedTableViewItemStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
	virtual void OnGroupedTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated);
private:
	static const int ID_GROUP_INDEX_MAIN = 0;
	static const int ID_GROUP_INDEX_VOLUME = 1;
	static const int ID_GROUP_INDEX_VIBRATION = 2;
	static const int ID_GROUP_INDEX_INFORMATION = 3;
	static const int ID_GROUP_INDEX_MAIN_ITEM_SOUNDS = 0;
	static const int ID_GROUP_INDEX_MAIN_ITEM_VIBRATION = 1;

	Tizen::Ui::Controls::GroupedTableView* __pList;
	Tizen::Ui::Controls::TableViewItem* __pItem;
	Tizen::Ui::Controls::Label* pGroupNameLabel;
	Tizen::Graphics::Bitmap* __pMinSoundBitmap;
	Tizen::Graphics::Bitmap* __pMaxSoundBitmap;
	Tizen::Graphics::Bitmap* __pMinVibrationBitmap;
	Tizen::Graphics::Bitmap* __pMaxVibrationBitmap;

}; // TableViewForm

#endif // _TABLEVIEW_FORM_H_
