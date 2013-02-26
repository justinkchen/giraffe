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
#include "ButtonForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Media;


ButtonForm::ButtonForm(void)
{
}

ButtonForm::~ButtonForm(void)
{
}

bool
ButtonForm::Initialize(void)
{
	Construct(L"IDF_FORM_BUTTON");
	return true;
}

result
ButtonForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	Button* pButton = static_cast <Button*> (GetControl("IDC_BUTTON_DISABLE", true));
	pButton->SetEnabled(false);

	return r;
}

void
ButtonForm::OnActionPerformed(const Control& source, int actionId)
{
}
