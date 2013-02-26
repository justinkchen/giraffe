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
#ifndef TABBARFORM_H_
#define TABBARFORM_H_

#include <FApp.h>
#include "BaseForm.h"

class TabBarForm
	: public BaseForm
	, public Tizen::Ui::Controls::IListViewItemEventListener
{
public:
	TabBarForm(void);
	virtual ~TabBarForm(void);

	virtual bool Initialize(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	bool CreateMainList(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	void SetHeaderStyle(int headerType);
	void SetFooterStyle(int footerType);
	void AlignControls(void);


private:
	static const int HEADER_STYLE_0 = 0;
	static const int HEADER_STYLE_1 = 1;
	static const int HEADER_STYLE_2 = 2;
	static const int HEADER_STYLE_3 = 3;
	static const int HEADER_STYLE_4 = 4;
	static const int HEADER_STYLE_5 = 5;
	static const int FOOTER_STYLE_0 = 0;
	static const int FOOTER_STYLE_1 = 1;
	static const int FOOTER_STYLE_2 = 2;

	static const int ID_EXIT = 100;
	static const int ID_HEADER_STYLE = 101;
	static const int ID_FOOTER_STYLE = 102;
	static const int ID_TRANSLUCENT = 103;
	static const int ID_VISIBLE = 104;

	static const int ID_TABBAR_ITEM1 = 201;
	static const int ID_TABBAR_ITEM2 = 202;
	static const int ID_TABBAR_ITEM3 = 203;
	static const int ID_TABBAR_ITEM4 = 204;
	static const int ID_TABBAR_ITEM5 = 205;

	static const int ID_HEADER_LEFTITEM = 301;
	static const int ID_HEADER_CENTERITEM = 302;
	static const int ID_HEADER_RIGHTITEM = 303;
	static const int ID_HEADER_LEFTBUTTON = 304;
	static const int ID_HEADER_RIGHTBUTTON = 305;
	static const int ID_HEADER_OPTIONTAY = 306;

	static const int ID_FOOTER_ITEM1 = 401;
	static const int ID_FOOTER_ITEM2 = 402;
	static const int ID_FOOTER_ITEM3 = 403;
	static const int ID_FOOTER_ITEM4 = 404;
	static const int ID_FOOTER_ITEM5 = 405;
	static const int ID_FOOTER_ITEM6 = 406;
	static const int ID_FOOTER_ITEM7 = 407;
	static const int ID_FOOTER_LEFTBUTTON = 408;
	static const int __indicatorHeight = 38;

 	static const int ID_CONTEXT_ITEM_1 = 504;
 	static const int ID_CONTEXT_ITEM_2 = 505;

	static const int ID_HEADER_ITEM1 = 601;
	static const int ID_HEADER_ITEM2 = 602;
	static const int ID_HEADER_ITEM3 = 603;
	static const int ID_HEADER_ITEM4 = 604;
	static const int ID_HEADER_ITEM5 = 605;
	static const int ID_HEADER_ITEM6 = 606;
	static const int ID_HEADER_ITEM7 = 607;

	Tizen::Ui::Controls::Button* __pHeaderStyle;
	Tizen::Ui::Controls::Button* __pFooterStyle;
	Tizen::Ui::Controls::Button* __pTranslucent;
	Tizen::Ui::Controls::Button* __pVisible;
	Tizen::Ui::Controls::Button* __pExit;
	Tizen::Ui::Controls::TabBar* __pTabBar;
	Tizen::Graphics::Bitmap* __pheaderLeftItemBitmap;
	Tizen::Graphics::Bitmap* __pLeftItemBitmap;
	Tizen::Graphics::Bitmap* __pRightItemBitmap;
	Tizen::Ui::Controls::Label* __pLogLabel;

	int __headerTypeIndex;
	int __footerTypeIndex;
	int __startY;
	bool __isTranslucent;
	bool __isVisible;
	bool __isOpened;
	bool __isAdded;

	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus status);
	virtual void OnListViewItemLongPressed(Tizen::Ui::Controls::ListView& listView, int index, int elementId, bool& invokeListViewItemCallback);
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction);
}; // TabBarForm



#endif /* TABBARFORM_H_ */
