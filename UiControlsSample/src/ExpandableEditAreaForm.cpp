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
#include "ExpandableEditAreaForm.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Utility;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

const int EXPANDABLE_LINE_MAX = 3;

ExpandableEditAreaForm::ExpandableEditAreaForm(void)
	: __pExpandableEdit(null)
	, __pPanel(null)
	, __pLabel(null)
{
}

ExpandableEditAreaForm::~ExpandableEditAreaForm(void)
{
}

bool
ExpandableEditAreaForm::Initialize(void)
{
	Construct(L"IDF_FORM_EXPANDABLEEDITAREA");
	return true;
}

result
ExpandableEditAreaForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	LayoutHeader();
	LayoutContent();
	return r;
}

result
ExpandableEditAreaForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

void
ExpandableEditAreaForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_FOOTER_BUTTON_BACK:
		BaseForm::OnActionPerformed(source, actionId);
	    break;
	case ID_HEADER_BUTTON_SEND:
	{
		String log(L"");
		log = __pExpandableEdit->GetText();
		if (log.CompareTo(L"") != 0)
		{
			__pLabel->SetText(log);
			__pExpandableEdit->SetText(L"");
			__pExpandableEdit->SetEnabled(true);
			__pExpandableEdit->SetKeypadEnabled(true);
			__pExpandableEdit->HideKeypad();

			Rectangle clientArea = GetClientAreaBounds();
			__pPanel->SetSize(clientArea.width, PANEL_HEIGHT);
			__pPanel->SetPosition(0, clientArea.height - PANEL_HEIGHT);
			__pExpandableEdit->SetSize(clientArea.width - EXPANDABLEEDITAREA_RIGHT_MARGIN, EXPANDABLEEDITAREA_HEIGHT);
			__prevBounds = Rectangle(15, 15, clientArea.width - EXPANDABLEEDITAREA_RIGHT_MARGIN, EXPANDABLEEDITAREA_HEIGHT);
			__pLabel->SetSize(clientArea.width - LEFT_MARGIN - RIGHT_MARGIN, clientArea.height - PANEL_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN);
		}
		Invalidate(true);
	}
	break;
	default:
		break;
	}
}

void
ExpandableEditAreaForm::LayoutHeader(void)
{

	Header* pHeader = GetHeader();
	pHeader->AddActionEventListener(*this);
}

void
ExpandableEditAreaForm::LayoutContent(void)
{
	Rectangle clientArea = GetClientAreaBounds();

	__pPanel = new (std::nothrow) Panel();
	__pPanel->Construct(Rectangle(0, clientArea.height - PANEL_HEIGHT, clientArea.width, PANEL_HEIGHT));
	__pPanel->SetBackgroundColor(Color(108, 108, 108));
	AddControl(*__pPanel);

	__pLabel = new (std::nothrow) Label();
	__pLabel->Construct(Rectangle(LEFT_MARGIN, RIGHT_MARGIN, clientArea.width - LEFT_MARGIN - RIGHT_MARGIN, clientArea.height - PANEL_HEIGHT), L"");
	__pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	__pLabel->SetTextVerticalAlignment(ALIGNMENT_TOP);
	__pLabel->SetText(L"Message");
	AddControl(*__pLabel);

	Button* pButton = new (std::nothrow) Button();
	pButton->Construct(Rectangle(clientArea.width - 147, 15, 129, 90));
	pButton->SetText(L"Send");
	pButton->SetActionId(ID_HEADER_BUTTON_SEND);
	pButton->AddActionEventListener(*this);
	__pPanel->AddControl(*pButton);

	__pExpandableEdit = new (std::nothrow) ExpandableEditArea();
	__prevBounds = Rectangle(15, 15, clientArea.width - EXPANDABLEEDITAREA_RIGHT_MARGIN, EXPANDABLEEDITAREA_HEIGHT);
	__pExpandableEdit->Construct(__prevBounds, EXPANDABLE_EDIT_AREA_STYLE_NORMAL, EXPANDABLE_EDIT_AREA_TITLE_STYLE_NONE, EXPANDABLE_LINE_MAX);
	__pExpandableEdit->SetMargin(EDIT_MARGIN_TYPE_VERTICAL,20);
	__pExpandableEdit->AddKeypadEventListener(*this);
	__pExpandableEdit->AddExpandableEditAreaEventListener(*this);
	__pPanel->AddControl(*__pExpandableEdit);
	__pExpandableEdit->SetFocus();
	__pExpandableEdit->ShowKeypad();
}


void
ExpandableEditAreaForm::OnKeypadActionPerformed(Control& source, KeypadAction keypadAction)
{
}

void
ExpandableEditAreaForm::OnKeypadClosed(Control& source)
{
	Rectangle clientArea = GetClientAreaBounds();
	Rectangle prePanelBounds = __pPanel->GetBounds();
	__pLabel->SetSize(clientArea.width - LEFT_MARGIN - RIGHT_MARGIN, clientArea.height - __pPanel->GetBounds().height - TOP_MARGIN - BOTTOM_MARGIN);
	__pPanel->SetPosition(prePanelBounds.x, clientArea.height - prePanelBounds.height);
	Invalidate(true);
}

void
ExpandableEditAreaForm::OnKeypadOpened(Control& source)
{
	Rectangle clientArea = GetClientAreaBounds();
	Rectangle prePanelBounds = __pPanel->GetBounds();
	__pLabel->SetSize(clientArea.width - LEFT_MARGIN - RIGHT_MARGIN, clientArea.height - __pPanel->GetBounds().height - TOP_MARGIN - BOTTOM_MARGIN);
	__pPanel->SetPosition(prePanelBounds.x, clientArea.height - prePanelBounds.height);
	Invalidate(true);
}

void
ExpandableEditAreaForm::OnKeypadWillOpen(Control& source)
{
}
void
ExpandableEditAreaForm::OnKeypadBoundsChanged(Control& source)
{
	Rectangle clientArea = GetClientAreaBounds();
	Rectangle prePanelBounds = __pPanel->GetBounds();
	__pLabel->SetSize(clientArea.width - LEFT_MARGIN - RIGHT_MARGIN, clientArea.height - __pPanel->GetBounds().height - TOP_MARGIN - BOTTOM_MARGIN);
	__pPanel->SetPosition(prePanelBounds.x, clientArea.height - prePanelBounds.height);
	Invalidate(true);
}

void
ExpandableEditAreaForm::OnExpandableEditAreaLineAdded(ExpandableEditArea& source, int newLineCount)
{
	Rectangle newBounds = __pExpandableEdit->GetBounds();
	Rectangle prePanelBounds = __pPanel->GetBounds();
	__pPanel->SetBounds(Rectangle(prePanelBounds.x, prePanelBounds.y - (newBounds.height - __prevBounds.height), prePanelBounds.width,
			prePanelBounds.height + (newBounds.height - __prevBounds.height)));
	__prevBounds = __pExpandableEdit->GetBounds();

	Rectangle labelArea = GetClientAreaBounds();
	prePanelBounds = __pPanel->GetBounds();
	__pLabel->SetSize(labelArea.width - LEFT_MARGIN - RIGHT_MARGIN, labelArea.height - prePanelBounds.height - TOP_MARGIN - BOTTOM_MARGIN );
	Invalidate(true);
}

void
ExpandableEditAreaForm::OnExpandableEditAreaLineRemoved(ExpandableEditArea& source, int newLineCount)
{
	Rectangle newBounds = __pExpandableEdit->GetBounds();
	Rectangle prePanelBounds = __pPanel->GetBounds();
	__pPanel->SetBounds(Rectangle(prePanelBounds.x, prePanelBounds.y + (__prevBounds.height - newBounds.height), prePanelBounds.width,
			prePanelBounds.height - (__prevBounds.height - newBounds.height)));
	__prevBounds = __pExpandableEdit->GetBounds();

	Rectangle labelArea = GetClientAreaBounds();
	prePanelBounds = __pPanel->GetBounds();
	__pLabel->SetSize(labelArea.width - LEFT_MARGIN - RIGHT_MARGIN, labelArea.height - prePanelBounds.height - TOP_MARGIN - BOTTOM_MARGIN );
	Invalidate(true);
}
