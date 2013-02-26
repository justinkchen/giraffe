//
// Tizen native SDK
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
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
#include "QuickPanelFrameForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Shell;

const wchar_t VOLUME_MIN_BITMAP[] = L"sliderVolumeMin.png";
const wchar_t VOLUME_MAX_BITMAP[] = L"sliderVolumeMax.png";

QuickPanelFrameForm::QuickPanelFrameForm(void)
	: __pQuickPanelFrame(null)
	, __pLogLabel(null)
	, __pQuickPanelFrameButton(null)
	, __pSlider(null)

{
}
QuickPanelFrameForm::~QuickPanelFrameForm(void)
{
	delete __pQuickPanelFrame;
}

result
QuickPanelFrameForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

bool
QuickPanelFrameForm::Initialize(void)
{
	Form::Construct(FORM_STYLE_NORMAL| FORM_STYLE_INDICATOR| FORM_STYLE_HEADER| FORM_STYLE_FOOTER);
	return true;
}

result
QuickPanelFrameForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	BaseForm::OnInitializing();

	Header* pHeader = GetHeader();
	pHeader->SetTitleText(L"QuickPanelFrame");

	SetFooter();
	CreateQuickPanelFrame();
	AttachControls();

	return r;
}

void
QuickPanelFrameForm::SetFooter()
{
	 Footer* pFooter = GetFooter();
	 if (pFooter)
	 {
		FooterItem  footerItem1;
		footerItem1.Construct(ID_FOOTER_ITEM1);
		footerItem1.SetText(L"Attached");

		FooterItem  footerItem2;
		footerItem2.Construct(ID_FOOTER_ITEM2);
		footerItem2.SetText(L"Detached");

		pFooter->SetStyle(FOOTER_STYLE_SEGMENTED_TEXT);
		pFooter->AddItem(footerItem1);
		pFooter->AddItem(footerItem2);
		pFooter->AddActionEventListener(*this);
		pFooter->SetBackButton();
	 }
}

void
QuickPanelFrameForm::CreateQuickPanelFrame()
{
	Rectangle rect = GetClientAreaBounds();
	__pQuickPanelFrame = new QuickPanelFrame();
	__pQuickPanelFrame->Construct(400);

	__pQuickPanelFrameButton = new Button();
	__pQuickPanelFrameButton->Construct(Rectangle(15,170,660,200),L"QuickPanelFrame Button");
	__pQuickPanelFrame->AddControl(*__pQuickPanelFrameButton);

	__pSlider = new Slider();

	__pSlider->Construct(Rectangle(40, 10, 610, 150), SLIDER_STYLE_NONE, 0, 15);
	__pQuickPanelFrame->AddControl(*__pSlider);

	__pLogLabel = new Label();
	__pLogLabel->Construct(Rectangle(0, rect.height - 400, rect.width, 400), L"Drag down indicator to check the QuickPanelFrame.");
	__pLogLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	AddControl(*__pLogLabel);
}

void
QuickPanelFrameForm::AttachControls()
{
	__pQuickPanelFrame->SetShowState(true);
	__pQuickPanelFrame->Show();
}

void
QuickPanelFrameForm::DetachControls()
{
	__pQuickPanelFrame->SetShowState(false);
	__pQuickPanelFrame->Show();
}

void
QuickPanelFrameForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_FOOTER_ITEM1:
		AttachControls();
		break;
	case ID_FOOTER_ITEM2:
		DetachControls();
		break;
	}
	__pLogLabel->Invalidate(false);
}

