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
#include "PanelForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

const int LABEL_HEIGHT = 90;

PanelForm::PanelForm(void)
	: __pLabelLog(null)
{
}

PanelForm::~PanelForm(void)
{
}

bool
PanelForm::Initialize(void)
{
	Construct(L"IDF_FORM_PANEL");
	return true;
}

result
PanelForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;
	return r;
}

void
PanelForm::OnActionPerformed(const Control& source, int actionId)
{
}
