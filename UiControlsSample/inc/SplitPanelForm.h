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
#ifndef _SPLIT_PANEL_FORM_H_
#define _SPLIT_PANEL_FORM_H_

#include "BaseForm.h"

class SplitPanelForm
	: public BaseForm
	, public Tizen::Ui::IOrientationEventListener
	, public Tizen::Ui::Controls::IListViewItemEventListener
	, public Tizen::Ui::Controls::IListViewItemProvider
	, public Tizen::Ui::Controls::ISplitPanelEventListener
{
public:
	SplitPanelForm(void);
	virtual ~SplitPanelForm(void);

	virtual bool Initialize(void);
	virtual result OnInitializing(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnOrientationChanged(const Tizen::Ui::Control &source, Tizen::Ui::OrientationStatus orientationStatus);
	virtual void OnDividerPositionChanged(Tizen::Ui::Controls::SplitPanel& source, int position);
	virtual void OnDividerDoublePressed(Tizen::Ui::Controls::SplitPanel& source);
	//ListView
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnItemReordered(Tizen::Ui::Controls::ListView &view, int oldIndex, int newIndex);
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::ListItemBase*  CreateItem (int index, int itemWidth);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth);

private:
	static const int ID_BUTTON_SECOND_MAXIMIZE = 102;
	static const int ID_BUTTON_RESTORE = 103;
	static const int ID_FORMAT_STRING = 700;
	static const int ID_FORMAT_NULL = -1;
	static const int ID_FORMAT_ROTATE = 500;
	static const int ID_FORMAT_MAXIMIZE = 501;
 	static const int ID_FORMAT_RESTORE = 502;

	Tizen::Ui::Controls::Button* __pButtonForMaximizingSecondPane;
	Tizen::Ui::Controls::Button* __pButtonForRestoringPanes;
	Tizen::Ui::Controls::SplitPanel* __pSplitPanel;
	Tizen::Ui::Controls::ListView* __pFirstPane;
	Tizen::Ui::Controls::Panel* __pSecondPane;
	Tizen::Ui::Controls::Label* __pLabel;
}; // SplitPanelForm

#endif  //_SPLIT_PANEL_FORM_H_
