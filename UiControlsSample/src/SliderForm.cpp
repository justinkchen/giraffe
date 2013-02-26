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
#include "SliderForm.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

SliderForm::SliderForm(void)
	: __pLabelLog(null)
	, __pSlider(null)
{
}

SliderForm::~SliderForm(void)
{
}

bool
SliderForm::Initialize(void)
{
	Construct(L"IDF_FORM_SLIDER");
	return true;
}

result
SliderForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	Slider *pSlider = static_cast<Slider*>(GetControl("IDC_SLIDER", true));
	pSlider->AddAdjustmentEventListener(*this);

	Slider * pSliderDisable = static_cast<Slider*>(GetControl("IDC_SLIDER_DISABLE", true));
	pSliderDisable->SetEnabled(false);

	return r;
}


void
SliderForm::OnAdjustmentValueChanged(const Control& source, int adjustment)
{
}

void
SliderForm::OnSliderBarMoved(Slider& source, int value)
{
}

