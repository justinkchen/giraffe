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
#ifndef _ICON_LISTVIEW_FORM_H_
#define _ICON_LISTVIEW_FORM_H_

#include <FApp.h>
#include "BaseForm.h"

class IconListViewForm
	: public BaseForm
	, public Tizen::Ui::Controls::IIconListViewItemProvider
	, public Tizen::Ui::Controls::IIconListViewItemEventListener
{
public:
	IconListViewForm(void);
	virtual ~IconListViewForm(void);

	virtual bool Initialize(void);
	void GetBitmap(void);
	void CreateIconListView(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	// IIconListViewItemEventListener
	virtual void OnIconListViewItemStateChanged (Tizen::Ui::Controls::IconListView &view, int index, Tizen::Ui::Controls::IconListViewItemStatus status);

	//IIconListViewItemProvider
	virtual Tizen::Ui::Controls::IconListViewItem* CreateItem(int index);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::IconListViewItem* pItem);
	virtual int GetItemCount(void);

private:
	static const int ID_FOOTER_HORIZONTAL = 101;
	static const int ID_FOOTER_VERTICAL = 102;
	static const int ID_REORDER_ON = 103;
	static const int ID_REORDER_OFF = 104;
	static const int ID_FOOTER_ICON = 105;
	static const int ID_FORMAT_STRING = 500;

	Tizen::Ui::Controls::Label* __pLabelLog;
	Tizen::Graphics::Bitmap* __pHome;
	Tizen::Graphics::Bitmap* __pMsg;
	Tizen::Graphics::Bitmap* __pAlarm;
	Tizen::Graphics::Bitmap* __pMore;
	Tizen::Ui::Controls::IconListView* __pHorizontalIconList;
	Tizen::Ui::Controls::IconListView* __pVerticalIconList;

}; // IconListViewForm

#endif // _ICON_LISTVIEW_FORM_H_
