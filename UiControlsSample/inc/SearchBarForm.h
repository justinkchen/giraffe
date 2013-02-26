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
#ifndef _SEARCHBAR_FORM_H_
#define _SEARCHBAR_FORM_H_

#include "BaseForm.h"

class SearchBarForm
	: public BaseForm
	, public Tizen::Ui::Controls::ISearchBarEventListener
	, public Tizen::Ui::IKeypadEventListener
	, public Tizen::Ui::ITextEventListener
	, public Tizen::Ui::Controls::IGroupedListViewItemEventListener
	, public Tizen::Ui::Controls::IGroupedListViewItemProvider
	, public Tizen::Ui::Controls::IFastScrollListener
	, public Tizen::Ui::Controls::IListViewItemEventListener
	, public Tizen::Ui::Controls::IListViewItemProvider
	, public Tizen::Ui::ITouchEventListener
{
public:
	SearchBarForm(void);
	virtual ~SearchBarForm(void);

	virtual bool Initialize(void);
	void SetGroupList(void);
	void UpdateSearchResult(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	// ISearchBarEventListener
	virtual void OnSearchBarModeChanged(Tizen::Ui::Controls::SearchBar& source, Tizen::Ui::Controls::SearchBarMode mode);
	virtual void OnSearchBarContentAreaResized(Tizen::Ui::Controls::SearchBar& source, Tizen::Graphics::Dimension& size) {}
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source){}

	// IKeypadEventListener
	virtual void OnKeypadActionPerformed(Tizen::Ui::Control &source, Tizen::Ui::KeypadAction keypadAction);
	virtual void OnKeypadClosed(Tizen::Ui::Control &source);
	virtual void OnKeypadOpened(Tizen::Ui::Control &source);
	virtual void OnKeypadWillOpen(Tizen::Ui::Control &source) {}
	virtual void OnKeypadBoundsChanged(Tizen::Ui::Control& source) {}

	// IGroupedListViewItemEventListener
	virtual void OnGroupedListViewContextItemStateChanged(Tizen::Ui::Controls::GroupedListView &listView, int groupIndex, int itemIndex, int elementId, Tizen::Ui::Controls::ListContextItemStatus state){}
	virtual void OnGroupedListViewItemStateChanged(Tizen::Ui::Controls::GroupedListView &listView, int groupIndex, int itemIndex, int elementId, Tizen::Ui::Controls::ListItemStatus state);
	virtual void OnGroupedListViewItemSwept(Tizen::Ui::Controls::GroupedListView &listView, int groupIndex,  int itemIndex, Tizen::Ui::Controls::SweepDirection direction){}

	// IGroupedListViewItemProvider
	virtual int GetGroupCount(void);
	virtual int GetItemCount(int groupIndex);
	virtual Tizen::Ui::Controls::GroupItem* CreateGroupItem(int groupIndex, int itemWidth);
	virtual bool DeleteGroupItem(int groupIndex, Tizen::Ui::Controls::GroupItem* pItem, int itemWidth);
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int groupIndex, int itemIndex, int itemWidth);
	virtual bool DeleteItem(int groupIndex, int itemIndex, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);

	// FastScroll
	virtual void OnFastScrollIndexSelected(Tizen::Ui::Control& source, Tizen::Base::String& index);

	// IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction);

	//IListViewItemProvider
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem (int index, int itemWidth);
	virtual bool  DeleteItem (int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth);
	virtual int GetItemCount(void);

	//ITouchEventListener
	virtual void  OnTouchDoublePressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){}
	virtual void  OnTouchFocusIn (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){}
	virtual void  OnTouchFocusOut (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){}
	virtual void  OnTouchLongPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){}
	virtual void  OnTouchMoved (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){}
	virtual void  OnTouchPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchReleased (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){}

private:
	static const int ID_FORMAT_STRING = 500;
	static const int ID_FORMAT_BITMAP = 501;
	static const int ID_FORMAT_CUSTOM = 503;
	static const int ID_CONTEXT_ITEM_1 = 504;
	static const int ID_CONTEXT_ITEM_2 = 505;
	static const int ID_GROUPITEM_INDEX = -1;
	static const int GROUP_MAX = 26;
	static const int ITEM_MAX = 30;

	Tizen::Ui::Controls::SearchBar* __pSearchBar;
	Tizen::Ui::Controls::Header* __pHeader;
	Tizen::Ui::Controls::GroupedListView* __pAllTextGroupedListView;
	Tizen::Ui::Controls::ListView* __pSearchBarListView;
	Tizen::Base::Collection::ArrayList* __pSearchedTextList;
	Tizen::Base::String __pWordString[GROUP_MAX][ITEM_MAX];
	Tizen::Base::String __groupCapitalArray[GROUP_MAX];
}; // SearchBarForm

#endif	// _SEARCHBAR_FORM_H_
