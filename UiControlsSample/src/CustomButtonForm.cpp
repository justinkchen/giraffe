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
#include "CustomButtonForm.h"
#include "CustomButton.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Uix::Sensor;

const int LABEL_HEIGHT = 100;

CustomButtonForm::CustomButtonForm(void)
{
}

CustomButtonForm::~CustomButtonForm(void)
{
}

bool
CustomButtonForm::Initialize(void)
{
	Construct(L"IDF_FORM_CUSTOMBUTTON");
	return true;
}

result
CustomButtonForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	CustomButton* pButton = new (std::nothrow) CustomButton;
    pButton->Construct(Rectangle(210, 200, 300, 300));
    pButton->SetText(L"MyButton");
    AddControl(*pButton);

    pButton->SetClickListener(this);

	return r;
}

void
CustomButtonForm::OnClicked(CustomButton& source)
{
	Invalidate(true);
}
