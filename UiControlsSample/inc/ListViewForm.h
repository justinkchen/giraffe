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
#ifndef _LISTVIEW_FORM_H_
#define _LISTVIEW_FORM_H_

#include <FApp.h>
#include "BaseForm.h"

	class CustomListElement
		: public Tizen::Ui::Controls::ICustomElement
	{
	public:
		CustomListElement(void) {}
		~CustomListElement(void) {}

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
	}; // CustomListElement
class ListViewForm
	: public BaseForm
	, public Tizen::Ui::Controls::IListViewItemEventListener
	, public Tizen::Ui::Controls::IListViewItemProvider
{
public:
	ListViewForm(void);
	virtual ~ListViewForm(void);

	virtual bool Initialize(void);
	void GetBitmap(void);
	void CreateListView(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	// IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual void OnListViewItemLongPressed(Tizen::Ui::Controls::ListView &listView, int index, int elementId, bool& invokeListViewItemCallback);

	//IListViewItemProvider
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem (int index, int itemWidth);
	virtual bool  DeleteItem (int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth);
	virtual int GetItemCount(void);




private:
	static const int ID_FORMAT_NULL = -1;
	static const int ID_REORDER_ON = 100;
	static const int ID_REORDER_OFF = 101;
	static const int ID_FORMAT_STRING = 500;
	static const int ID_FORMAT_BITMAP = 501;
 	static const int ID_FORMAT_CUSTOM = 503;
 	static const int ID_CONTEXT_ITEM_1 = 504;
 	static const int ID_CONTEXT_ITEM_2 = 505;


	Tizen::Ui::Controls::ListView* __pList;
	Tizen::Ui::Controls::Label* __pLabelLog;
	Tizen::Graphics::Bitmap* __pHome;
	Tizen::Graphics::Bitmap* __pMsg;
	Tizen::Graphics::Bitmap* __pAlarm;
	Tizen::Graphics::Bitmap* __pCall;
	CustomListElement* __pCustomListElement;
	Tizen::Ui::Controls::ListContextItem* __pItemContext;

}; // ListViewForm

#endif // _LISTVIEW_FORM_H_
