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
#include "MenuForm.h"
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Media;

const wchar_t LIST_STYLE_CALL_NORMAL_BITMAP[] = L"call_type1.png";
const wchar_t LIST_STYLE_CALL_PRESS_BITMAP[] = L"call_f_type1.png";
const wchar_t LIST_STYLE_MSG_NORMAL_BITMAP[] = L"message_type1.png";
const wchar_t LIST_STYLE_MSG_PRESS_BITMAP[] = L"message_f_type1.png";

const wchar_t ICON_STYLE_CALL_NORMAL_BITMAP[] = L"call_type2.png";
const wchar_t ICON_STYLE_CALL_PRESS_BITMAP[] = L"call_f_type2.png";
const wchar_t ICON_STYLE_MSG_NORMAL_BITMAP[] = L"message_type2.png";
const wchar_t ICON_STYLE_MSG_PRESS_BITMAP[] = L"message_f_type2.png";

const wchar_t GRID_STYLE_CALL_NORMAL_BITMAP[] = L"call_type2.png";
const wchar_t GRID_STYLE_CALL_PRESS_BITMAP[] = L"call_f_type2.png";
const wchar_t GRID_STYLE_CALL_HIGHLIGHT_BITMAP[] = L"alarm_type1.png";
const wchar_t GRID_STYLE_MSG_NORMAL_BITMAP[] = L"message_type2.png";
const wchar_t GRID_STYLE_MSG_PRESS_BITMAP[] = L"message_f_type2.png";
const wchar_t GRID_STYLE_MSG_HIGHLIGHT_BITMAP[] = L"home_type1.png";

const int LABEL_HEIGHT = 150;

MenuForm::MenuForm()
	: __pContextMenuIcon(null)
	, __pContextMenuIconText(null)
	, __pContextMenuGrid(null)
	, __pLabelLog(null)
{
}

MenuForm::~MenuForm()
{
}

bool
MenuForm::Initialize(void)
{
	Construct(L"IDF_FORM_MENU");
	return true;
}

result
MenuForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	CreateContextMenuListStyle();
	CreateContextMenuGridStyle();

	Button* pButtonList = static_cast<Button*>(GetControl("IDC_BUTTON_LIST", true));
	if(pButtonList)
	{
		pButtonList->SetActionId(ID_BUTTON_CONTEXT_LIST);
		pButtonList->AddActionEventListener(*this);
	}
	Button* pButtonGrid = static_cast<Button*>(GetControl("IDC_BUTTON_GRID", true));
	if(pButtonGrid)
	{
		pButtonGrid->SetActionId(ID_BUTTON_CONTEXT_GRID);
		pButtonGrid->AddActionEventListener(*this);
	}

	return r;
}

result
MenuForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	delete __pContextMenuIcon;
	delete __pContextMenuIconText;
	delete __pContextMenuGrid;

	return r;
}

void
MenuForm::CreateContextMenuListStyle(void)
{
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	Bitmap* pNormalBitmap1 = pAppResource->GetBitmapN(LIST_STYLE_CALL_NORMAL_BITMAP);
	Bitmap* pPressedBitmap1 = pAppResource->GetBitmapN(LIST_STYLE_CALL_PRESS_BITMAP);
	Bitmap* pNormalBitmap2 = pAppResource->GetBitmapN(LIST_STYLE_MSG_NORMAL_BITMAP);
	Bitmap* pPressedBitmap2 = pAppResource->GetBitmapN(LIST_STYLE_MSG_PRESS_BITMAP);

	__pContextMenuIconText = new (std::nothrow) ContextMenu();
	__pContextMenuIconText->Construct(Point(360, 260), CONTEXT_MENU_STYLE_LIST);
	__pContextMenuIconText->AddItem(L"Item 1", ID_CONTEXT_ITEM1, *pNormalBitmap1, pPressedBitmap1);
	__pContextMenuIconText->AddItem(L"Item 2", ID_CONTEXT_ITEM2, *pNormalBitmap2, pPressedBitmap2);
	__pContextMenuIconText->AddActionEventListener(*this);

	// Deallocate bitmaps
	delete pNormalBitmap1;
	delete pPressedBitmap1;
	delete pNormalBitmap2;
	delete pPressedBitmap2;

}

void
MenuForm::CreateContextMenuGridStyle(void)
{
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	Bitmap* pNormalBitmap1 = pAppResource->GetBitmapN(GRID_STYLE_CALL_NORMAL_BITMAP);
	Bitmap* pPressedBitmap1 = pAppResource->GetBitmapN(GRID_STYLE_CALL_PRESS_BITMAP);
	Bitmap* pHighlightBitmap1 = pAppResource->GetBitmapN(GRID_STYLE_CALL_HIGHLIGHT_BITMAP);

	Bitmap* pNormalBitmap2 = pAppResource->GetBitmapN(GRID_STYLE_MSG_NORMAL_BITMAP);
	Bitmap* pPressedBitmap2 = pAppResource->GetBitmapN(GRID_STYLE_MSG_PRESS_BITMAP);
	Bitmap* pHighlightBitmap2 = pAppResource->GetBitmapN(GRID_STYLE_MSG_HIGHLIGHT_BITMAP);

	__pContextMenuGrid = new (std::nothrow) ContextMenu();
	__pContextMenuGrid->Construct(Point(360, 365), CONTEXT_MENU_STYLE_GRID);
	__pContextMenuGrid->AddItem(*pNormalBitmap1,pPressedBitmap1,pHighlightBitmap1, ID_CONTEXT_ITEM1);
	__pContextMenuGrid->AddItem(*pNormalBitmap2,pPressedBitmap2,pHighlightBitmap2, ID_CONTEXT_ITEM2);
	__pContextMenuGrid->AddItem(L"Item 1", ID_CONTEXT_ITEM3);
	__pContextMenuGrid->AddItem(L"Long Item 1", ID_CONTEXT_ITEM4);
	__pContextMenuGrid->AddItem(L"Item 2", ID_CONTEXT_ITEM5);
	__pContextMenuGrid->AddItem(L"Long Long Item 1", ID_CONTEXT_ITEM6);
	__pContextMenuGrid->AddActionEventListener(*this);
	// Deallocate bitmaps
	delete pNormalBitmap1;
	delete pPressedBitmap1;
	delete pHighlightBitmap1;
	delete pNormalBitmap2;
	delete pPressedBitmap2;
	delete pHighlightBitmap2;
}

void
MenuForm::OnActionPerformed(const Control& source, int actionId)
{
	String itemText(L"");
	switch (actionId)
	{
	case ID_BUTTON_CONTEXT_LIST:
		__pContextMenuIconText->SetShowState(true);
		__pContextMenuIconText->Show();
		break;
	case ID_BUTTON_CONTEXT_GRID:
		__pContextMenuGrid->SetShowState(true);
		__pContextMenuGrid->Show();
		break;
	default:
		break;
	}
}
