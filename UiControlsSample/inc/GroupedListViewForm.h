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
#ifndef _GROUPED_LISTVIEW_FORM_H_
#define _GROUPED_LISTVIEW_FORM_H_

#include <FApp.h>
#include "BaseForm.h"

class CustomGroupedListElement
	: public Tizen::Ui::Controls::ICustomElement
{
public:
	CustomGroupedListElement(void){}
	virtual ~CustomGroupedListElement(void){}
	static const int LINE_WITH = 3;
	static const int TEXT_MARGIN_X = 10;
	static const int TEXT_MARGIN_Y = 15;

	bool OnDraw(Tizen::Graphics::Canvas& canvas, const Tizen::Graphics::Rectangle& rect, Tizen::Ui::Controls::ListItemDrawingStatus itemStatus)
 	{
  		Tizen::Graphics::Font font;
  		font.Construct(Tizen::Graphics::FONT_STYLE_PLAIN , (rect.height/2));
  		canvas.SetFont(font);
  		canvas.SetLineWidth(LINE_WITH);
  		canvas.SetForegroundColor(Tizen::Graphics::Color::GetColor(Tizen::Graphics::COLOR_ID_GREEN));

  		int fontRectHeight = font.GetMaxHeight();

  		if (canvas.DrawRectangle(rect) != E_SUCCESS)
  		{
   			return false;
 		 }
  		if (canvas.DrawText(Tizen::Graphics::Point(rect.x + TEXT_MARGIN_X, rect.y + ((rect.height-fontRectHeight)/2)), L"Custom") != E_SUCCESS)
  		{
  			 return false;
  		}
  		return true;
 	}
}; // CustomGroupedListElement

class GroupedListViewForm
	: public BaseForm
    , public Tizen::Ui::Controls::IGroupedListViewItemEventListener
    , public Tizen::Ui::Controls::IGroupedListViewItemProvider
    , public Tizen::Ui::Controls::IFastScrollListener
{
public:
	GroupedListViewForm(void);
	virtual ~GroupedListViewForm(void);

	virtual bool Initialize(void);
	void GetBitmap(void);
	void CreateListView(void);
	void CreateGroupedListView(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	// IGroupedListViewItemEventListener
	virtual void OnGroupedListViewContextItemStateChanged(Tizen::Ui::Controls::GroupedListView &listView, int groupIndex, int itemIndex, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnGroupedListViewItemStateChanged(Tizen::Ui::Controls::GroupedListView &listView, int groupIndex, int itemIndex, int elementId, Tizen::Ui::Controls::ListItemStatus state);
	virtual void OnGroupedListViewItemSwept(Tizen::Ui::Controls::GroupedListView &listView, int groupIndex,  int itemIndex, Tizen::Ui::Controls::SweepDirection direction);
	virtual void OnGroupedListViewItemLongPressed(Tizen::Ui::Controls::GroupedListView &listView, int groupIndex, int itemIndex, int elementId, bool& invokeListViewItemCallback);

	// IGroupedListViewItemProvider
	virtual int GetGroupCount(void);
	virtual int GetItemCount(int groupIndex);
	virtual Tizen::Ui::Controls::GroupItem* CreateGroupItem(int groupIndex, int itemWidth);
	virtual bool DeleteGroupItem(int groupIndex, Tizen::Ui::Controls::GroupItem* pItem, int itemWidth);
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int groupIndex, int itemIndex, int itemWidth);
	virtual bool DeleteItem(int groupIndex, int itemIndex, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);

	// FastScroll
	virtual void OnFastScrollIndexSelected(Tizen::Ui::Control& source, Tizen::Base::String& index);

private:
	static const int ID_FORMAT_NULL = -1;
	static const int ID_FORMAT_STRING = 500;
	static const int ID_FORMAT_BITMAP = 501;
 	static const int ID_FORMAT_CUSTOM = 503;
 	static const int ID_CONTEXT_ITEM_1 = 504;
 	static const int ID_CONTEXT_ITEM_2 = 505;

	Tizen::Ui::Controls::GroupedListView* __pList;
	Tizen::Ui::Controls::Label* __pLabelLog;
	Tizen::Graphics::Bitmap* __pHome;
	Tizen::Graphics::Bitmap* __pMsg;
	Tizen::Graphics::Bitmap* __pAlarm;
	Tizen::Graphics::Bitmap* __pCall;
	CustomGroupedListElement* __pCustomGroupedListElement;
	Tizen::Ui::Controls::ListContextItem* __pItemContext;
}; // GroupedListViewForm

#endif // _GROUPED_LISTVIEW_FORM_H_
