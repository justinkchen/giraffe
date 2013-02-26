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
#ifndef _MAIN_FORM_H_
#define _MAIN_FORM_H_

#include "BaseForm.h"
#include <FUi.h>

class MainForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::Controls::IListViewItemEventListener
	, public Tizen::Ui::Controls::IListViewItemProvider
	, public Tizen::Ui::Controls::IFormBackEventListener
{
public:
	MainForm(void);
	virtual ~MainForm(void);

	virtual bool Initialize(void);
	bool CreateMainList(void);
	bool MoveToForm(int index);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	virtual result OnInitializing(void);
	//ListView
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnItemReordered(Tizen::Ui::Controls::ListView &view, int oldIndex, int newIndex);
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::ListItemBase*  CreateItem (int index, int itemWidth);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth);

private:
	static const int ID_FORMAT_STRING = 500;

	Tizen::Ui::Controls::ListView* __pList;
}; // MainForm

#endif // _MAIN_FORM_H_
