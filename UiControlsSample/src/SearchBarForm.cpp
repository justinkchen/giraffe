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
#include "SearchBarForm.h"

using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Media;

const int GROUP_MAX = 26;
const int ITEM_MAX = 30;

SearchBarForm::SearchBarForm(void)
	: __pSearchBar(null)
	, __pHeader(null)
	, __pAllTextGroupedListView(null)
	, __pSearchBarListView(null)
	, __pSearchedTextList(null)
{
}

SearchBarForm::~SearchBarForm(void)
{
}

bool
SearchBarForm::Initialize()
{
	Construct(L"IDF_FORM_SEARCHBAR");
	return true;
}

result
SearchBarForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;
	Rectangle rect = GetClientAreaBounds();

	__pAllTextGroupedListView = static_cast <GroupedListView*> (GetControl("IDC_GROUPEDLISTVIEW"));
	__pAllTextGroupedListView->SetItemProvider(*this);
	__pAllTextGroupedListView->AddGroupedListViewItemEventListener(*this);
	__pAllTextGroupedListView->SetFastScrollIndex(L"abcdefghijklmnopqrstuvwxyz", false);
	__pAllTextGroupedListView->AddFastScrollListener(*this);

	__pSearchBar = static_cast<SearchBar*>(GetControl("IDC_SEARCHBAR"));
	__pSearchBar->SetText(L"Click here!");
	__pSearchBar->AddSearchBarEventListener(*this);
	__pSearchBar->AddTextEventListener(*this);
	__pSearchBar->AddKeypadEventListener(*this);

	SetGroupList();
	__pSearchBarListView = new (std::nothrow) ListView();
	__pSearchBarListView->Construct(Rectangle(0, 0, rect.width, rect.height - __pSearchBar->GetHeight()), true, false);
	__pSearchBarListView->SetItemProvider(*this);
	__pSearchBarListView->AddListViewItemEventListener(*this);
	__pSearchBarListView->SetTextOfEmptyList(L"No search result");
 	__pSearchBar->SetContent(__pSearchBarListView);

    __pSearchBarListView->AddTouchEventListener(*this);
 	__pSearchBarListView->SetShowState(false);

	// Create WatchTextList
 	__pSearchedTextList = new (std::nothrow) ArrayList();
 	__pSearchedTextList->Construct();

 	AddControl(*__pAllTextGroupedListView);
	AddControl(*__pSearchBar);

	return r;
}

result
SearchBarForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	__pSearchedTextList->RemoveAll(true);
	delete __pSearchedTextList;

	return r;
}

void
SearchBarForm::SetGroupList(void)
{
	for (int i = 0; i < GROUP_MAX ; i ++)
	{
		__groupCapitalArray[i].Format(5, L"%c", i + 97);
	}
	for (int i = 0; i < GROUP_MAX; i ++)
	{
		for (int j = 0; j < ITEM_MAX; j ++)
		{
			String listItem = __groupCapitalArray[i];
			int stringNum = Tizen::Base::Utility::Math::Rand() % 7 + 1;

			for (int k = 0; k < stringNum; k ++)
			{
				int selectedAlpha = Tizen::Base::Utility::Math::Rand() % 26;
				listItem += __groupCapitalArray[selectedAlpha];
			}
			__pWordString[i][j] = listItem;
			listItem = "";
		}
	}

}

void
SearchBarForm::OnKeypadActionPerformed(Control &source, Tizen::Ui::KeypadAction keypadAction)
{
	__pSearchBar->HideKeypad();
	Invalidate(true);
}

void
SearchBarForm::OnKeypadClosed(Control &source)
{
	SetActionBarsVisible(FORM_ACTION_BAR_FOOTER, true);
}

void
SearchBarForm::OnKeypadOpened(Control &source)
{
	SetActionBarsVisible(FORM_ACTION_BAR_FOOTER, false);
}

void
SearchBarForm::OnSearchBarModeChanged(SearchBar& source, SearchBarMode mode)
{
	Rectangle clientRect;
	__pSearchBar->SetText(L"");
	if(mode == SEARCH_BAR_MODE_INPUT)
	{
		SetActionBarsVisible(FORM_ACTION_BAR_FOOTER, false);
		clientRect = GetClientAreaBounds();
		__pSearchBar->SetContentAreaSize(Dimension(clientRect.width, clientRect.height - __pSearchBar->GetHeight()));
		__pSearchBarListView->SetSize(Dimension(clientRect.width, clientRect.height - __pSearchBar->GetHeight()));
		__pAllTextGroupedListView->SetSize(Dimension(clientRect.width, clientRect.height));
		__pAllTextGroupedListView->SetEnabled(false);
	}
	else
	{
		SetActionBarsVisible(FORM_ACTION_BAR_FOOTER, true);
		clientRect = GetClientAreaBounds();
		__pSearchedTextList->RemoveAll(true);
		__pSearchBarListView->UpdateList();
		__pAllTextGroupedListView->SetShowState(true);
		__pSearchBarListView->SetShowState(false);
		__pSearchBar->SetText(L"Click here!");
		__pAllTextGroupedListView->SetSize(Dimension(clientRect.width, clientRect.height - __pSearchBar->GetHeight()));
		__pAllTextGroupedListView->SetEnabled(true);
	}
	__pAllTextGroupedListView->ScrollToItem(0, -1);
	Invalidate(true);
}

void
SearchBarForm::OnTextValueChanged(const Control& source)
{
	UpdateSearchResult();
}

void
SearchBarForm::UpdateSearchResult(void)
{
	String inputText = __pSearchBar->GetText();
	int Indexof = -1;
	int GetItemCount = 0;

	if(inputText.CompareTo(L"") != 0)
	{
		__pAllTextGroupedListView->SetShowState(false);
		__pSearchBarListView->SetShowState(true);
		__pSearchedTextList->RemoveAll(true);

	for (int i = 0; i < 26; i ++)
	{
			for (int j = 0; j < ITEM_MAX ; j ++)
			{
					Indexof = -1;
					GetItemCount = __pSearchedTextList->GetCount();
				   __pWordString[i][j].IndexOf(inputText, 0, Indexof);
					if(Indexof >= 0)
					__pSearchedTextList->InsertAt(*(new (std::nothrow) String(__pWordString[i][j])), GetItemCount);
				}
			}
		__pSearchBarListView->UpdateList();
	}
	else
	{
		__pSearchedTextList->RemoveAll(true);
		__pSearchBarListView->UpdateList();
		__pAllTextGroupedListView->SetShowState(true);
		__pSearchBarListView->SetShowState(false);
		__pSearchBar->SetText(L"");
	}
	Invalidate(true);
}

void
SearchBarForm::OnFastScrollIndexSelected(Control& source, Tizen::Base::String& index)
{
	String compare(L"");
	for(int i = 0; i < GROUP_MAX; i ++)
	{
		compare.Format(5, L"%c", i + 97);
		if(compare.CompareTo(index) == 0)
		{
			__pAllTextGroupedListView->ScrollToItem(i, -1);
		}
	}
	__pAllTextGroupedListView->Invalidate(false);
}

int
SearchBarForm::GetGroupCount(void)
{
	return GROUP_MAX;
}

int
SearchBarForm::GetItemCount(int groupIndex)
{
	return ITEM_MAX;
}

GroupItem*
SearchBarForm::CreateGroupItem(int groupIndex, int itemWidth)
{
	GroupItem* pItem = new (std::nothrow) GroupItem();
	pItem->Construct(Dimension(itemWidth, 48));
	String text(L"");
	text = __groupCapitalArray[groupIndex];
	pItem->SetElement(text, null);

	return pItem;
}

bool
SearchBarForm::DeleteGroupItem(int groupIndex, GroupItem* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}

ListItemBase*
SearchBarForm::CreateItem(int groupIndex, int itemIndex, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem* pItem = new (std::nothrow) CustomItem();
	pItem->Construct(Dimension(itemWidth, 112), style);
	pItem->AddElement(Rectangle(40, 32, 300, 50), ID_FORMAT_STRING, __pWordString[groupIndex][itemIndex], 40);

	return pItem;
}

bool
SearchBarForm::DeleteItem(int groupIndex, int itemIndex, ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}

void
SearchBarForm::OnGroupedListViewItemStateChanged(GroupedListView& listView, int groupIndex, int itemIndex, int elementId, ListItemStatus state)
{
	if (itemIndex != ID_GROUPITEM_INDEX)
	{
		String selectedText;
		selectedText = __pWordString[groupIndex][itemIndex];
		__pSearchBar->SetText(selectedText);
		Invalidate(true);

		selectedText.Append(L" is selected");
		MessageBox messageBox;
		messageBox.Construct(L"SearchBar", selectedText, MSGBOX_STYLE_OK, 2000);
		int modalResult;
		messageBox.ShowAndWait(modalResult);
	}
}

void
SearchBarForm::OnListViewItemStateChanged(ListView& listView, int index, int elementId, ListItemStatus status)
{
	String selectedText;
	selectedText = *(static_cast<String *>(__pSearchedTextList->GetAt(index)));
	__pSearchBar->SetText(selectedText);
	UpdateSearchResult();

	selectedText.Append(L" is selected");
	MessageBox messageBox;
	messageBox.Construct(L"SearchBar", selectedText, MSGBOX_STYLE_OK, 2000);
	int modalResult;
	messageBox.ShowAndWait(modalResult);
}

void
SearchBarForm::OnListViewItemSwept(ListView& listView, int index, SweepDirection direction)
{
}

void
SearchBarForm::OnListViewContextItemStateChanged(ListView& listView, int index, int elementId, ListContextItemStatus state)
{
}

int
SearchBarForm::GetItemCount(void)
{
	if (__pSearchedTextList != null)
	{
		return __pSearchedTextList->GetCount();
	}

	return 0;
}

ListItemBase*
SearchBarForm::CreateItem(int index, int itemWidth)
{

	String* pItemText = null;
	pItemText = static_cast<String *>(__pSearchedTextList->GetAt(index));

	CustomItem* pItem = new (std::nothrow) CustomItem();
	if(pItemText)
	{
		pItem->Construct(Dimension(itemWidth, 112), LIST_ANNEX_STYLE_NORMAL);
		pItem->AddElement(Rectangle(26, 32, 300, 50), 0, *pItemText, true);
	}
	return pItem;
}

bool
SearchBarForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}

void
SearchBarForm::OnTouchPressed (const Control& source, const Point& currentPosition, const TouchEventInfo &touchInfo)
{
	__pSearchBar->HideKeypad();
	Invalidate(true);
}
