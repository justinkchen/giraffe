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
#include "EnrichedTextForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

const int ROTATION_INITIALIZE_INDEX = -1;
const int ROTATION_INDEX_MAX_1 = 1;
const int ROTATION_INDEX_MAX_2 = 2;
const int ITEM_COUNT = 11;

EnrichedTextForm::EnrichedTextForm(void)
	: __pEnrichedText(null)
	, __pTextElement1(null)
	, __pTextElement2(null)
	, __pTextElement3(null)
	, __pLabelText(null)
	, __vertialCount(0)
	, __horizontalCount(0)
	, __wrapCount(0)
	, __abbriviationCount(0)
{
}

EnrichedTextForm::~EnrichedTextForm(void)
{
	delete __pTextElement1;
	delete __pEnrichedText;
	delete __pTextElement2;
	delete __pTextElement3;
}

bool
EnrichedTextForm::Initialize()
{
	Construct(L"IDF_FORM_ENRICHEDTEXT");
	return true;
}

result
EnrichedTextForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	ButtonItem buttonLeftItem;
	buttonLeftItem.Construct(BUTTON_ITEM_STYLE_TEXT, ID_EXIT);
	buttonLeftItem.SetText(L"Back");

	Rectangle rect(20, 200, 680, 360);
	__pEnrichedText = new (std::nothrow) EnrichedText();
	__pEnrichedText->Construct(Dimension(rect.width, rect.height));
	__pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
	__pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
	__pEnrichedText->SetTextWrapStyle(TEXT_WRAP_NONE);
	__pEnrichedText->SetTextAbbreviationEnabled(true);

	Font* pFont = new (std::nothrow) Font();
	pFont->Construct(FONT_STYLE_PLAIN, 35);

	Font* pFontItalic = new (std::nothrow) Font();
	pFontItalic->Construct(FONT_STYLE_ITALIC, 30);

	Bitmap* pBitmap = App::GetInstance()->GetAppResource()->GetBitmapN(L"home_type3.png");
	if (pBitmap)
	{
		pBitmap->Scale(Dimension(50, 50));
	}

	__pTextElement1 = new (std::nothrow) TextElement();
	__pTextElement2 = new (std::nothrow) TextElement();
	__pTextElement3 = new (std::nothrow) TextElement();

	__pTextElement1->Construct(L"Tizen is a new open platform that enables richer user experience");
	__pTextElement2->Construct(L"in applications on mobile devices.");
	__pTextElement3->Construct(L"Tizen API Reference provides of all the powerful features. Tizen is a new open platform that enables richer user experience in applications on mobile devices");

	__pTextElement1->SetTextColor(Color::GetColor(COLOR_ID_YELLOW));

	__pTextElement2->SetTextColor(Color::GetColor(COLOR_ID_BLUE));
	__pTextElement2->SetFont(*pFont);

	__pTextElement3->SetTextColor(Color::GetColor(COLOR_ID_VIOLET));
	__pTextElement3->SetFont(*pFontItalic);

	__pEnrichedText->Add(*__pTextElement1);
	__pEnrichedText->Add(*__pTextElement2);
	__pEnrichedText->Add(*pBitmap);
	__pEnrichedText->Add(*__pTextElement3);

	__pEnrichedText->Refresh();

	ListView* pListview = static_cast<ListView*>(GetControl("IDC_LISTVIEW", true));
	if(pListview)
	{
		pListview->SetBounds(0, GetClientAreaBounds().height/2, GetClientAreaBounds().width, GetClientAreaBounds().height/2);
		pListview->AddListViewItemEventListener(*this);
		pListview->SetItemProvider(*this);
	}

	delete pFont;
	delete pFontItalic;
	delete pBitmap;

	return r;
}

result
EnrichedTextForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void
EnrichedTextForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
}

result
EnrichedTextForm::OnDraw(void)
{
	result r = E_SUCCESS;

	Rectangle rect1(45, 250, 630, 313);

	Canvas* pCanvas = GetCanvasN();

	if (pCanvas)
	{
		pCanvas->Clear();
		pCanvas->SetLineWidth(3);
		pCanvas->FillRectangle(Color::GetColor(COLOR_ID_GREY), Rectangle(rect1));
	}

	if (__pEnrichedText->GetTextLength() != 0)
	{
		__pEnrichedText->SetSize(rect1.width, rect1.height);
		pCanvas->DrawText(Point(rect1.x, rect1.y), *__pEnrichedText);
	}

	delete pCanvas;

	return r;
}

void
EnrichedTextForm::OnListViewContextItemStateChanged(ListView& listView, int index, int elementId, ListContextItemStatus status)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");

}

void
EnrichedTextForm::OnListViewItemLongPressed(ListView& listView, int index, int elementId, bool& invokeListViewItemCallback)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");

}

void
EnrichedTextForm::OnListViewItemStateChanged(ListView& listView, int index, int elementId, ListItemStatus status)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
	switch (index)
	{
	case 0:
	{
		__pEnrichedText->SetTextWrapStyle(TEXT_WRAP_NONE);
		__pEnrichedText->Refresh();
		break;
	}
	case 1:
	{
		__pEnrichedText->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);
		break;
	}
	case 2:
	{
		__pEnrichedText->SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
		break;
	}
	case 3:
	{
		__pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
		break;
	}
	case 4:
	{
		__pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
		break;
	}
	case 5:
	{
		__pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
		break;
	}
	case 6:
	{
		__pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
		break;
	}
	case 7:
	{
		__pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
		break;
	}
	case 8:
	{
		__pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
		break;
	}
	case 9:
	{
		__pEnrichedText->SetTextAbbreviationEnabled(true);
		break;
	}
	case 10:
	{
		__pEnrichedText->SetTextAbbreviationEnabled(false);
		break;
	}
	default:
		break;
	}
	Invalidate(true);
}

void
EnrichedTextForm::OnListViewItemSwept(ListView& listView, int index, SweepDirection direction)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");

}

Controls::ListItemBase *
EnrichedTextForm::CreateItem(int index, int itemWidth)
{
	// TODO: Add your implementation codes here
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
		CustomItem* pItem = new (std::nothrow) CustomItem();
		pItem->Construct(Tizen::Graphics::Dimension(itemWidth, 112), style);
		Rectangle mainListItemRect(26, 32, GetClientAreaBounds().width, 50);

		switch(index)
		{
		  case 0:
		      pItem->AddElement(mainListItemRect, TEXT_WRAP_NONE_INDEX, L"Text Wrap None", true);
		      break;
		  case 1:
		      pItem->AddElement(mainListItemRect, TEXT_WRAP_WORD_WRAP_INDEX, L"Text Wrap Word", true);
		      break;
		  case 2:
		      pItem->AddElement(mainListItemRect, TEXT_WRAP_CHARACTER_WRAP_INDEX, L"Text Wrap Character Wrap", true);
		      break;
		  case 3:
		      pItem->AddElement(mainListItemRect, TEXT_ALIGNMENT_LEFT_INDEX, L"Text Alignment Left", true);
		      break;
		  case 4:
		      pItem->AddElement(mainListItemRect, TEXT_ALIGNMENT_CENTER_INDEX, L"Text Alignment Center", true);
		      break;
		  case 5:
		      pItem->AddElement(mainListItemRect, TEXT_ALIGNMENT_RIGHT_INDEX, L"Text Alignment Right", true);
		      break;
		  case 6:
		      pItem->AddElement(mainListItemRect, TEXT_ALIGNMENT_TOP_INDEX, L"Text Alignment Top", true);
		      break;
		  case 7:
			  pItem->AddElement(mainListItemRect, TEXT_ALIGNMENT_MIDDLE_INDEX, L"Text Alignment Middle", true);
			  break;
		  case 8:
			  pItem->AddElement(mainListItemRect, TEXT_ALIGNMENT_BOTTOM_INDEX, L"Text Alignment Bottom", true);
			  break;
		  case 9:
		      pItem->AddElement(mainListItemRect, ABBREVIATION_ENABLED_TRUE, L"Abbreviation Enabled", true);
		      break;
		  case 10:
		      pItem->AddElement(mainListItemRect, ABBREVIATION_ENABLED_FALSE, L"Abbreviation Disabled", true);
		      break;
		default:
			break;
		}
		return pItem;

}

bool
EnrichedTextForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth)
{
	// TODO: Add your implementation codes here
	delete pItem;
	pItem = null;
	return true;

}

int
EnrichedTextForm::GetItemCount(void)
{
	// TODO: Add your implementation codes here

	return ITEM_COUNT;

}
