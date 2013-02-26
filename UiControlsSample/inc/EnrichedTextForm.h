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
#ifndef _ENRICHED_TEXT_FORM_H_
#define _ENRICHED_TEXT_FORM_H_

#include <FApp.h>
#include "BaseForm.h"

class EnrichedTextForm
	: public BaseForm,
 	public Tizen::Ui::Controls::IListViewItemEventListener,
 	public Tizen::Ui::Controls::IListViewItemProvider
{
public:
	EnrichedTextForm(void);
	virtual ~EnrichedTextForm(void);

	virtual bool Initialize(void);
	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

private:
	static const int  ID_EXIT =100;
	//ID_FOOTER_ITEM1
	static const int ID_VERTICAL_ITEM = 201;
	static const int ID_HORIZONTAL_ITEM = 202;
	static const int ID_WRAP_ITEM = 203;
	static const int ID_ABBREVIATION_ITEM = 204;

	//Wrap Style
	static const int TEXT_WRAP_NONE_INDEX = 0;
	static const int TEXT_WRAP_WORD_WRAP_INDEX = 1;
	static const int TEXT_WRAP_CHARACTER_WRAP_INDEX = 2;

	//Horizontal Style
	static const int TEXT_ALIGNMENT_LEFT_INDEX = 0;
	static const int TEXT_ALIGNMENT_CENTER_INDEX = 1;
	static const int TEXT_ALIGNMENT_RIGHT_INDEX = 2;

	//Vertical
	static const int TEXT_ALIGNMENT_TOP_INDEX = 0;
	static const int TEXT_ALIGNMENT_MIDDLE_INDEX = 1;
	static const int TEXT_ALIGNMENT_BOTTOM_INDEX  = 2;

	//Abbreviation
	static const int ABBREVIATION_ENABLED_TRUE = 0;
	static const int ABBREVIATION_ENABLED_FALSE = 1;

	Tizen::Graphics::EnrichedText* __pEnrichedText;
	Tizen::Graphics::TextElement* __pTextElement1;
	Tizen::Graphics::TextElement* __pTextElement2;
	Tizen::Graphics::TextElement* __pTextElement3;
	Tizen::Ui::Controls::Label *__pLabelText;

	int __vertialCount;
	int __horizontalCount;
	int __wrapCount;
	int __abbriviationCount;

	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus status);
	virtual void OnListViewItemLongPressed(Tizen::Ui::Controls::ListView& listView, int index, int elementId, bool& invokeListViewItemCallback);
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual Tizen::Ui::Controls::ListItemBase * 	CreateItem(int index, int itemWidth);
	virtual bool 	DeleteItem(int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth);
	virtual int 	GetItemCount(void);
}; // EnrichedTextForm

#endif	// _ENRICHEDTEXT_FORM_H_
