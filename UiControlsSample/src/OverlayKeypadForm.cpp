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
#include "OverlayKeypadForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Graphics;

OverlayKeypadForm::OverlayKeypadForm(void)
	: __pEditArea(null)
	, __pEditField(null)
	, __pEditFieldText(null)
	, __pEditAreaText(null)
	, __pEditFieldPreText(null)
	, __pEditAreaPreText(null)
{
}

OverlayKeypadForm::~OverlayKeypadForm(void)
{
}

bool
OverlayKeypadForm::Initialize(void)
{
	Construct(L"IDF_FORM_OVERLAYKEYPAD");
	return true;
}

void
OverlayKeypadForm::OnOrientationChanged(const Control& source, OrientationStatus orientationStatus)
{
	SetActionBarsVisible(FORM_ACTION_BAR_HEADER,true);

	Invalidate(true);
}

result
OverlayKeypadForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;
	SetOrientation(ORIENTATION_AUTOMATIC);
    AddOrientationEventListener(*this);
    Tizen::Ui::OrientationStatus orientationStatus = GetOrientationStatus();
	if(orientationStatus == ORIENTATION_STATUS_LANDSCAPE|| orientationStatus == ORIENTATION_STATUS_LANDSCAPE_REVERSE)
	{
		SetActionBarsVisible(FORM_ACTION_BAR_HEADER,false);
	}

	__pScrollPanel = static_cast<ScrollPanel*>(GetControl(L"IDC_SCROLLPANEL", false));
	__pEditField = static_cast<EditField*>(GetControl(L"IDC_EDITFIELD", true));
	__pEditArea = static_cast<EditArea*>(GetControl(L"IDC_EDITAREA", true));

	__pEditField->AddTextEventListener(*this);
	__pEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pEditField->AddKeypadEventListener(*this);
	
	__pEditArea->AddTextEventListener(*this);
	__pEditArea->SetOverlayKeypadCommandButtonVisible(false);
	__pEditArea->AddKeypadEventListener(*this);

	Button* pButtonClear = static_cast<Button*>(GetControl(L"IDC_BUTTON_EDITAREA_CLEAR", true));
	pButtonClear->SetActionId(ID_BUTTON_EDITAREA_CLEAR);
	pButtonClear->AddActionEventListener(*this);

	__pEditFieldText = new (std::nothrow) String();
	__pEditAreaText = new (std::nothrow) String();
	__pEditAreaPreText = new (std::nothrow) String();
	__pEditFieldPreText = new (std::nothrow) String();

	return r;
}

result
OverlayKeypadForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	delete __pEditFieldText;
	delete __pEditAreaText;
	delete __pEditFieldPreText;
	delete __pEditAreaPreText;

	return r;
}

void
OverlayKeypadForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_BUTTON_EDITAREA_CLEAR:
		*__pEditAreaPreText = L"";
		*__pEditFieldPreText = L"";
		__pEditArea->Clear();
		__pEditField->Clear();
		Invalidate(true);
		break;
	case ID_BUTTON_DONE:
		*__pEditFieldPreText = __pEditField->GetText();
		*__pEditAreaPreText = __pEditArea->GetText();
		__pEditField->HideKeypad();
		__pEditField->Invalidate(false);
		__pEditArea->HideKeypad();
		__pEditArea->Invalidate(false);
		break;
	case ID_BUTTON_CANCEL:
		__pEditField->SetText(*__pEditFieldPreText);
		__pEditArea->SetText(*__pEditAreaPreText);
		__pEditField->HideKeypad();
		__pEditField->Invalidate(false);
		__pEditArea->HideKeypad();
		__pEditArea->Invalidate(false);
		break;
	default:
		break;
	}
}

void
OverlayKeypadForm::OnKeypadWillOpen(Control& source)
{
	Footer* pFooter = GetFooter();
	pFooter->SetShowState(false);
}

void
OverlayKeypadForm::OnKeypadOpened(Control& source)
{
	Header* pHeader = GetHeader();

	HeaderItem doneItem;
	HeaderItem cancelItem;

	doneItem.Construct(ID_BUTTON_DONE);
	doneItem.SetText("Done");

	cancelItem.Construct(ID_BUTTON_CANCEL);
	cancelItem.SetText("Cancel");

	pHeader->SetStyle(HEADER_STYLE_BUTTON);
	pHeader->AddItem(doneItem);
	pHeader->AddItem(cancelItem);
	pHeader->AddActionEventListener(*this);
}

void
OverlayKeypadForm::OnKeypadClosed(Control& source)
{
	Header* pHeader = GetHeader();
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	pHeader->SetTitleText(L"OverlayKeypad");
	Footer* pFooter = GetFooter();
	pFooter->SetShowState(true);
	Invalidate(true);
}

void
OverlayKeypadForm::OnTextValueChanged(const Control& source)
{
}

void
OverlayKeypadForm::OnTextValueChangeCanceled(const Control& source)
{
}
