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
#include "CheckButtonForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

CheckButtonForm::CheckButtonForm(void)
{
}

CheckButtonForm::~CheckButtonForm(void)
{
}

bool
CheckButtonForm::Initialize(void)
{
	Construct(L"IDF_FORM_CHECKBUTTON");
	return true;
}

result
CheckButtonForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	CheckButton* pCheckButton = static_cast <CheckButton*> (GetControl("IDC_CHECKBUTTON_DISABLE", true));
	pCheckButton->SetEnabled(false);

	return r;
}

void
CheckButtonForm::OnActionPerformed(const Control& source, int actionId)
{
}
