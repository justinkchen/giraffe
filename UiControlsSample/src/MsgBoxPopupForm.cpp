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
#include "MsgBoxPopupForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

MsgBoxPopupForm::MsgBoxPopupForm(void)
	: __pPopup(null)
	, __pProgressPopup(null)
	, __pLabel(null)
{
}

MsgBoxPopupForm::~MsgBoxPopupForm(void)
{
}

bool
MsgBoxPopupForm::Initialize(void)
{
	Construct(L"IDF_FORM_MSGBOXPOPUP");
	return true;
}

result
MsgBoxPopupForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	__pProgressPopup = new (std::nothrow) ProgressPopup();
	__pProgressPopup->Construct(true,false);
	__pProgressPopup->SetTitleText(L"Title");
	__pProgressPopup->SetBounds(260,260,200,500);
	__pProgressPopup->SetText(L"Hello World!");
	__pProgressPopup->AddProgressPopupEventListener(*this);

	__pPopup = new (std::nothrow) Popup();
	__pPopup->Construct(true, Dimension(600, 750));
	__pPopup->SetTitleText(L"Title");

	Rectangle rect;
	rect = __pPopup->GetClientAreaBounds();
	__pLabel = new (std::nothrow) Label();
	__pLabel->Construct(Rectangle(0, 0, rect.width, 180), L"Hello World!");
	__pLabel->SetTextHorizontalAlignment(ALIGNMENT_CENTER);

	__pPopup->AddControl(*__pLabel);

	Button *pButtonClose = new (std::nothrow) Button();
	pButtonClose->Construct(Rectangle(190, 510, 180, 74), L"Close");
	pButtonClose->SetActionId(ID_BUTTON_CLOSE_POPUP);
	pButtonClose->AddActionEventListener(*this);
	__pPopup->AddControl(*pButtonClose);


	Button* pButtonMessageBox = static_cast<Button*>(GetControl("IDC_BUTTON_MESSAGEBOX", true));
	if(pButtonMessageBox)
	{
		pButtonMessageBox->SetActionId(ID_BUTTON_MESSAGEBOX);
		pButtonMessageBox->AddActionEventListener(*this);
	}
	Button* pButtonPopup = static_cast<Button*>(GetControl("IDC_BUTTON_POPUP", true));
	if(pButtonPopup)
	{
		pButtonPopup->SetActionId(ID_BUTTON_POPUP);
		pButtonPopup->AddActionEventListener(*this);
	}

	Button* pButtonProgressPopup = static_cast<Button*>(GetControl("IDC_BUTTON_PROGRESSPOPUP", true));
	if(pButtonPopup)
	{
		pButtonProgressPopup->SetActionId(ID_BUTTON_PROGRESSPOPUP);
		pButtonProgressPopup->AddActionEventListener(*this);
	}

	return r;
}

result
MsgBoxPopupForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	delete __pPopup;
	delete __pProgressPopup;

	return r;
}

void
MsgBoxPopupForm::ShowMessageBox(void)
{
	MessageBox* pMessageBox = new (std::nothrow) MessageBox();
	pMessageBox->Construct(L"Title", L"Hello world!", MSGBOX_STYLE_OKCANCEL, 3000);

	int ModalResult;
	pMessageBox->ShowAndWait(ModalResult);

	delete pMessageBox;
}

void
MsgBoxPopupForm::ShowPopup(void)
{
	__pPopup->SetShowState(true);
	__pPopup->Show();
}

void
MsgBoxPopupForm::HidePopup(void)
{
	__pPopup->SetShowState(false);
	Invalidate(true);
}

void
MsgBoxPopupForm::ShowProgressPopup(void)
{
	__pProgressPopup->SetShowState(true);
	__pProgressPopup->Show();
}

void
MsgBoxPopupForm::HideProgressPopup(void)
{

}

void
MsgBoxPopupForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_BUTTON_MESSAGEBOX:
		ShowMessageBox();
		break;
	case ID_BUTTON_POPUP:
		ShowPopup();
		break;
	case ID_BUTTON_CLOSE_POPUP:
		HidePopup();
		break;
	case ID_BUTTON_PROGRESSPOPUP:
		ShowProgressPopup();
		break;
	default:
		break;
	}
}

void
MsgBoxPopupForm::OnProgressPopupCanceled(void)
{
	__pProgressPopup->SetShowState(false);
	Invalidate(true);
}
