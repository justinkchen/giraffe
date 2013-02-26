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
#ifndef _QUICK_PANEL_FRAME_FORM_H_
#define _QUICK_PANEL_FRAME_FORM_H_

#include <FApp.h>
#include <FShell.h>
#include "BaseForm.h"

class QuickPanelFrameForm
	: public BaseForm
{
public:
	QuickPanelFrameForm(void);
	virtual ~QuickPanelFrameForm(void);

	bool Initialize(void);
	void SetFooter(void);
	void CreateQuickPanelFrame(void);
	void AttachControls(void);
	void DetachControls(void);
	void GetBitmap(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

private:
	static const int ID_FOOTER_ITEM1 = 200;
	static const int ID_FOOTER_ITEM2 = 201;

	Tizen::Shell::QuickPanelFrame* __pQuickPanelFrame;
	Tizen::Ui::Controls::Label* __pLogLabel;
	Tizen::Ui::Controls::Button * __pQuickPanelFrameButton;
	Tizen::Ui::Controls::Label* __pSoundLabelMin;
	Tizen::Ui::Controls::Label* __pSoundLabelMax;
	Tizen::Ui::Controls::Slider* __pSlider;
	Tizen::Graphics::Bitmap* __pMinSoundBitmap;
	Tizen::Graphics::Bitmap* __pMaxSoundBitmap;
}; // QuickPanelFrameForm

#endif // _QUICK_PANEL_FRAME_FORM_H_
