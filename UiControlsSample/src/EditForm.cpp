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
#include "EditForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::Graphics;

const int LABEL_HEIGHT = 60;

EditForm::EditForm(void)
	: __pEditArea(null)
	, __pEditField(null)
	, __pEditFieldDisable(null)
{
}

EditForm::~EditForm(void)
{
}

bool
EditForm::Initialize(void)
{
	Construct(L"IDF_FORM_EDIT");
	return true;
}

result
EditForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;


	Button* pButtonOk = static_cast<Button*>(GetControl(L"IDC_BUTTON_CLEAR2", true));
	if(pButtonOk)
	{
		pButtonOk->SetActionId(ID_BUTTON_OK);
		pButtonOk->AddActionEventListener(*this);
	}
	Button* pButtonClear = static_cast<Button*>(GetControl(L"IDC_BUTTON_CLEAR", true));
	if(pButtonClear)
	{
		pButtonClear->SetActionId(ID_BUTTON_CLEAR);
		pButtonClear->AddActionEventListener(*this);
	}
	__pEditArea = static_cast<EditArea*>(GetControl(L"IDC_EDITAREA", true));
	if(__pEditArea)
	{
		__pEditArea->AddTextEventListener(*this);
	}
	__pEditField = static_cast<EditField*>(GetControl(L"IDC_EDITFIELD", true));
	if(__pEditField)
	{
		__pEditField->AddTextEventListener(*this);
	}

	__pEditFieldDisable = static_cast<EditField*>(GetControl(L"IDC_EDITFIELD_DISABLE", true));
	__pEditFieldDisable->SetEnabled(false);

	return r;
}


// How to make ActionListener.
void
EditForm::OnActionPerformed(const Control& source, int actionId)
{
	String editText(__pEditArea->GetText());
	String tempText(__pEditField->GetText());

	switch (actionId)
	{
	case ID_BUTTON_OK:
		editText.Append(tempText);
		__pEditField->Clear();
		break;
	case ID_BUTTON_CLEAR:
		__pEditArea->Clear();
		break;
	case ID_EXIT:
		BaseForm::OnActionPerformed(source, actionId);
	    break;
	default:
		break;
	}

	__pEditArea->Invalidate(false);
	__pEditField->Invalidate(false);
	BaseForm::OnActionPerformed(source, actionId);
}

void
EditForm::OnTextValueChanged(const Control& source)
{
	SetFocus();
}

void
EditForm::OnTextValueChangeCanceled(const Control& source)
{
	SetFocus();
}
