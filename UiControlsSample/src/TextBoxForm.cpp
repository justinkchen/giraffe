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
#include "TextBoxForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Base;

TextBoxForm::TextBoxForm(void)
	: __pTextBox(null)
{
}

TextBoxForm::~TextBoxForm(void)
{
}

bool
TextBoxForm::Initialize(void)
{
	Construct(FORM_STYLE_NORMAL| FORM_STYLE_INDICATOR| FORM_STYLE_HEADER| FORM_STYLE_FOOTER);
	SetFooter();
	return true;
}

result
TextBoxForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	pHeader->SetTitleText(L"TextBox");

	__pTextBox = new (std::nothrow) TextBox();
	__pTextBox->Construct(Rectangle(175, 170, 380, 450), TEXT_BOX_BORDER_ROUNDED);
	__pTextBox->SetTextSize(50);

	String sampleText1(L"TextBox Sample");
	__pTextBox->SetText(sampleText1);

	String sampleText2(L" Tizen SDK");
	__pTextBox->AppendText(sampleText2);

	AddControl(*__pTextBox);

	return r;
}
