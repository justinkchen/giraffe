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
#include "ProgressForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

ProgressForm::ProgressForm(void)
	: __pProgress(null)
	, __pProgressDisable(null)
	, __pProgressColor(null)
{
}

ProgressForm::~ProgressForm(void)
{
}

bool
ProgressForm::Initialize(void)
{
	Construct(L"IDF_FORM_PROGRESS");
	return true;
}

result
ProgressForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	__pProgress = static_cast<Progress*>(GetControl(L"IDC_PROGRESS", true));
	__pProgressColor = static_cast<Progress*>(GetControl(L"IDC_PROGRESS_COLOR", true));
	__pProgressDisable = static_cast<Progress*>(GetControl(L"IDC_PROGRESS_DISABLE", true));
	__pProgressDisable->SetEnabled(false);

	Button* pButtonUp = static_cast<Button*>(GetControl(L"IDC_BUTTON_UP", true));
	Button* pButtonDown = static_cast<Button*>(GetControl(L"IDC_BUTTON_DOWN", true));

	pButtonUp->SetActionId(ID_BUTTON_UP);
	pButtonDown->SetActionId(ID_BUTTON_DOWN);
	pButtonUp->AddActionEventListener(*this);
	pButtonDown->AddActionEventListener(*this);

	return r;
}

void
ProgressForm::OnActionPerformed(const Control& source, int actionId)
{

	int val = __pProgress->GetValue();
	int maxVal, minVal;
	__pProgress->GetRange(minVal, maxVal);
	switch(actionId)
	{
	case ID_BUTTON_UP:
		if(val < maxVal)
		{
			val++;
		}
		__pProgress->SetValue(val);
		__pProgressColor->SetValue(val);
		break;
	case ID_BUTTON_DOWN:
		if(val > minVal)
		{
			val--;
		}
		__pProgress->SetValue(val);
		__pProgressColor->SetValue(val);
		break;
	default:
		break;
	}
	__pProgress->Invalidate(false);
	__pProgressColor->Invalidate(false);

}
