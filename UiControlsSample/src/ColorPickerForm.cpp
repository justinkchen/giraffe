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
#include "ColorPickerForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

ColorPickerForm::ColorPickerForm()
	: __pLabelColor(null)
{
}

ColorPickerForm::~ColorPickerForm()
{
}

bool
ColorPickerForm::Initialize(void)
{
	Construct(L"IDF_FORM_COLORPICKER");
	return true;
}

result
ColorPickerForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	ColorPicker* pColorPicker = static_cast<ColorPicker*>(GetControl("IDC_COLORPICKER", true));
	pColorPicker->AddColorChangeEventListener(*this);

	__pLabelColor = static_cast<Label*>(GetControl("IDC_LABEL_COLOR", true));
	__pLabelColor->SetBackgroundColor(pColorPicker->GetColor());
	AddControl(*__pLabelColor);

	return r;
}

void
ColorPickerForm::OnColorChanged(const Control& source, const Tizen::Graphics::Color& color)
{
	__pLabelColor->SetBackgroundColor(color);
	__pLabelColor->Invalidate(false);
}
